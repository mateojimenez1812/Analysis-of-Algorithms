"""
Lab 04 - Exercise 3
Breadth First Search (BFS) that prints the value stored at each node of a graph.

Data structure choice: ADJACENCY LIST (same reasoning as Exercise 2 - sparse
graphs are handled in O(V + E) instead of O(V^2), and BFS only needs to
enumerate each node's neighbors, which is O(degree) with a list).
"""

from collections import deque


class Graph:
    def __init__(self):
        self.adjacency_list = {}
        self.node_values = {}

    def add_node(self, node_id, value):
        self.adjacency_list.setdefault(node_id, [])
        self.node_values[node_id] = value

    def add_edge(self, u, v, directed=False):
        self.adjacency_list.setdefault(u, []).append(v)
        if not directed:
            self.adjacency_list.setdefault(v, []).append(u)

    def bfs(self, start):
        """
        Standard BFS using a queue (collections.deque). Prints the value of
        each node the first time it is visited, in BFS (level) order.
        """
        visited = {start}
        queue = deque([start])
        order = []

        while queue:
            node = queue.popleft()
            order.append(node)
            print(f"Visiting node {node} -> value = {self.node_values[node]}")

            for neighbor in self.adjacency_list.get(node, []):
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append(neighbor)

        return order


if __name__ == "__main__":
    g = Graph()

    # Same example graph as Exercise 2, so the two traversal orders can be compared
    nodes = {
        "A": 10, "B": 20, "C": 30, "D": 40,
        "E": 50, "F": 60, "G": 70
    }
    for node_id, value in nodes.items():
        g.add_node(node_id, value)

    edges = [
        ("A", "B"), ("A", "C"),
        ("B", "D"), ("B", "E"),
        ("C", "F"),
        ("E", "G"),
    ]
    for u, v in edges:
        g.add_edge(u, v)

    print("=" * 60)
    print("BREADTH FIRST SEARCH (adjacency list)")
    print("=" * 60)
    print("Graph edges:", edges)
    print("Starting BFS from node 'A':\n")

    visit_order = g.bfs("A")

    print("\nBFS visit order:", visit_order)
