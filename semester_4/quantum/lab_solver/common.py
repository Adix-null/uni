from sympy import Matrix,  Rational
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

def dotComplex(x, y):
    x = Matrix(x)
    y = Matrix(y)

    return (x.T * y.conjugate())[0]

def lengthComplex(z):
    return (dotComplex(z,z)) ** Rational(1,2)
