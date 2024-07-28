
class Node:
    def __init__(self, name):
        self.name = name
        self.distance = 0
        self.color = "white"
        self.predecessor = None
        self.reachable = []

    
def read_graph(file):
    graph = []
    with open(file, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) != 3:
                continue

            chamber1 = Node(parts[0])
            connection = parts[1]
            chamber2 = Node(parts[2])

            if chamber1 not in graph:
                graph.append(Node(chamber1))
            if chamber2 not in graph:
                graph.append(Node(chamber2))
            
            if connection == '>':
                index = graph.index(Node(chamber1))
                graph[index].reachable.append(chamber2)
            elif connection == '<':
                index = graph.index(Node(chamber2))
                graph[index].reachable.append(chamber1)
            elif connection == '<>':
                index = graph.index(Node(chamber1))
                graph[index].reachable.append(chamber2)
                index = graph.index(Node(chamber2))
                graph[index].reachable.append(chamber1)
    return graph

def bfs(graph, start, goal):

    path = []
    queue = graph[start]
    visited = set()

    while queue:
        v = queue.pop(0)
        if v == goal:
            return path
        
        path.append(v)
        visited.add(v)
        for u in graph[v]:
            if u not in visited:
                queue.append(u)
                visited.add(u)
        
    return None


if __name__ == '__main__':
    # Einlesen der Datei

    file = "08_Graphen\hoehle.txt"
    graph = read_graph(file)

    # Startknoten
    start = "Hoehleneingang"
    goal = "Schatzkammer"

    path = bfs(graph, start, goal)

    if path:
        print("Pfad zur Schatzkammer:", " -> ".join(path))
    else:
        print("Kein Pfad gefunden")

