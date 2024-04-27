from foundation import *

class BinTreeNode(AlgoDatValue):
    """
    Represents a node in a binary tree.

    Attributes:
        value: The value stored in the node.
        left: The left child node.
        right: The right child node.
    """

    def __init__(self, value):
        super().__init__(value)
        self.left = None
        self.right = None

class BinTree():
    """
    Binary Tree class represents a binary tree data structure.
    """

    def __init__(self):
        self.__root = None

    def get_root(self):
        """
        Returns the root node of the binary tree.

        Returns:
            BinTreeNode: The root node of the binary tree.
        """
        return self.__root

    def insert(self, value:int):
        """
        Inserts a new node with the given value into the binary tree.

        Args:
            value (int): The value to be inserted into the binary tree.
        """
        y = None
        x = self.__root

        while x is not None:
            y = x
            if value < x.value:
                x = x.left
            else:
                x = x.right

        if y is None:
            self.__root = BinTreeNode(value)
        elif value < y.value:
            y.left = BinTreeNode(value)
        else:
            y.right = BinTreeNode(value)


    def find(self, key):
        """
        Finds a node with the given key in the binary tree.

        Args:
            key: The key to be searched in the binary tree.

        Returns:
            BinTreeNode: The node with the given key, or None if not found.
        """
        if self.__root is None or self.__root.value == key:
            return None
        
    def walk(self):
        """
        Prints the values of the nodes in the binary tree in sorted order.
        """
        print("Sorted: [ ", end="")
        self._walk(self.__root)
        print("]")

    def _walk(self, node: BinTreeNode):
        if node is not None:
            self._walk(node.left)
            print(f"{node.value} ", end="")
            self._walk(node.right)

        

    def treeWalk(self):
        """
        Prints the values of the nodes in the binary tree in a tree-like structure.
        """
        print("Tree Walk:")
        self._treeWalk(self.__root, 20)
        print()

    def _treeWalk(self, node: BinTreeNode, level = 0):
        print(" " * level, end="")
        if node is not None:
            self._treeWalk(node.left, level + 4)
            print(f"{node.value} ")
            self._treeWalk(node.right, level - 4)

    def levelWalk(self, node: BinTreeNode = None):
        """
        Prints the values of the nodes in the binary tree in level order.
        """
        if self.__root is not None:
            queue = [self.__root]
            while len(queue) > 0:
                n = queue.pop(0)
                print(f"{n.value} ", end="")
                if n.left is not None:
                    queue.append(n.left)
                if n.right is not None:
                    queue.append(n.right)


if __name__ == "__main__":
    file = "seq0.txt"

    print("Binary Tree:")
    tree = BinTree()
    A = read_int_sequence(file)
    for i in A:
        tree.insert(i)
    
    tree.walk()

    tree.treeWalk()

    tree.levelWalk()


    # AlgoDatValue.summary()

    print()
    print("End of Binary Tree")
