import matplotlib.pyplot as plt
from qiskit import QuantumCircuit, QuantumRegister, ClassicalRegister, transpile
from qiskit_aer import AerSimulator

def encode_state(a, b, c, d, e):
    return format(a, "03b") + format(b, "03b") + format(c, "02b") + format(d, "02b") + format(e, "02b")

def check_solution(a, b, c, d, e):
    return (2 * (a + b + c + d + e)) % 11 == ((a + 1) ** 3) % 11

def all_solutions():
    sols = []
    for a in range(4):
        for b in range(4):
            for c in range(4):
                for d in range(4):
                    for e in range(4):
                        if check_solution(a, b, c, d, e):
                            sols.append((a, b, c, d, e))
    return sols

def add_fixed(qc, a, b, res):
    for i in range(len(a)):
        for j in range(len(b)):
            if i + j < len(res):
                qc.ccx(a[i], b[j], res[i + j])


def oracle(qc, a, b, c, d, e, left, right, tmp_sq, anc_copy, flag):
    for reg in [a, b, c, d, e]:
        for i in range(len(reg)):
            qc.cx(reg[i], left[i])

    for i in range(len(a)):
        qc.cx(a[i], right[i])
    qc.ccx(right[0], right[1], right[2])
    qc.cx(right[0], right[1])
    qc.x(right[0])

    for i in range(len(right)):
        qc.cx(right[i], anc_copy[i])

    for i in range(len(right)):
        for j in range(len(anc_copy)):
            if i + j < len(tmp_sq):
                qc.ccx(right[i], anc_copy[j], tmp_sq[i + j])

    qc.x(flag)
    qc.h(flag)
    qc.mcx(tmp_sq, flag)
    qc.h(flag)
    qc.x(flag)

    for i in reversed(range(len(right))):
        for j in reversed(range(len(anc_copy))):
            if i + j < len(tmp_sq):
                qc.ccx(right[i], anc_copy[j], tmp_sq[i + j])
    for i in reversed(range(len(right))):
        qc.cx(right[i], anc_copy[i])

    qc.x(right[0])
    qc.cx(right[0], right[1])
    qc.ccx(right[0], right[1], right[2])
    for i in reversed(range(len(a))):
        qc.cx(a[i], right[i])

    for reg in [e, d, c, b, a]:
        for i in reversed(range(len(reg))):
            qc.cx(reg[i], left[i])


def diffusion(qc, qubits):
    qc.h(qubits)
    qc.x(qubits)
    qc.h(qubits[-1])
    qc.mcx(qubits[:-1], qubits[-1])
    qc.h(qubits[-1])
    qc.x(qubits)
    qc.h(qubits)

a = QuantumRegister(3, 'a')
b = QuantumRegister(3, 'b')
c = QuantumRegister(2, 'c')
d = QuantumRegister(2, 'd')
e = QuantumRegister(2, 'e')
left = QuantumRegister(6, 'left')
right = QuantumRegister(4, 'right')
tmp_sq = QuantumRegister(8, 'tmp_sq')
anc_copy = QuantumRegister(4, 'anc_copy')
flag = QuantumRegister(1, 'flag')
cr = ClassicalRegister(12, 'meas')

qc = QuantumCircuit(a, b, c, d, e, left, right, tmp_sq, anc_copy, flag, cr)
var_qubits = list(a) + list(b) + list(c) + list(d) + list(e)

qc.h(var_qubits)

iterations = 60
for _ in range(iterations):
    oracle(qc, a, b, c, d, e, left, right, tmp_sq, anc_copy, flag)
    diffusion(qc, var_qubits)

qc.measure(var_qubits, cr)

sim = AerSimulator(method='matrix_product_state')
t_qc = transpile(qc, sim)
counts = sim.run(t_qc, shots=20048).result().get_counts()

solutions = all_solutions()
marked_states = [encode_state(a, b, c, d, e) for a, b, c, d, e in solutions]

print("Sprendinių skaičius:", len(marked_states))
print("Pirmi 10 sprendinių:")
for s in solutions[:10]:
    print(s)

sorted_counts = sorted(counts.items(), key=lambda item: item[1], reverse=True)

print(f"{'Binary Result':<15} | {'a b c d e':<12} | {'Count':<6} | {'Check'}")
print("-" * 55)

for bitstring, count in sorted_counts[:20]:
    res = bitstring[::-1]
    a_v = int(res[0:3], 2)
    b_v = int(res[3:6], 2)
    c_v = int(res[6:8], 2)
    d_v = int(res[8:10], 2)
    e_v = int(res[10:12], 2)

    valid = check_solution(a_v, b_v, c_v, d_v, e_v)
    print(f"{bitstring:<15} | {a_v} {b_v} {c_v} {d_v} {e_v:<4} | {count:<6} | {valid}")