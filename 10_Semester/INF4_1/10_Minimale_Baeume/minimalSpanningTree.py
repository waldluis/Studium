class Graph:
    """
    A class representing a graph.

    Attributes:
        nodes (list): A list of nodes in the graph.
        edges (list): A list of edges in the graph.

    Methods:
        addNode(node): Adds a node to the graph.
        addEdge(edge): Adds an edge to the graph.
        getNodes(): Returns the list of nodes in the graph.
        getEdges(): Returns the list of edges in the graph.
        getSumWeights(): Returns the sum of weights of all edges in the graph.
        __str__(): Returns a string representation of the graph.
    """

    def __init__(self):
        self.nodes = []
        self.edges = []

    def addNode(self, node: str):
        self.nodes.append(node)

    def addEdge(self, edge: 'Edge'):
        self.edges.append(edge)

    def getNodes(self):
        return self.nodes
    
    def getEdges(self):
        return self.edges
    
    def getSumWeights(self):
        return sum([edge.getWeight() for edge in self.edges])
    
    def __str__(self):
        nodeString = ', '.join(self.nodes)

        edgeString = ''
        for edge in self.edges:
            edgeString += str(edge) + '\n'

        return f'Nodes: \n{nodeString}\nEdges:\n{edgeString}'
    

class Edge:
    """
    Represents an edge between two vertices in a graph.

    Attributes:
        start (str): The starting vertex of the edge.
        end (str): The ending vertex of the edge.
        weight (int): The weight of the edge.
    """

    def __init__(self, start:str, end:str, weight:int):
        self.start = start
        self.end = end
        self.weight = weight

    def getWeight(self):
        return self.weight
    
    def __str__(self):
        return f'{self.start} -> {self.end} ({self.weight})'



def kruskal(tree: Graph):
    """
    Applies Kruskal's algorithm to find the minimum spanning tree of a given graph.

    Args:
        tree (Graph): The input graph.

    Returns:
        Graph: The minimum spanning tree of the input graph.
    """

    minTree = Graph()

    # make set of each node
    nodeSetArray = [set([node]) for node in tree.nodes]

    # sort edges by weight
    edges = []
    for edge in tree.edges:
        edges.append(edge)

    edges.sort(key=lambda edge: edge.getWeight())

    # iterate over edges
    for edge in edges:
        start = edge.start
        end = edge.end

        # find the sets of start and end
        startSet = None
        endSet = None
        for nodeSet in nodeSetArray:
            if start in nodeSet:
                startSet = nodeSet
            if end in nodeSet:
                endSet = nodeSet

        # if start and end are in different sets, add edge to minTree
        if startSet != endSet:
            minTree.addEdge(edge)

            # merge the sets
            startSet.update(endSet)
            nodeSetArray.remove(endSet)

    # add all nodes to minTree
    nodes = set()
    for edge in minTree.edges:
        nodes.add(edge.start)
        nodes.add(edge.end)

    for node in nodes:
        minTree.addNode(node)
    
    return minTree


def read_graph_from_file(file) -> Graph:
    """
    Reads a graph from a file and returns a Graph object.

    Args:
        file (str): The path to the file containing the graph data.

    Returns:
        Graph: The graph object representing the data read from the file.
    """
    with open(file, 'r') as f:
        lines = f.readlines()

    graph = Graph()
    nodes = set()

    for line in lines:
        start, end, _ = line.strip().split(";")
        nodes.add(start)
        nodes.add(end)

    for node in nodes:
        graph.addNode(node)

    for line in lines:
        start, end, weight = line.strip().split(";")
        edge = Edge(start, end, int(weight))
        graph.addEdge(edge)

    return graph


def main():
    tree = read_graph_from_file('elektro.txt')

    minTree = kruskal(tree)

    print('Minimal tree:')
    print(minTree)

    print('Sum of weights:', minTree.getSumWeights())


if __name__ == '__main__':
    main()