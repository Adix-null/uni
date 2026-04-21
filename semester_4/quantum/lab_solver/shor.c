/*
 * Minimal Shor demo in plain C
 * Factors N = 15 using a tiny statevector simulator
 *
 * Compile (Linux/macOS):
 *     gcc shor.c -lm -o shor
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*==================== Complex numbers ====================*/

typedef struct {
    double re;
    double im;
} Complex;

static Complex c_add(Complex a, Complex b) {
    Complex r = {a.re + b.re, a.im + b.im};
    return r;
}

static Complex c_sub(Complex a, Complex b) {
    Complex r = {a.re - b.re, a.im - b.im};
    return r;
}

static Complex c_mul(Complex a, Complex b) {
    Complex r = {
        a.re * b.re - a.im * b.im,
        a.re * b.im + a.im * b.re
    };
    return r;
}

static Complex c_scale(Complex a, double s) {
    Complex r = {a.re * s, a.im * s};
    return r;
}

/*==================== Quantum state ====================*/

typedef struct {
    int n_qubits;
    int dim;        /* 2^n_qubits */
    Complex *amp;   /* amplitudes */
} QState;

QState *qs_create(int n_qubits) {
    QState *s = (QState *)malloc(sizeof(QState));
    s->n_qubits = n_qubits;
    s->dim = 1 << n_qubits;
    s->amp = (Complex *)calloc(s->dim, sizeof(Complex));
    printf("  [State] Allocated %d-qubit statevector (%d amplitudes, %zu bytes)\n",
           n_qubits, s->dim, s->dim * sizeof(Complex));
    /* initialize |0...0> */
    s->amp[0].re = 1.0;
    s->amp[0].im = 0.0;
    printf("  [State] Initialized to |0...0>\n");
    return s;
}

void qs_destroy(QState *s) {
    if (!s) return;
    free(s->amp);
    free(s);
}

/*==================== Basic number theory ====================*/

