from sympy import Matrix,  Rational
import re
import networkx as nx
import matplotlib.pyplot as plt

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

def showMatrixGraph(M):
    G = nx.DiGraph()
    n = M.rows
    G.add_nodes_from(range(1, n + 1)) # sugeneruoti taškus

    for j in range(n):  # iš j-ojo stulpelio
        for i in range(n):  # į i-ąją eilutę
            if M[i, j] != 0:
                G.add_edge(j + 1, i + 1, svoris=M[i, j])

    pos = nx.circular_layout(G)
    # taškai
    nx.draw_networkx_nodes(G, pos, node_size=800)
    nx.draw_networkx_labels(G, pos)

    # lankai
    nx.draw_networkx_edges(
        G, pos,
        connectionstyle="arc3, rad=0.1",
        arrows=True,
        arrowstyle="-|>",
        arrowsize=15,
        edge_color="black",
        min_source_margin=15,
        min_target_margin=15
    )

    # tikimybės
    edge_labels = {(u, v): d["svoris"] for u, v, d in G.edges(data=True)}
    nx.draw_networkx_edge_labels(
        G, pos,
        edge_labels=edge_labels,
        label_pos=0.6,
        font_size=8,
        rotate=False
    )

    plt.axis('off')
    plt.show()
