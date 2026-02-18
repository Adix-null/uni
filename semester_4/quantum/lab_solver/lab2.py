from sympy import Matrix, I, simplify, latex, Rational

from common import prettyPrint, lengthComplex, dotComplex

# 1.11
v1 = Matrix([-1 - 5 * I, -4 + 3 * I, -5 + I, -3 - 5 * I])
v2 = Matrix([-4 + I, - 4 - 3 * I, 3 - I, -3 + 2 * I])
v3 = Matrix([-1 - I, -1 - 4 * I, 2 - 2 * I, -4 + 4 * I])

A = Matrix.hstack(v1, v2, v3)

print('-' * 20)
print('1.11: ')

print(f"Input: {A}")
print(f"Rank: {A.rank()}")          # rank
print(f"Reduction: {A.rref()}")          # reduced row echelon form
print(f"Dependency: {A.nullspace()}")     # nontrivial solution => dependent

print('-' * 20 + '\n')

# 2.11
A = Matrix([
    [-7 + 7*I, 1 + 5*I],
    [6 + 8*I, -4 -6*I]
])
B = Matrix([
    [-4 - 9*I, -4 - 8*I],
    [-4 + 2*I, -8 + 3*I]
])
C = Matrix([
    [-9 - 8*I, -6 - 7*I],
    [-3 + 7*I, 4 + 4*I]
])

print('-' * 20)
print('2.11: ')

print(prettyPrint(latex(simplify(
    B**2 + (3*A.adjoint())*(C**(-2)) + (A**(-1)).adjoint()
))))

print('-' * 20 + '\n')

# 3.11
v1 = Matrix([
    [2 + 4*I],
    [-1 - 2*I],
    [-2 - 2*I]
])

v2 = Matrix([
    [4 + I],
    [-2 - 4*I],
    [1 - 3*I]
])

v3 = Matrix([
    [-3 - 5*I],
    [1 - 4*I],
    [-3 + 4*I]
])

v4 = Matrix([
    [-2 - 5*I],
    [1 - I],
    [2 - 2*I]
])

V = Matrix.hstack(v1, v2, v3)

print('-' * 20)
print('3.11: ')
print(prettyPrint(latex(simplify(
    V**(-1)*v4
))))

print('-' * 20 + '\n')

# 4.11

u1 = v1
u2 = v2 - ((dotComplex(v2, u1) / dotComplex(u1, u1)) * u1)
u3 = v3 - ((dotComplex(v3, u2) / dotComplex(u2, u2)) * u2) - ((dotComplex(v3, u1) / dotComplex(u1, u1)) * u1)

e1 = u1 / lengthComplex(u1)
e2 = u2 / lengthComplex(u2)
e3 = u3 / lengthComplex(u3)

print('-' * 20)
print('4.11: ')

print("e1: " + prettyPrint(latex(simplify(e1))))
print("e2: " + prettyPrint(latex(simplify(e2))))
# print("e3: " + prettyPrint(latex(simplify(e3))))

print('-' * 20 + '\n')

# 5.20
A = Matrix([
    [2*I, 5, 0],
    [2*I, 3, 0],
    [0, 0, -I]
])

print('-' * 20)
print('5.20: ')
print(prettyPrint(latex(
    A.eigenvects()
)))
print('-' * 20 + '\n')

# 6.1
H = Matrix([
    [0, 0, 1],
    [0, 1, 0],
    [1, 0, 0]
])

U = (1 / (2 * Rational(1,2))) * Matrix([
    [1, 1, 0],
    [-1, 1, 0],
    [0, 0, 2 ** Rational(1,2)]
])

print('-' * 20)
print('6.1: ')

print("X: " + prettyPrint(latex(simplify(
    A**(-1) * H
))))
print("Y: " + prettyPrint(latex(simplify(
    A**(-1) * U
))))

print('-' * 20 + '\n')