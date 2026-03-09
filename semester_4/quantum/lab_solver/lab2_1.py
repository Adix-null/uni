import random
from sympy import Matrix
from qiskit.visualization import plot_histogram, circuit_drawer
from qiskit.circuit.library import UnitaryGate
from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator
import matplotlib.pyplot as plt

question = None
if __name__ == "__main__":
    while question is None:
        question = input("Užduotis: ")

#region 1.22
if question == '1' or question == 0:
    def binary_op(a, b, op):
        n = len(a)

        x = int("".join(map(str, a)), 2)
        y = int("".join(map(str, b)), 2)

        result = op(x, y)

        mask = (1 << n) - 1
        result &= mask
        return [int(bit) for bit in format(result, f"0{n}b")]

    def f(a, b):
        return min(2*a, 3*b) % 11

    print('-' * 20)
    print('1.22: ')

    res = binary_op([0, 1, 1, 0], [0, 1, 0, 1], f)
    print(f"result: {res}")

    print('-' * 20 + '\n')
#endregion

#region D1 & D2
if question == 'D1' or question == 'D2' or question == 0:
    print('-' * 20)
    print('D1 & D2: ')

    inp_cnt = 4

    qc = QuantumCircuit(inp_cnt + 1, inp_cnt)

    for i in range(inp_cnt):
        qc.h(i)

    qc.x(inp_cnt)
    qc.h(inp_cnt)

    qc.cx(0, inp_cnt)
    # qc.cx(1, inp_cnt)
    qc.cx(2, inp_cnt)
    qc.cx(3, inp_cnt)

    for i in range(inp_cnt):
        qc.h(i)

    for i in range(inp_cnt):
        qc.measure(i, i)

    sim = AerSimulator()
    job = sim.run(qc, shots=10000)
    result = job.result()

    counts = result.get_counts()
    bal = sorted(counts.items(), key=lambda item: item[1])[0][0]

    print(f"D1: Ar bent viena funkcija subalansuota: {'Taip' if '1' in bal else 'Ne'}")
    print(f"D2: Ar visos funkcijos subalansuotos: {'Ne' if '0' in bal else 'Taip'}")

    # Draw the circuit
    circuit_drawer(qc, output="mpl")
    plt.show()

    # Plot the measurement results
    plot_histogram(counts)
    plt.show()

    print('-' * 20 + '\n')
#endregion

#region D3
if question == 'D3' or question == 0:
    print('-' * 20)
    print('D3: ')

    inp_cnt = 7

    qc = QuantumCircuit(inp_cnt + 1, inp_cnt)

    for i in range(inp_cnt):
        qc.h(i)

    qc.x(inp_cnt)
    qc.h(inp_cnt)

    qc.cx(0, inp_cnt)
    # qc.cx(1, inp_cnt)
    qc.cx(2, inp_cnt)
    qc.cx(3, inp_cnt)

    qc.cx(5, inp_cnt)

    for i in range(inp_cnt):
        qc.h(i)

    for i in range(inp_cnt):
        qc.measure(i, i)

    sim = AerSimulator()
    job = sim.run(qc, shots=10000)
    result = job.result()

    counts = result.get_counts()
    bal = sorted(counts.items(), key=lambda item: item[1])[0][0]

    print(f"Kiek funkcijų subalansuota: {bal.count('1')}")

    # Draw the circuit
    circuit_drawer(qc, output="mpl")  # uses matplotlib
    plt.show()

    # Plot the measurement results
    plot_histogram(counts)
    plt.show()

    print('-' * 20 + '\n')
#endregion

#region DJ1 & DJ2
def Uf(rule):
    size = len(rule)*2
    U = Matrix.zeros(size)

    if not is_dj_linear(rule):
        print("Funkcija netinkama")
        return U

    for x in range(len(rule)):
        fx = int(rule[x])

        for y in (0, 1):
            inp = (x << 1) | y # x1 x2 x3 x4 y
            out = (x << 1) | (y ^ fx) # x1 x2 x3 x4 (y xor fx)

            U[out, inp] = 1
    return U

def is_dj_linear(rule):
    n = 0
    L = len(rule)

    while 2 ** n < L:
        n += 1

    if all(c == '0' for c in rule) or all(c == '1' for c in rule):
        return True # konstanta

    zeros = rule.count('0')
    ones = rule.count('1')
    if zeros != ones:
        return False # Nebalansuotas

    return True

if question == 'DJ1' or question == 'DJ2' or question == 0:
    print('-' * 20)
    print('DJ1: ')

    function = '0000111111110000'

    inp_cnt = 4

    qc = QuantumCircuit(inp_cnt + 1, inp_cnt)

    for i in range(inp_cnt):
        qc.h(i)

    qc.x(inp_cnt)
    qc.h(inp_cnt)

    oracle = UnitaryGate(Uf(function))
    qc.append(oracle, [4, 3, 2, 1, 0])

    for i in range(inp_cnt):
        qc.h(i)

    for i in range(inp_cnt):
        qc.measure(i, i)

    sim = AerSimulator()
    job = sim.run(qc, shots=10000)
    result = job.result()

    counts = result.get_counts()

    # Draw the circuit
    circuit_drawer(qc, output="mpl")
    plt.show()

    # Plot the measurement results
    plot_histogram(counts)
    plt.show()

    print('-' * 20 + '\n')
#endregion

#region BV 1
def truth_table(secret):
    n = len(secret)
    table = []

    for i in range(2 ** n):
        x_bits = [(i >> j) & 1 for j in reversed(range(n))]
        fx = sum(int(bx) * int(bs) for bx, bs in zip(x_bits, secret)) % 2
        table.append(fx)

    return table

if question == 'BV1' or question == 0:

    print('-' * 20)
    print('BV1: ')

    s = [0, 0, 0, 1, 0, 0]
    table = truth_table(s)

    for i, e in enumerate(table):
        print(f"{i:0{len(s)}b} -> {e}")

    print('-' * 20 + '\n')
# endregion

#region BV 2
if question == 'BV2' or question == 0:
    n = None
    while n is None or n < 0:
        try:
            n = int(input("n = "))
        except ValueError:
            print("n turi būti natūralus skaičius")

    print('-' * 20)
    print('BV2: ')

    s = [random.randint(0, 1) for i in range(n)]
    table = truth_table(s)

    print(f"Atsitiktinis s: {s}")
    for i, e in enumerate(table):
        print(f"{i:0{len(s)}b} -> {e}")

    print('-' * 20 + '\n')
# endregion

#region BV 3
if question == 'BV3' or question == 0:
    def IsBV(truth_table):
        n = (len(truth_table)).bit_length() - 1
        c = truth_table[0]
        s = []

        for i in range(n):
            ei = 1 << i
            si = truth_table[ei] ^ c
            s.append(si)

        for x in range(len(truth_table)):
            fx = truth_table[x]
            dot = sum(((x >> i) & 1) * s[i] for i in range(n)) % 2
            if fx != (c ^ dot):
                return False, None

        return True, s

    n = None
    while n is None or n < 0:
        try:
            n = int(input("n = "))
        except ValueError:
            print("n turi būti natūralus skaičius")

    function = [random.randint(0, 1) for i in range(2**n)]

    print('-' * 20)
    print('BV3: ')

    table = truth_table(function)

    # function = [0,1,0,1,1,0,1,0]
    is_bv, secret = IsBV(function)
    print(f"Ar funkcija BV: {'Taip' if is_bv else 'Ne'}")
    if is_bv:
        print(f"s: {secret}")

    print('-' * 20 + '\n')
# endregion