int gcd_int(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

/* modular exponentiation: a^x mod N */
int modexp_int(int a, int x, int N) {
    long long res = 1;
    long long base = a % N;
    while (x > 0) {
        if (x & 1) {
            res = (res * base) % N;
        }
        base = (base * base) % N;
        x >>= 1;
    }
    return (int)res;
}

/* smallest n with 2^n >= x */
int ceil_log2(int x) {
    int n = 0;
    int p = 1;
    while (p < x) {
        p <<= 1;
        n++;
    }
    return n;
}

/*==================== Quantum gates ====================*/

/* Hadamard on qubit 'qubit' (0 = least significant bit) */
void apply_hadamard(QState *s, int qubit) {
    int dim = s->dim;
    int step = 1 << qubit;
    double inv_sqrt2 = 1.0 / sqrt(2.0);

    for (int i = 0; i < dim; i += 2 * step) {
        for (int j = 0; j < step; ++j) {
            int idx0 = i + j;
            int idx1 = idx0 + step;
            Complex a = s->amp[idx0];
            Complex b = s->amp[idx1];

            /* (a|0> + b|1>) -> ((a+b)|0> + (a-b)|1>)/sqrt(2) */
            s->amp[idx0].re = (a.re + b.re) * inv_sqrt2;
            s->amp[idx0].im = (a.im + b.im) * inv_sqrt2;
            s->amp[idx1].re = (a.re - b.re) * inv_sqrt2;
            s->amp[idx1].im = (a.im - b.im) * inv_sqrt2;
        }
    }
}

/* Controlled phase: if qc=1 and qt=1, multiply by e^{i theta} */
void apply_controlled_phase(QState *s, int qc, int qt, double theta) {
    int dim = s->dim;
    double c = cos(theta);
    double si = sin(theta);

    for (int i = 0; i < dim; ++i) {
        int bit_c = (i >> qc) & 1;
        int bit_t = (i >> qt) & 1;
        if (bit_c && bit_t) {
            Complex a = s->amp[i];
            double re = a.re * c - a.im * si;
            double im = a.re * si + a.im * c;
            s->amp[i].re = re;
            s->amp[i].im = im;
        }
    }
}

/* In-place swap of two qubits (permute amplitudes) */
void swap_qubits(QState *s, int q1, int q2) {
    if (q1 == q2) return;
    int dim = s->dim;
    int mask = (1 << q1) | (1 << q2);

    for (int i = 0; i < dim; ++i) {
        int bits = i & mask;
        /* if bits differ, swap amplitudes with partner index */
        if (bits == (1 << q1) || bits == (1 << q2)) {
            int j = i ^ mask;
            if (i < j) {
                Complex tmp = s->amp[i];
                s->amp[i] = s->amp[j];
                s->amp[j] = tmp;
            }
        }
    }
}

/* Inverse QFT on the first t qubits (0..t-1) */
void apply_qft_inverse(QState *s, int t) {
    printf("  [QFT^-1] Applying inverse QFT to %d qubits\n", t);

    for (int k = 0; k < t; ++k) {
        /* controlled rotations */
        for (int j = 0; j < k; ++j) {
            double theta = -2.0 * M_PI / (double)(1 << (k - j + 1));
            apply_controlled_phase(s, j, k, theta);
        }
        apply_hadamard(s, k);
    }

    printf("  [QFT^-1] Bit-reversal: swapping qubit pairs\n");
    for (int i = 0; i < t / 2; ++i) {
        printf("  [QFT^-1]   Swapping qubit %d <-> qubit %d\n", i, t - 1 - i);
        swap_qubits(s, i, t - 1 - i);
    }

    printf("  [QFT^-1] Done.\n");
}

/*==================== Modular exponentiation unitary ====================*/

/*
 * We encode basis as:
 *   index = (y << t) | x
 * where:
 *   - x is the "phase" register: t qubits (least significant bits)
 *   - y is the second register: n qubits (most significant bits)
 *
 * We implement:
 *   |x>|0> -> |x>|a^x mod N>
 *
 * Since we always start with y=0, we can safely treat this as a permutation
 * only on that subspace.
 */

void apply_modexp(QState *s, int t, int n, int a, int N) {
    int dim = s->dim;
    Complex *new_amp = (Complex *)calloc(dim, sizeof(Complex));
    int x_mask = (1 << t) - 1;
    int x_dim = 1 << t;

    printf("  [ModExp] Computing |x>|0> -> |x>|%d^x mod %d> for x in [0, %d)\n",
           a, N, x_dim);

    /* Print the modular exponentiation table for the first few values */
    int preview = x_dim < 16 ? x_dim : 16;
    printf("  [ModExp] Precomputed a^x mod N table (first %d entries):\n", preview);
    for (int x = 0; x < preview; ++x) {
        printf("  [ModExp]   %d^%d mod %d = %d\n", a, x, N, modexp_int(a, x, N));
    }

    for (int idx = 0; idx < dim; ++idx) {
        int x = idx & x_mask;
        int y = idx >> t;

        if (y == 0) {
            int y_new = modexp_int(a, x, N);
            int idx_new = (y_new << t) | x;
            new_amp[idx_new] = c_add(new_amp[idx_new], s->amp[idx]);
        } else {
            new_amp[idx] = c_add(new_amp[idx], s->amp[idx]);
        }
    }

    free(s->amp);
    s->amp = new_amp;
    printf("  [ModExp] Done. Statevector updated.\n");
}

/*==================== Measurement ====================*/

/* Measure first t qubits (the x-register, least significant bits) */
int measure_first_register(QState *s, int t) {
    int dim = s->dim;
    int x_dim = 1 << t;
    int x_mask = x_dim - 1;
    double *p_x = (double *)calloc(x_dim, sizeof(double));

    /* Accumulate probabilities for each x */
    for (int idx = 0; idx < dim; ++idx) {
        int x = idx & x_mask;
        double re = s->amp[idx].re;
        double im = s->amp[idx].im;
        p_x[x] += re * re + im * im;
    }

    /* Print top non-negligible probabilities */
    printf("  [Measure] First register probability distribution (peaks > 0.01):\n");
    int shown = 0;
    for (int x = 0; x < x_dim; ++x) {
        if (p_x[x] > 0.01) {
            printf("  [Measure]   P(x=%4d) = %.4f\n", x, p_x[x]);
            shown++;
        }
    }
    if (shown == 0)
        printf("  [Measure]   (all probabilities <= 0.01)\n");

    /* Sample outcome according to probabilities */
    double r = (double)rand() / (double)RAND_MAX;
    printf("  [Measure] Random sample draw: r = %.6f\n", r);

    double cum = 0.0;
    int outcome = 0;
    for (int x = 0; x < x_dim; ++x) {
        cum += p_x[x];
        if (r <= cum) {
            outcome = x;
            break;
        }
    }
    printf("  [Measure] Collapsed to outcome x = %d (cumulative prob at this point: %.4f)\n",
           outcome, cum);

    /* Collapse state on measured x */
    for (int idx = 0; idx < dim; ++idx) {
        int x = idx & x_mask;
        if (x != outcome) {
            s->amp[idx].re = 0.0;
            s->amp[idx].im = 0.0;
        }
    }

    /* Renormalize */
    double norm = 0.0;
    for (int idx = 0; idx < dim; ++idx) {
        double re = s->amp[idx].re;
        double im = s->amp[idx].im;
        norm += re * re + im * im;
    }
    norm = sqrt(norm);
    printf("  [Measure] Post-collapse norm before renormalization: %.6f\n", norm);
    if (norm > 0.0) {
        for (int idx = 0; idx < dim; ++idx) {
            s->amp[idx].re /= norm;
            s->amp[idx].im /= norm;
        }
    }

    free(p_x);
    return outcome;
}

/*==================== Continued fractions: extract period ====================*/

/*
 * Given:
 *   m  = measurement result
 *   q  = 2^t (size of first register)
 *   N, a as in Shor
 *
 * Try to recover the order r of a modulo N from m/q using continued fractions.
 */

int extract_period_from_measurement(int m, int q, int N, int a) {
    if (m == 0) {
        printf("  [CF] m = 0: cannot extract period.\n");
        return 0;
    }

    printf("  [CF] Expanding %d/%d as a continued fraction\n", m, q);

    int cf[64];
    int cf_len = 0;

    int num = m;
    int den = q;

    /* Continued fraction expansion of m/q */
    while (den != 0 && cf_len < 64) {
        int a_i = num / den;
        cf[cf_len++] = a_i;
        int tmp = num % den;
        num = den;
        den = tmp;
    }

    printf("  [CF] Coefficients: [");
    for (int i = 0; i < cf_len; ++i) {
        printf("%d%s", cf[i], i < cf_len - 1 ? ", " : "");
    }
    printf("]\n");

    /* Build convergents and look for denominator giving a^r ≡ 1 mod N */
    long long p_prev2 = 0, p_prev1 = 1;
    long long q_prev2 = 1, q_prev1 = 0;

    int candidate_r = 0;

    printf("  [CF] Convergents:\n");
    for (int i = 0; i < cf_len; ++i) {
        int a_i = cf[i];
        long long p_i = a_i * p_prev1 + p_prev2;
        long long q_i = a_i * q_prev1 + q_prev2;

        p_prev2 = p_prev1;
        p_prev1 = p_i;
        q_prev2 = q_prev1;
        q_prev1 = q_i;

        int val = (q_i > 0) ? modexp_int(a, (int)(q_i % (2 * N + 1)), N) : -1;
        printf("  [CF]   convergent[%d] = %lld/%lld  (denominator r=%lld, %d^r mod %d = %d)\n",
               i, p_i, q_i, q_i, a, N, (q_i > 0 && q_i <= 2*N) ? modexp_int(a, (int)q_i, N) : -1);

        if (q_i == 0) continue;
        if (q_i > 2 * N) {
            printf("  [CF]   Denominator %lld > 2N=%d, stopping search.\n", q_i, 2 * N);
            break;
        }

        int r = (int)q_i;
        int check = modexp_int(a, r, N);
        if (check == 1) {
            printf("  [CF]   %d^%d mod %d = 1 -- candidate order r = %d found!\n", a, r, N, r);
            candidate_r = r;
            break;
        }
    }

    if (candidate_r == 0) {
        printf("  [CF] No valid order found from continued fractions.\n");
        return 0;
    }

    /* Ensure we return the smallest positive r with a^r ≡ 1 mod N */
    printf("  [CF] Searching for smallest divisor of %d that is also a valid order\n", candidate_r);
    for (int d = 1; d <= candidate_r; ++d) {
        if (candidate_r % d == 0) {
            int check = modexp_int(a, d, N);
            printf("  [CF]   d=%d: %d^%d mod %d = %d%s\n",
                   d, a, d, N, check, check == 1 ? " <-- smallest order!" : "");
            if (check == 1) {
                return d;
            }
        }
    }

    return candidate_r;
}

/*==================== Quantum order finding ====================*/

int quantum_order_finding(int N, int a) {
    int n = ceil_log2(N);     /* qubits in second register */
    int t = 2 * n;            /* qubits in first register */
    int Q = n + t;

    printf("  [QOF] Register sizes: t=%d (phase), n=%d (work), total=%d qubits\n", t, n, Q);
    printf("  [QOF] First register dimension: 2^%d = %d\n", t, 1 << t);

    QState *psi = qs_create(Q);

    /* 1. Put first register into uniform superposition */
    printf("  [QOF] Step 1: Applying Hadamard to all %d phase-register qubits\n", t);
    for (int qbit = 0; qbit < t; ++qbit) {
        apply_hadamard(psi, qbit);
    }
    printf("  [QOF] Phase register now in uniform superposition over %d basis states.\n", 1 << t);

    /* 2. Apply modular exponentiation unitary */
    printf("  [QOF] Step 2: Applying modular exponentiation a=%d, N=%d\n", a, N);
    apply_modexp(psi, t, n, a, N);

    /* 3. Apply inverse QFT to first register */
    printf("  [QOF] Step 3: Applying inverse QFT to phase register\n");
    apply_qft_inverse(psi, t);

    /* 4. Measure first register */
    printf("  [QOF] Step 4: Measuring phase register\n");
    int m = measure_first_register(psi, t);
    qs_destroy(psi);

    int q = 1 << t;

    printf("  [QOF] Measured m = %d (fraction m/q = %d/%d = %.6f)\n", m, m, q, (double)m / q);

    /* 5. Classical post-processing */
    printf("  [QOF] Step 5: Classical continued-fraction post-processing\n");
    int r = extract_period_from_measurement(m, q, N, a);
    printf("  [QOF] Extracted candidate order r = %d\n", r);

    return r;
}

/*==================== Outer Shor loop ====================*/

int shor_factor(int N) {
    printf("============================================================\n");
    printf("  Shor's Algorithm: factoring N = %d\n", N);
    printf("============================================================\n\n");

    /* Try several random a's */
    for (int attempt = 1; attempt <= 20; ++attempt) {
        int a = 2 + rand() % (N - 3);  /* random in [2, N-2] */
        int g = gcd_int(a, N);

        printf("------------------------------------------------------------\n");
        printf("Attempt %d: a = %d\n", attempt, a);
        printf("  gcd(%d, %d) = %d\n", a, N, g);

        if (g > 1 && g < N) {
            printf("  -> Nontrivial factor found directly by GCD!\n");
            return g;
        }

        printf("  gcd is trivial (1 or N); proceeding to quantum order finding.\n\n");

        int r = quantum_order_finding(N, a);

        printf("\n--- Post-processing for attempt %d ---\n", attempt);

        if (r <= 0) {
            printf("  r = %d (non-positive): order finding failed. Retrying...\n\n", r);
            continue;
        }
        if ((r % 2) == 1) {
            printf("  r = %d is odd: cannot use a^(r/2). Trying again\n\n", r);
            continue;
        }

        printf("  Order r = %d is even. Computing a^(r/2) mod N\n", r);
        int x = modexp_int(a, r / 2, N);
        printf("  a^(r/2) = %d^%d mod %d = %d\n", a, r / 2, N, x);

        if (x == 1) {
            printf("  a^(r/2) = 1 mod N gives trivial factors. Trying again\n\n");
            continue;
        }
        if (x == N - 1) {
            printf("  a^(r/2) = -1 mod N (%d) gives trivial factors. Trying again\n\n", x);
            continue;
        }

        printf("  Computing gcd(%d - 1, %d) = gcd(%d, %d)\n", x, N, x - 1, N);
        int p = gcd_int(x - 1, N);
        printf("  Computing gcd(%d + 1, %d) = gcd(%d, %d)\n", x, N, x + 1, N);
        int q_val = gcd_int(x + 1, N);
        printf("  Candidate factors: p = %d, q = %d\n", p, q_val);

        if (p > 1 && p < N) {
            printf("  -> Success! Nontrivial factor p = %d found (r = %d).\n\n", p, r);
            return p;
        }
        if (q_val > 1 && q_val < N) {
            printf("  -> Success! Nontrivial factor q = %d found (r = %d).\n\n", q_val, r);
            return q_val;
        }

        printf("  Neither candidate is a nontrivial factor. Trying again\n\n");
    }

    return 1;  /* failure */
}

/*==================== main ====================*/

int main(void) {

    int N;
    printf("Input N --> ");
    scanf("%d", &N);

    srand((unsigned int)time(NULL));

    printf("\nRunning Shor's algorithm simulator to factor N = %d\n\n", N);

    int p = shor_factor(N);

    printf("============================================================\n");
    if (p == 1 || p == N) {
        printf("Result: Failed to factor %d in the given attempts.\n", N);
    } else {
        int q = N / p;
        printf("Result: %d x %d = %d\n", p, q, N);
        printf("Verification: %d * %d = %d %s\n", p, q, p * q,
               (p * q == N) ? "Correct" : "ERROR");
    }
    printf("============================================================\n");

    return 0;
}