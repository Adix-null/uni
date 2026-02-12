from sympy import Matrix, I, simplify

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

B_squared = simplify(B**2)
print(f"Squared B: {B_squared}")