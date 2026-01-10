import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()

edges = [
    (0,1),
    (0,2),
    (1,3),
    (2,3),
    (1,4),
    (2,5),
    (4,6),
    (5,6),
    (6,7),
    (3,7)
]

G.add_edges_from(edges)

plt.figure(figsize=(8,6))

nx.draw(
    G,
    with_labels=True,
    node_size=1000
)

plt.title("Network Topology")

plt.show()