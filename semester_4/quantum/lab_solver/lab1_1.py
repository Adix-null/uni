from sympy import I, latex, symbols, solve, nroots

from common import prettyPrint

# 5.9

n = 8
z = -1 - I

w = symbols('w')
sol = solve(w ** n - z, w)  # exact radical form
# sol = nroots(w ** n - z)

print('-' * 20)
print('5.9: ')
print(prettyPrint(latex((
    sol
))))
print('-' * 20 + '\n')