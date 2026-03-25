from sympy import Matrix, I, simplify, latex, Rational, eye, sqrt, Abs, N, symbols, exp, pi
from sympy.physics.quantum import TensorProduct

from common import *

question = None
if __name__ == "__main__":
    while question is None:
        try:
            question = int(input("Užduotis: "))
        except ValueError:
            print("Pasirinkimas turi būti sveikas skaičius")

#region 1
if question == 1 or question == 0:
    print('-' * 20)
    print('1: ')

    n = None
    while n is None and n != 2 and n != 4:
        try:
            n = int(input("Omega dydis n (2 arba 4) = "))
        except ValueError:
            print("n turi būti 2 arba 4")

    psi_2 = Matrix([
        [-7 + 3*I],
        [4 + 9*I]
    ])
    psi_4 = Matrix([
        [-1 + 2*I],
        [6*I],
        [-8 + I],
        [2 + 4*I]
    ])
    Omega_2 = Matrix([
        [1, 2 - I],
        [2 + I, 3]
    ])
    Omega_4 = Matrix([
        [3, -I, 4 + 3*I, 0],
        [I, 0, -2, -1 - 4*I],
        [4 - 3*I, -2, -5, -2 + 3*I],
        [0, -1 + 4*I, -2 - 3*I, 1]
    ])
    psi_2 = normalize(psi_2)
    psi_4 = normalize(psi_4)

    if n == 2:
        print('Vidurkis: ')
        print(prettyPrint(latex(simplify(
            psi_2.conjugate().T * Omega_2 * psi_2
        ))))
        print('Variacija: ')
        print(prettyPrint(latex(simplify(
            (psi_2.conjugate().T * (Omega_2**2) * psi_2) -
            (psi_2.conjugate().T * Omega_2 * psi_2)**2
        ))))

    if n == 4:
        print('Vidurkis: ')
        print(prettyPrint(latex(simplify(
            psi_4.conjugate().T * (Omega_4**2) * psi_4
        ))))
        print('Variacija: ')
        print(prettyPrint(latex(simplify(
            (psi_4.conjugate().T * (Omega_4 ** 2) * psi_4) -
            (psi_4.conjugate().T * Omega_4 * psi_4) ** 2
        ))))

    print('-' * 20 + '\n')
# endregion

#region 2
if question == 2 or question == 0:
    print('-' * 20)
    print('2: ')

    psi = Matrix([
        [-1 + 2 * I],
        [6 * I],
        [-8 + I],
        [2 + 4 * I]
    ])

    t = None
    while t is None or t < 0:
        try:
            t = int(input("T = "))
        except ValueError:
            print("T turi būti teigiamas sveikas skaičius")

    U = Rational(1 , 2) * Matrix([
        [1, 1, 1, 1],
        [1, -1, exp(I * t), -exp(I * t)],
        [1, 1, -1, -1],
        [1, -1, -exp(I * t), exp(I * t)]
    ])

    print(f'Būsena po T={t}: ')
    print(prettyPrint(latex(simplify(
        (U**t) * psi
    ))))

    print('-' * 20 + '\n')
# endregion

#region 3
def Control(M):
    N = M.rows
    C = eye(2 * N)

    for i in range(N):
        for j in range(N):
            C[N + i, N + j] = M[i, j]
    return C

I2 = eye(2)
H = (1 / 2**Rational(1 , 2)) *  Matrix([
    [1, 1],
    [1, -1],
])
Y = Matrix([
    [0, -I],
    [I, 0]
])
Z = Matrix([
    [1, 0],
    [0, -1]
])
T = Matrix([
    [1, 0],
    [0, exp(I * (pi / 4))]
])
X = Matrix([
    [0, 1],
    [1, 0]
])
CU = Control(I2)
SWAP = Matrix([
    [1, 0, 0, 0],
    [0, 0, 1, 0],
    [0, 1, 0, 0],
    [0, 0, 0, 1]
])

CX_01 = Control(X)
CX_10 = SWAP * CX_01 * SWAP

C = None

def P(p):
    return Matrix([
        [1, 0],
        [0, exp(I * p)]
    ])

#endregion

#region 4
if question == 4 or question == 0:
    print('-' * 20)
    print('4: ')

    x_1, x_2 = symbols('x_1 x_2')
    q = Matrix([
        [x_1],
        [x_2]
    ])

    row = [H, Y, Z, T, H, X]
    state = q
    for op in reversed(row):
        state = op * state

    print(f'q galutinė būsena: ')
    print(prettyPrint(latex(simplify(
        state
    ))))

    print('-' * 20 + '\n')
#endregion

#region 5 & 6


if question == 5 or question == 6 or question == 0:
    print('-' * 20)
    print('5 & 6: ')

    x_01, x_02, x_11, x_12 = symbols('x_01 x_02 x_11 x_12')
    q0 = Matrix([
        [x_01],
        [x_02]
    ])
    q1 = Matrix([
        [x_11],
        [x_12]
    ])
    state = TensorProduct(q0, q1)
    U = eye(4)

    row_q0 = [H, C, Y, I2, H, I2]
    row_q1 = [H, I2, Z, H, H, C]

    for i in range(len(row_q0)):
        g0 = row_q0[i]
        g1 = row_q1[i]

        # controlled gate check
        if g0 == C:
            # q0 controls q1
            if g1 == I2:
                op = CX_01
            else:
                raise Exception("C has to be in pair with I")
        elif g1 == C:
            # q1 controls q0
            if g0 == I2:
                op = CX_10
            else:
                raise Exception("C has to be in pair with I")
        else:
            # normal case
            op = TensorProduct(g0, g1)

        U = op * U
        state = op * state

    print(f'5. q galutinė būsena: ')
    print(prettyPrint(latex(simplify(
        state
    ))))
    print(f'6. Viso tinklo operatorius: ')
    print(prettyPrint(latex(simplify(
        U
    ))))

    print('-' * 20 + '\n')
#endregion
