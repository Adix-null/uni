from sympy import Matrix, I, simplify, latex, Rational, eye, sqrt, Abs, N, symbols, exp, pi
from sympy.physics.quantum import TensorProduct
from qiskit.visualization import plot_histogram, circuit_drawer
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

#region DJ1
if question == 'DJ1' or question == 0:
    print('-' * 20)
    print('DJ1: ')


    print('-' * 20 + '\n')
#endregion