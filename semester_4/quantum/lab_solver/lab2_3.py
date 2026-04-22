import numpy as np
from qiskit import QuantumCircuit, transpile
from qiskit.circuit.library import DiagonalGate
from qiskit.circuit.library import grover_operator
from qiskit.visualization import circuit_drawer, plot_histogram
from qiskit_aer import AerSimulator
import matplotlib.pyplot as plt


def is_solution(a, b, c, d, e):
    left_side = (2 * (a + b + c + d + e)) % 11
    right_side = ((a + 1) ** 3) % 11
    return left_side == right_side


def build_oracle(num_qubits):
    oracle_matrix = np.ones(2 ** num_qubits)

    for i in range(2 ** num_qubits):
        a = (i >> 0) & 0b111
        b = (i >> 3) & 0b111
        c = (i >> 6) & 0b11
        d = (i >> 8) & 0b11
        e = (i >> 10) & 0b11

        if is_solution(a, b, c, d, e):
            oracle_matrix[i] = -1  # phase flip correct solution

    diag_gate = DiagonalGate(oracle_matrix)
    oracle_qc = QuantumCircuit(num_qubits)
    oracle_qc.append(diag_gate, range(num_qubits))
    return oracle_qc

num_vars_qubits = 12
oracle_circ = build_oracle(num_vars_qubits)
grover_op = grover_operator(oracle_circ)

qc = QuantumCircuit(num_vars_qubits)
qc.h(range(num_vars_qubits))

iterations = 4
for _ in range(iterations):
    qc.append(grover_op, range(num_vars_qubits))

qc.measure_all()

sim = AerSimulator()
t_qc = transpile(qc, sim)
result = sim.run(t_qc, shots=5000).result()
counts = result.get_counts()

circuit_drawer(qc, output="mpl")
plt.show()

plot_histogram(counts)
plt.show()

sorted_counts = sorted(counts.items(), key=lambda x: x[1], reverse=True)

print(f"{'a b c d e':<15} | {'count':<8} | {'function check'}")
print("-" * 40)

for bitstring, count in sorted_counts[:50]:
    val = int(bitstring, 2)
    a = (val >> 0) & 0b111
    b = (val >> 3) & 0b111
    c = (val >> 6) & 0b11
    d = (val >> 8) & 0b11
    e = (val >> 10) & 0b11

    valid = is_solution(a, b, c, d, e)
    print(f"{a} {b} {c} {d} {e:<6}  | {count:<8} | {valid}")