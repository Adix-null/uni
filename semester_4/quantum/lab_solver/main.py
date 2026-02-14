from sympy import Matrix, I, simplify, latex, Rational, symbols, solve
import re

def prettyPrint(inp):
    inp = inp.replace('\\begin{matrix}', '\\begin{bmatrix}\n')
    inp = inp.replace('\\end{matrix}', '\n\\end{bmatrix}')
    inp = inp.replace('\\left', '')
    inp = inp.replace('\\right', '')
    inp = inp.replace('[', '')
    inp = inp.replace(']', '')
    # inp = inp.replace('- \\frac', '-\\frac')
    pattern = r'\\frac\{(\d+)\s*i\}\{(\d+)\}'
    inp = re.sub(pattern, r'i\\frac{\1}{\2}', inp)
    inp = inp.replace('\\\\', ' \\\\\n')
    return inp
# 1.11

# v1 = Matrix([-1 - 5 * I, -4 + 3 * I, -5 + I, -3 - 5 * I])
# v2 = Matrix([-4 + I, - 4 - 3 * I, 3 - I, -3 + 2 * I])
# v3 = Matrix([-1 - I, -1 - 4 * I, 2 - 2 * I, -4 + 4 * I])
#
# A = Matrix.hstack(v1, v2, v3)
#
# print(f"Input: {A}")
# print(f"Rank: {A.rank()}")          # rank
# print(f"Reduction: {A.rref()}")          # reduced row echelon form
# print(f"Dependency: {A.nullspace()}")     # nontrivial solution ⇒ dependent

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

# print(f"Result: {simplify(B**2 + (3*A.adjoint())*(C**(-2)) + (A**(-1)).adjoint())}")

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

# 4.11
def dotComplex(x, y):
    x = Matrix(x)
    y = Matrix(y)

    return (x.T * y.conjugate())[0]

def lengthComplex(z):
    return (dotComplex(z,z)) ** Rational(1,2)

u1 = v1
u2 = v2 - ((dotComplex(v2, u1) / dotComplex(u1, u1)) * u1)
u3 = v3 - ((dotComplex(v3, u2) / dotComplex(u2, u2)) * u2) - ((dotComplex(v3, u1) / dotComplex(u1, u1)) * u1)

e1 = u1 / lengthComplex(u1)
e2 = u2 / lengthComplex(u2)
e3 = u3 / lengthComplex(u3)

a = Matrix([
    [4, -1],
    [2, 1]
])
b = Matrix([
    [2],
    [3]
])

# 5.20
M = Matrix([
    [2*I, 5, 0],
    [2*I, 3, 0],
    [0, 0, -I]
])
AI = Matrix([
    [0, 0, 1],
    [0, 1, 0],
    [1, 0, 0]
])

lambda_ = symbols('lambda')
eq = (2*I - lambda_)*(3 - lambda_) - 10*I
sols = solve(eq, lambda_)
# print(prettyPrint((M.eigenvects())))

# 6.1
U = (1 / (2 * Rational(1,2))) * Matrix([
    [1, 1, 0],
    [-1, 1, 0],
    [0, 0, 2 ** Rational(1,2)]
])


print(prettyPrint(latex(simplify(
    M**(-1) * U
))))