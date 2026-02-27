import random
random.seed()
from sympy import Matrix, I, simplify, latex, Rational, eye, sqrt, Abs, N, symbols
import numpy as np

from common import *

question = None
while question is None:
    try:
        question = int(input("Užduotis: "))
    except ValueError:
        print("Pasirinkimas turi būti sveikas skaičius")

M = Matrix([
    [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 1, 0, 0, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
    [0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 1, 0, 0]
])

#region 1.2
if question == 1 or question == 0:
    print('-' * 20)
    print('1.2: ')

    k = None
    while k is None:
        try:
            k = int(input("k = "))
        except ValueError:
            print("k turi būti sveikas skaičius")

    print("M po k žingsnių: ")
    print(prettyPrint(latex(simplify(
        M**k
    ))))
    showMatrixGraph(M)
    print('-' * 20 + '\n')
#endregion

#region 2
def randMatrix(N):
    # N eilės I generavimas
    M = eye(N)

    if N == 2:
        return Matrix([[Rational(1,2), Rational(1,2)],
                       [Rational(1,2), Rational(1,2)]])

    zeros_exist = True
    while zeros_exist:
        zeros = [(x, y) for x in range(N) for y in range(N) if M[x,y] == 0]
        if not zeros:
            break

        x, y = random.choice(zeros)  # atsitiktinis 0

        # Artimiausias ne 0 nuo pozicijos eilutėje
        row_val = None
        j_closest = None
        for j in range(N):
            if j == y:
                continue
            if M[x, j] != 0:
                if row_val is None or abs(j - y) < abs(j_closest - y):
                    j_closest = j
                    row_val = M[x, j]
        if row_val is None:
            continue  # ne 0 nerasta

        # Artimiausias ne 0 nuo pozicijos stulpelyje
        col_val = None
        i_closest = None
        for i in range(N):
            if i == x:
                continue
            if M[i, y] != 0:
                if col_val is None or abs(i - x) < abs(i_closest - x):
                    i_closest = i
                    col_val = M[i, y]
        if col_val is None:
            continue  # ne 0 nerasta

        # persvara kitiems 2 kampams
        min_delta = min(row_val / 2, col_val / 2)

        M[x, y] += min_delta
        M[x, j_closest] -= min_delta
        M[i_closest, y] -= min_delta
        M[i_closest, j_closest] += min_delta

    return M

def isMatrix2Stochastic(M):
    for i in range(N):
        if sum(M.row(i)) != 1 or sum(M.col(i)) != 1 :
            return False
    return True

if question == 2 or question == 0:
    print('-' * 20)
    print('2: ')

    N = None
    while N is None or N < 1:
        try:
            N = int(input("N = "))
        except ValueError:
            print("N turi būti natūralus skaičius")

    k = None
    while k is None:
        try:
            k = int(input("k = "))
        except ValueError:
            print("k turi būti sveikas skaičius")

    print("Atsitiktinė dvigubai stohastinė matrica: ")
    R = randMatrix(N)
    print(prettyPrint(latex(simplify(
        R
    ))))
    print(f"Ar matrica yra dvigubai stochastinė: {'Taip' if isMatrix2Stochastic(R) else 'Ne'}")
    print("Sistema po k žingsnių: ")
    print(prettyPrint(latex(simplify(
        R**k
    ))))
    showMatrixGraph(R)
    print('-' * 20 + '\n')
#endregion

#region 3
def column_Gram_Schmidt(M):
    N = M.cols
    U = M.copy()

    norm0 = sqrt(sum(Abs(U[i, 0]) ** 2 for i in range(U.rows)))
    U[:, 0] = U[:, 0] / norm0

    for k in range(1, N):
        v = U[:, k]
        u0 = U[:, 0]
        proj = sum((v[i] * u0[i].conjugate()) for i in range(U.rows))
        v = v - proj * u0
        norm = sqrt(sum(Abs(v[i]) ** 2 for i in range(U.rows)))
        if norm != 0:
            U[:, k] = v / norm
        else:
            # if the column became zero, just leave it as zero
            U[:, k] = v

    return U

def randComplexStateMatrix(N):
    M = Matrix.zeros(N)
    for i in range(M.rows):
        non_zero_indices = []
        for j in range(N):
            # atsistiktinis kiekis 0
            if j == 0 or random.random() < Rational(1, random.randint(1, N)):
                non_zero_indices.append(j)

        sqMag = 0
        for j in non_zero_indices:
            x = random.randint(1, N*5)
            y = random.randint(1, N*5)
            z = Rational(1, min(x, y)) + I*Rational(1, max(x, y))
            M[j,i] = simplify(z)
            sqMag += Abs(z)**2

        # normalizavimas
        norm = sqrt(sqMag)
        for j in non_zero_indices:
            M[j,i] /= norm

    return column_Gram_Schmidt(M)

def isComplexStateMatrix(M):
    for i in range(M.rows):
        colSum = 0
        for j in range(M.cols):
            colSum += Abs(M[j, i]) ** 2
        if colSum != 1:
            return False
    return True

def probabilityOfState(M, start, end, time):
    x_0 = Matrix.zeros(M.cols, 1)
    x_0[start - 1] = 1

    amplitude = (M ** time * x_0)[end - 1]
    probability = Abs(amplitude) ** 2
    return probability.evalf()


if question == 3 or question == 0:
    print('-' * 20)
    print('3: ')

    N = None
    while N is None or N < 1:
        try:
            N = int(input("N = "))
        except ValueError:
            print("N turi būti natūralus skaičius")

    k = None
    while k is None:
        try:
            k = int(input("k = "))
        except ValueError:
            print("k turi būti sveikas skaičius")

    i = 2
    j = 4
    T = 4

    print("Atsitiktinė kvantinės sistemos matrica: ")
    R = randComplexStateMatrix(N)
    print(prettyPrint(latex(simplify(
        R
    ))))
    print(f"Ar matrica yra kvantinės sistemos dinaminė: {'Taip' if isComplexStateMatrix(R) else 'Ne'}")
    print("Sistema po k žingsnių: ")
    print(prettyPrint(latex(simplify(
        R**k
    ))))
    print(f"Tikimybė pereiti nuo būsenos {i} į būseną {j} per T={T}: {(probabilityOfState(R, i, j, T) * 100):.2f}%")
    showMatrixGraph(R)

    print('-' * 20 + '\n')
#endregion

#region 5.9
if question == 5 or question == 0:
    print('-' * 20)
    print('5.9: ')
    psi = Matrix([
        7 + 5*I,
        -1 - 3*I,
        6*I,
        -5 + 2*I,
        4 - 7*I,
        6 - 8*I,
        -1 + 7*I,
        -7 - 8*I
    ])
    phi = Matrix([
        7 + 3*I,
        -6 - 7*I,
        5 + 5*I,
        -4 - I,
        -6 - 3*I,
        3 - 6*I,
        -6 + 5*I,
        -8 - 2*I
    ])
    psi /= (psi.conjugate().T * psi)[0]
    phi /= (phi.conjugate().T * phi)[0]
    print("Tranzicijos amplitudė: ")
    print(prettyPrint(latex(simplify(
        (phi.conjugate().T * psi)[0]
    ))))
    print('-' * 20 + '\n')
#endregion

#region 6
def commutate(A, B):
    return A * B - B * A

gamma, xi, tau = symbols('gamma xi tau')
a, b, c, d = symbols('a b c d')

A = Matrix([
    [xi, 7, tau],
    [a, b, 9],
    [0, tau, -2],
])

B = Matrix([
    [gamma, 37, d],
    [1, d, 0],
    [xi, c, a],
])

if question == 6 or question == 0:
    print('-' * 20)
    print('6: ')
    print(prettyPrint(latex(simplify(
        commutate(A, B)
    ))))
    print('-' * 20 + '\n')
#endregion
