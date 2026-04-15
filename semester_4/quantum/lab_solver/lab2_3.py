import random
import sympy as sp
from qiskit.visualization import plot_histogram, circuit_drawer
from qiskit import QuantumCircuit, QuantumRegister, ClassicalRegister
from qiskit_aer import AerSimulator
from qiskit.circuit.library import RGQFTMultiplier, IntegerComparator
import matplotlib.pyplot as plt

question = None
if __name__ == "__main__":
    while question is None:
        question = input("Užduotis: ")

#region GrA.22

def encode_state(a, b, c, d, e):
    return format(a, "03b") + format(b, "03b") + format(c, "02b") + format(d, "02b") + format(e, "02b")

def check_solution(a, b, c, d, e):
    return (2 * (a + b + c + d + e)) % 11 == ((a + 1) ** 3) % 11

def add(qc, x, y):
    n = len(y)

    for i in range(n):
        if i < len(x):
            qc.cx(x[i], y[i])
        if 0 < i < len(x):
            qc.ccx(x[i], y[i], y[i-1])

    for i in reversed(range(n)):
        if 0 < i < len(x):
            qc.ccx(x[i], y[i], y[i-1])
        if i < len(x):
            qc.cx(x[i], y[i])

def add_constant(qc, k, reg):
    for i in range(len(reg)):
        if (k >> i) & 1:
            qc.x(reg[i])

def add_dagger(qc, x, y):
    n = len(y)

    for i in range(n):
        if i < len(x):
            qc.cx(x[i], y[i])
        if i > 0:
            qc.ccx(x[i], y[i], y[i-1])

    for i in reversed(range(n)):
        if i > 0:
            qc.ccx(x[i], y[i], y[i-1])
        if i < len(x):
            qc.cx(x[i], y[i])

def subtract_const(qc, x, k_bits):
    n = len(x)

    for i in range(n):
        if (k_bits >> i) & 1:
            qc.cx(x[i], x[i])

def mul2(qc, reg):
    n = len(reg)

    for i in range(n - 1):
        qc.swap(reg[i], reg[i+1])

def mul2_dagger(qc, reg):
    n = len(reg)

    for i in reversed(range(n - 1)):
        qc.swap(reg[i], reg[i+1])

def mul(qc, a, b, res):
    n = len(a)

    for i in range(len(b)):
        for j in range(n):
            if j + i < len(res):
                qc.ccx(b[i], a[j], res[j+i])

def mul_dagger(qc, a, b, res):
    n = len(a)

    for i in reversed(range(len(b))):
        for j in reversed(range(n)):
            if j + i < len(res):
                qc.ccx(b[i], a[j], res[j+i])

def mod_k(qc, x, k, flag):
    n = len(x)

    # compute flag (>=k check)
    for i in reversed(range(n)):
        if (k >> i) & 1:
            qc.cx(x[i], flag[0])

    # conditional subtraction
    for i in range(n):
        if (k >> i) & 1:
            qc.cx(flag[0], x[i])

def mod_k_dagger(qc, x, k, flag):
    n = len(x)

    for i in reversed(range(n)):
        if (k >> i) & 1:
            qc.cx(x[i], flag[0])

    for i in range(n):
        if (k >> i) & 1:
            qc.cx(flag[0], x[i])

def equal(qc, a, b, flag, diff):
    n = len(a)

    for i in range(n):
        qc.cx(a[i], diff[i])
        qc.cx(b[i], diff[i])

    for i in range(n):
        qc.x(diff[i])

    qc.mcx(diff, flag[0])

    for i in range(n):
        qc.x(diff[i])

def equal_dagger(qc, a, b, flag, diff):
    n = len(a)

    for i in range(n):
        qc.x(diff[i])

    qc.mcx(diff, flag[0])

    for i in range(n):
        qc.x(diff[i])

    for i in range(n):
        qc.cx(b[i], diff[i])
        qc.cx(a[i], diff[i])

def oracle(qc, a, b, c, d, e, left, right, tmp1, tmp2, flag, diff):
    # left
    add(qc, a, left)
    add(qc, b, left)
    add(qc, c, left)
    add(qc, d, left)
    add(qc, e, left)

    mul2(qc, left)

    mod_k(qc,left,11,flag)

    # right
    add(qc, a, right)
    add_constant(qc, 1, right)

    mul(qc,right,right,tmp1)
    mul(qc,tmp1,right,tmp2)

    mod_k(qc,tmp2,11,flag)

    for i in range(len(right)):
        qc.cx(tmp2[i],right[i])

    # compare
    equal(qc,left,right,flag,diff)
    qc.z(flag[0])
    equal_dagger(qc,left,right,flag,diff)

    # uncompare
    equal_dagger(qc, left, right, flag, diff)

    # uncompute right
    for i in range(len(right)):
        qc.cx(tmp2[i], right[i])

    mod_k_dagger(qc, tmp2, 11, flag)

    mul_dagger(qc, right, tmp1, tmp2)
    mul_dagger(qc, right, right, tmp1)

    add_constant(qc, 1, right)
    add_dagger(qc, a, right)

    # uncompute left
    mod_k_dagger(qc,left,11,flag)
    mul2_dagger(qc,left)

    add_dagger(qc,e,left)
    add_dagger(qc,d,left)
    add_dagger(qc,c,left)
    add_dagger(qc,b,left)
    add_dagger(qc,a,left)

def diffusion(qc, qubits):
    qc.h(qubits)
    qc.x(qubits)

    qc.h(qubits[-1])
    qc.mcx(qubits[:-1], qubits[-1])
    qc.h(qubits[-1])

    qc.x(qubits)
    qc.h(qubits)

if question == 'GA' or question == 0:
    a = QuantumRegister(3, 'a')
    b = QuantumRegister(3, 'b')
    c = QuantumRegister(3, 'c')
    d = QuantumRegister(3, 'd')
    e = QuantumRegister(3, 'e')

    left = QuantumRegister(4, 'left')
    right = QuantumRegister(4, 'right')
    tmp1 = QuantumRegister(4, 'tmp1')
    tmp2 = QuantumRegister(4, 'tmp2')
    flag = QuantumRegister(1, 'flag')
    diff = QuantumRegister(12, 'diff')

    cl = ClassicalRegister(12, 'cl')

    qc = QuantumCircuit(
        a, b, c, d, e,
        left, right, tmp1, tmp2,
        flag, diff,
        cl
    )

    qc.initialize([1, 0], c[2])
    qc.initialize([1, 0], d[2])
    qc.initialize([1, 0], e[2])

    var_qubits = list(a) + list(b) + list(c) + list(d) + list(e)
    qc.h(var_qubits)

    iterations = 16

    for _ in range(iterations):
        oracle(qc, a, b, c, d, e, left, right, tmp1, tmp2, flag, diff)
        diffusion(qc, var_qubits)

    qc.measure(var_qubits, cl)

    sim = AerSimulator()
    result = sim.run(qc, shots=1024).result()
    counts = result.get_counts()

    plot_histogram(counts)
    plt.show()




