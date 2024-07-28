from collections import deque

def read_graph(file_path):
    graph = {}
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) != 3:
                continue
            chamber1, connection, chamber2 = parts
            if chamber1 not in graph:
                graph[chamber1] = []
            if chamber2 not in graph:
                graph[chamber2] = []
            
            if connection == '>':
                graph[chamber1].append(chamber2)
            elif connection == '<':
                graph[chamber2].append(chamber1)
            elif connection == '<>':
                graph[chamber1].append(chamber2)
                graph[chamber2].append(chamber1)
    return graph

def bfs_shortest_path(graph, start, goal):
    queue = deque([(start, [start])])
    visited = set()
    while queue:
        current, path = queue.popleft()
        if current == goal:
            return path
        visited.add(current)
        for neighbor in graph.get(current, []):
            if neighbor not in visited:
                queue.append((neighbor, path + [neighbor]))
                visited.add(neighbor)
    return None

def reverse_graph(graph):
    reversed_graph = {}
    for chamber in graph:
        for neighbor in graph[chamber]:
            if neighbor not in reversed_graph:
                reversed_graph[neighbor] = []
            reversed_graph[neighbor].append(chamber)
    return reversed_graph

# Einlesen der Datei und Erstellen des Graphen
file_path = '08_Graphen\\hoehle.txt'
graph = read_graph(file_path)

# Definieren des Höhleneingangs und der Schatzkammer
start_chamber = 'Hoehleneingang'
treasure_chamber = 'Schatzkammer'

# Kürzesten Pfad zum Schatz finden
path_to_treasure = bfs_shortest_path(graph, start_chamber, treasure_chamber)
if path_to_treasure:
    print("Pfad zur Schatzkammer:", " -> ".join(path_to_treasure))
else:
    print("Kein Pfad zur Schatzkammer gefunden.")

# Umkehren des Graphen für den Rückweg
reversed_graph = reverse_graph(graph)

# Kürzesten Rückweg zum Eingang finden
path_back_to_entrance = bfs_shortest_path(reversed_graph, treasure_chamber, start_chamber)
if path_back_to_entrance:
    print("Rückweg zum Eingang:", " -> ".join(path_back_to_entrance))
else:
    print("Kein Rückweg zum Eingang gefunden.")
