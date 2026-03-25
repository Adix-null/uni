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

#region SA.22
if question == 'SA' or question == 0:
    s_hidden = 11011