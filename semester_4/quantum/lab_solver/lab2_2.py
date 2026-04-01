import random
import sympy as sp
from qiskit.visualization import plot_histogram, circuit_drawer
from qiskit import QuantumCircuit, QuantumRegister, ClassicalRegister
from qiskit_aer import AerSimulator
import matplotlib.pyplot as plt

question = None
if __name__ == "__main__":
    while question is None:
        question = input("Užduotis: ")

#region SA.22
def xor_bits(a, b):
    return ''.join(str(int(x) ^ int(y)) for x, y in zip(a, b))

def build_simon_table(s: str):
    n = len(s)

    # gaunamos visos {0, 1}^n x kombinacijos
    all_x = [format(i, f'0{n}b') for i in range(2 ** n)]
    used_outputs = set()
    f = {}

    i = 0
    while i < len(all_x):
        x = all_x[i]

        if x in f:
            i += 1
            continue

        x2 = xor_bits(x, s)

        # pasirenkama nenaudota atsitiktinė n bitų reikšmė
        while True:
            fx = ''.join(str(random.randint(0, 1)) for _ in range(n))
            if fx not in used_outputs:
                break

        used_outputs.add(fx)

        f[x] = fx
        f[x2] = fx

        i += 1

    return [f[x] for x in all_x]

def anf_terms(f: str):
    n = (len(f)).bit_length() - 1
    a = [int(bit) for bit in f]

    # Žegalkino polinomas
    for i in range(n):
        step = 1 << i
        for mask in range(len(a)):
            if mask & step:
                a[mask] ^= a[mask ^ step]

    return [format(i, f'0{n}b') for i, v in enumerate(a) if v == 1]

def solve_simon(counts, n):
    ys = [list(map(int, y[::-1])) for y in counts.keys()]

    A = ys[:]

    # surandams vektoriųs su kuriuo y * s = 0 (mod 2)
    for i in range(1, 1 << n):
        v = [(i >> j) & 1 for j in range(n)]

        ok = True
        for eq in A:
            if sum(x & y for x, y in zip(v, eq)) % 2 != 0:
                ok = False
                break

        if ok:
            return ''.join(map(str, v))

    return None

if question == 'SA' or question == 0:
    s_hidden = "11011"
    n = len(s_hidden)

    table = build_simon_table(s_hidden)
    print(f"f(x) reikšmės: {table}")

    transposed = ["".join(column) for column in zip(*table)]

    qr_x = QuantumRegister(n, "x")
    qr_y = QuantumRegister(n, "y")
    cr = ClassicalRegister(n, "c")

    qc = QuantumCircuit(qr_x, qr_y, cr)

    # H vartai 1
    qc.h(qr_x)

    # Orakula iš Žegalkino polinomų narių
    for j, f_column in enumerate(transposed):
        anf = anf_terms(f_column)

        for term in anf:
            control_bits = [i for i, bit in enumerate(term) if bit == "1"]

            if not control_bits:
                # Jei termas {0}^n, tiesiog X vartas taikiniui
                qc.x(qr_y[j])
            elif len(control_bits) == 1:
                # Jei tik vienas kontroliuoja, užtenka CNOT
                qc.cx(qr_x[control_bits[0]], qr_y[j])
            else:
                # k kontrolės bitai valdo taikinį su (C*k)NOT
                qc.mcx([qr_x[i] for i in control_bits], qr_y[j])

    # H vartai 2
    qc.h(qr_x)

    qc.measure(qr_x, cr)

    sim = AerSimulator()
    result = sim.run(qc, shots=1024).result()
    counts = result.get_counts()

    # Draw the circuit
    circuit_drawer(qc, output="mpl")
    plt.show()

    # Plot the measurement results
    plot_histogram(counts)
    plt.show()

    print(f"Išmatuotos tinkamos reikšmės: {counts.keys()}")

    s_recovered = solve_simon(counts, n)
    print(f"Atgauta s = {s_recovered}, {'sutampa' if s_recovered == s_hidden else 'nesutampa'}")