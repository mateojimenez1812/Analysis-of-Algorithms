"""
Lab 04 - Exercise 2
Depth First Search (DFS) that prints the value stored at each node of a graph.

Data structure choice: ADJACENCY LIST.
For sparse graphs (the typical case in most applications and in this lab's
example), an adjacency list uses O(V + E) memory instead of the O(V^2) an
adjacency matrix always needs, and iterating over a node's neighbors is
O(degree) instead of O(V). Since DFS only ever needs "give me the neighbors
of this node", the adjacency list is the more efficient and natural fit.
"""


class Graph:
    def __init__(self):
        # adjacency list: node_id -> list of neighbor node_ids
        self.adjacency_list = {}
        # value stored at each node (could be a label, weight, data, etc.)
        self.node_values = {}

    def add_node(self, node_id, value):
        self.adjacency_list.setdefault(node_id, [])
        self.node_values[node_id] = value

    def add_edge(self, u, v, directed=False):
        self.adjacency_list.setdefault(u, []).append(v)
        if not directed:
            self.adjacency_list.setdefault(v, []).append(u)

    def dfs(self, start):
        """
        Iterative DFS using an explicit stack (avoids recursion depth limits
        on large graphs). Prints the value of each node the first time it is
        visited, in DFS order.
        """
        visited = set()
        stack = [start]
        order = []

        while stack:
            node = stack.pop()
            if node in visited:
                continue
            visited.add(node)
            order.append(node)
            print(f"Visiting node {node} -> value = {self.node_values[node]}")

            # push neighbors in reverse so the traversal visits them
            # in the same left-to-right order they were added
            for neighbor in reversed(self.adjacency_list.get(node, [])):
                if neighbor not in visited:
                    stack.append(neighbor)

        return order


if __name__ == "__main__":
    g = Graph()

    # Build a small example graph with letter-labeled nodes and integer values
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
    print("DEPTH FIRST SEARCH (adjacency list)")
    print("=" * 60)
    print("Graph edges:", edges)
    print("Starting DFS from node 'A':\n")

    visit_order = g.dfs("A")

    print("\nDFS visit order:", visit_order)
