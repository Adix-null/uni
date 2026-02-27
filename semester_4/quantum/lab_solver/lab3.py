import random
random.seed()
from sympy import Matrix, I, simplify, latex, Rational, eye

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
    for i in range(M.rows):
        if sum(M.row(i)) != 1:
            return False
    for i in range(M.cols):
        if sum(M.col(i)) != 1:
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
    print(f"Ar matrica yra dvigubai stochastinė: {'Taip' if isMatrix2Stochastic(M) else 'Ne'}")
    print("Sistema po k žingsnių: ")
    print(prettyPrint(latex(simplify(
        R**k
    ))))
    showMatrixGraph(R)
    print('-' * 20 + '\n')
#endregion

#region 3
if question == 3 or question == 0:
    print('-' * 20)
    print('3: ')

    print('-' * 20 + '\n')
#endregion

