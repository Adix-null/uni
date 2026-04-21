import numpy as np
import random
import matplotlib.pyplot as plt
from math import gcd
from qiskit import QuantumCircuit, transpile
from qiskit.visualization import circuit_drawer, plot_histogram
from qiskit_aer import AerSimulator
from qiskit.circuit.library import QFTGate, UnitaryGate

def controlled_mul_mod_n_correct(n, a, power, n_qubits):
    multiplier = pow(a, 2 ** power, n)
    dim = 2 ** n_qubits

    matrix = np.zeros((dim, dim), dtype=complex)

    for x in range(dim):
        if x < n:
            y = (multiplier * x) % n
            matrix[y, x] = 1
        else:
            matrix[x, x] = 1

    gate = UnitaryGate(matrix, label=f"{a}^{2**power} mod {n}")
    return gate.control()

def controlled_mul_mod_n_simplified(n, a, power, n_qubits):
    qc = QuantumCircuit(n_qubits)

    for i in range(n_qubits):
        if (a * (2 ** i)) % n != (2 ** i) % n:
            qc.x(i)

    gate = qc.to_gate()
    gate.name = f"{a}^{power} mod {n}"
    return gate.control()

def quantum_phase_estimation(a, n, n_count, n_target):
    qc = QuantumCircuit(n_count + n_target, n_count)

    for q in range(n_count):
        qc.h(q)

    # target registras |1>
    qc.x(n_count)

    # CU
    for q in range(n_count):
        power = 2 ** q
        qc.append(
            controlled_mul_mod_n_simplified(n, a, power, n_target),
            [q] + [i + n_count for i in range(n_target)]
        )

    # atvirkščias QFT
    qc.append(QFTGate(n_count), range(n_count))

    qc.measure(range(n_count), range(n_count))
    return qc

def shor(n):
    if n % 2 == 0:
        return 2

    while True:
        a = random.randint(2, n - 2)
        g = gcd(a, n)
        if g > 1:
            return g

        n_target = int(np.ceil(np.log2(n)))
        n_count = n_target * 2

        qc = quantum_phase_estimation(a, n, n_count, n_target)

        simulator = AerSimulator()
        qc = transpile(qc, simulator)

        result = simulator.run(qc, shots=1024).result()
        counts = result.get_counts()

        measured = max(counts, key=counts.get)
        phase = int(measured, 2) / (2 ** n_count)

        if phase == 0:
            continue

        r = round(1 / phase)

        if r % 2 != 0:
            continue

        p = gcd(pow(a, r // 2, n) - 1, n)
        q = gcd(pow(a, r // 2, n) + 1, n)

        if p not in [1, n]:
            return p, n // p

# 2.4
N = 205
sol = shor(N)
print(f"N = {N}, p = {sol}, q = {N // sol}")