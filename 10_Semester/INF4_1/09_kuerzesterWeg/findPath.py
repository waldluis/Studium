import heapq

# Convert the grid to an adjacency matrix and get node indices
def grid_to_adjacency_matrix(grid):
    rows, cols = len(grid), len(grid[0])
    node_indices = {}
    index = 0
    
    # Assign an index to each traversable cell
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] != 'x':
                node_indices[(r, c)] = index
                index += 1

    # Initialize the adjacency matrix with zeros
    size = len(node_indices)
    adjacency_matrix = [[0] * size for _ in range(size)]
    
    # Directions for moving in the grid (up, down, left, right)
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    for (r, c), idx in node_indices.items():
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if (nr, nc) in node_indices:
                neighbor_idx = node_indices[(nr, nc)]
                adjacency_matrix[idx][neighbor_idx] = 1
                adjacency_matrix[neighbor_idx][idx] = 1  # Since the graph is undirected

    return adjacency_matrix, node_indices

# Heuristic function (Manhattan distance)
def heuristic(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1])

# A* algorithm implementation
def a_star(adjacency_matrix, node_indices, start, end):
    """
    Finds the shortest path between two nodes using the A* algorithm.

    Parameters:
    - adjacency_matrix (list of lists): The adjacency matrix representing the graph.
    - node_indices (dict): A dictionary mapping node names to their corresponding indices in the adjacency matrix.
    - start (str): The name of the starting node.
    - end (str): The name of the target node.

    Returns:
    - path (list): The shortest path from the start node to the end node, represented as a list of node names.
      If no path is found, returns None.
    """
    reverse_node_indices = {v: k for k, v in node_indices.items()}
    start_idx = node_indices[start]
    end_idx = node_indices[end]
    
    open_set = []
    heapq.heappush(open_set, (0, start_idx))
    came_from = {start_idx: None}
    g_score = {i: float('inf') for i in range(len(adjacency_matrix))}
    g_score[start_idx] = 0
    f_score = {i: float('inf') for i in range(len(adjacency_matrix))}
    f_score[start_idx] = heuristic(start, end)

    while open_set:
        _, current = heapq.heappop(open_set)
        
        if current == end_idx:
            # Reconstruct path
            path = []
            while current is not None:
                path.append(reverse_node_indices[current])
                current = came_from[current]
            return path[::-1]
        
        for neighbor in range(len(adjacency_matrix)):
            if adjacency_matrix[current][neighbor] == 1:
                tentative_g_score = g_score[current] + 1
                
                if tentative_g_score < g_score[neighbor]:
                    came_from[neighbor] = current
                    g_score[neighbor] = tentative_g_score
                    f_score[neighbor] = tentative_g_score + heuristic(reverse_node_indices[neighbor], end)
                    if neighbor not in [i[1] for i in open_set]:
                        heapq.heappush(open_set, (f_score[neighbor], neighbor))
    
    return None  # No path found

def read_grid_from_file(file_path):
    with open(file_path, 'r') as file:
        grid = [list(line.strip()) for line in file]
    return grid

def find_letter(grid, letter):
    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if cell == letter:
                return r, c
    return None


if __name__ == '__main__':

    # Define the grid
    grid = read_grid_from_file('labyrinth.txt')

    # Get the adjacency matrix and node indices
    adjacency_matrix, node_indices = grid_to_adjacency_matrix(grid)

    # Coordinates for start (S) and end (A)
    start = find_letter(grid, 'S')
    end = find_letter(grid, 'A')

    # Find the path
    path = a_star(adjacency_matrix, node_indices, start, end)

    print(path)  
    print("Length of the path:", len(path) - 1)

    # print("adjanency matrix:")
    # for row in adjacency_matrix:
    #     print(row)



    # paint the path
    for r, c in path:
        grid[r][c] = '*'

    grid[start[0]][start[1]] = 'S'
    grid[end[0]][end[1]] = 'A'

    # Print the grid with the path
    for row in grid:
        print(''.join(row))
