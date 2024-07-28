from foundation import *


class AVLTreeNode(AlgoDatValue):
    """
    Represents a node in an AVL tree.

    Attributes:
        value: The value stored in the node.
        left: The left child node.
        right: The right child node.
        height: The height of the node.
    """

    def __init__(self, value):
        super().__init__(value)
        self.left = None
        self.right = None
        self.balance = 0
        self.parent = None


class AVLTree():

    def __init__(self):
        self.__root = None

    def get_root(self):
        return self.__root
    
    def insert(self, value:int):
        # TODO: Implement the insert method for the AVL tree.
        y = None
        x = self.__root

        while x is not None:
            y = x
            if value < x.value:
                x = x.left
            else:
                x = x.right

        if y is None:
            self.__root = AVLTreeNode(value)
            y = self.__root
        elif value < y.value:
            y.left = AVLTreeNode(value)
            y.left.parent = y
            y.balance = self.getHeight(y.right) - self.getHeight(y.left)
        else:
            y.right = AVLTreeNode(value)
            y.right.parent = y
            y.balance = self.getHeight(y.right) - self.getHeight(y.left)

        self.updateBalance(y)

        if y.parent is not None:
            self.AVLbalance(y.parent)


    def rightRotate(self, k: AVLTreeNode) -> AVLTreeNode:
        # TODO: Implement the rightRotate method for the AVL tree.
        l = k.left
        l.parent = k.parent
        k.left = l.right

        if l.right is not None:
            k.left.parent = k
        
        l.right = k
        k.parent = l

        if l.parent is not None:
            if l.parent.left == k:
                l.parent.left = l
            else:
                l.parent.right = l

        k.balance = self.getHeight(k.right) - self.getHeight(k.left)
        l.balance = self.getHeight(l.right) - self.getHeight(l.left)

        return l

    def leftRotate(self, k = None) -> AVLTreeNode:
        # TODO: Implement the leftRotate method for the AVL tree.
        r = k.right
        r.parent = k.parent
        k.right = r.left

        if r.left is not None:
            k.right.parent = k

        r.left = k
        k.parent = r

        if r.parent is not None:
            if r.parent.left == k:
                r.parent.left = r
            else:
                r.parent.right = r

        k.balance = self.getHeight(k.right) - self.getHeight(k.left)
        r.balance = self.getHeight(r.right) - self.getHeight(r.left)

        return r

    def rightLeftRotate(self, k) -> AVLTreeNode:
        k.right = self.rightRotate(k.right)
        return self.leftRotate(k)

    def leftRightRotate(self, k) -> AVLTreeNode:
        k.left = self.leftRotate(k.left)
        return self.rightRotate(k)


    def updateBalance(self, k):
        if k.parent is not None:
            heightLeft = self.getHeight(k.left)
            heightRight = self.getHeight(k.right)
            k.balance = heightRight - heightLeft
            self.updateBalance(k.parent)
        
        else:
            heightLeft = self.getHeight(k.left)
            heightRight = self.getHeight(k.right)
            k.balance = heightRight - heightLeft


    def AVLbalance(self, k = None):
        # TODO: Implement the balance method for the AVL tree.

        if k is None:
            return k

        if k.balance == -2:
            if k.left.balance == 1:
                return self.leftRightRotate(k)
            else:
                return self.rightRotate(k)
        elif k.balance == 2:
            if k.right.balance == -1:
                return self.rightLeftRotate(k)
            else:
                return self.leftRotate(k)
        
        if k.parent is not None:
            self.AVLbalance(k.parent)
        else:
            self.__root = k
        
        return k
    
    def getHeight(self, k) -> int:
        if k is None:
            return -1
        return max(self.getHeight(k.left), self.getHeight(k.right)) + 1
    

    def delete(self, value):
        # TODO: Implement the delete method for the AVL tree.
        pass


    def walk(self):
        """
        Prints the values of the nodes in the binary tree in sorted order.
        """
        print("Sorted: [ ", end="")
        self._walk(self.__root)
        print("]")

    def _walk(self, node: AVLTreeNode):
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

    def _treeWalk(self, node: AVLTreeNode, level = 0):
        print(" " * level, end="")
        if node is not None:
            self._treeWalk(node.left, level + 4)
            print(f"{node.value} ")
            self._treeWalk(node.right, level - 4)

    def levelWalk(self, node: AVLTreeNode = None):
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

    def generate_graphviz(self, filename):
        with open(filename, 'w') as f:
            f.write("digraph AVLTree {\n")
            self._generate_graphviz_recursive(self.__root, f)
            f.write("}")

    def _generate_graphviz_recursive(self, root, f):
        if root:
            if root.left:
                f.write(f'"{root.value}" -> "{root.left.value}";\n')
                self._generate_graphviz_recursive(root.left, f)
            if root.right:
                f.write(f'"{root.value}" -> "{root.right.value}";\n')
                self._generate_graphviz_recursive(root.right, f)
        

if __name__ == "__main__":

    file = 'C:\\Studium\\10_Semester\\INF4_1\\Praktikum\\05_AVLTree\\seq1.txt'

    print("AVL Tree")
    tree = AVLTree()
    A = read_int_sequence(file)
    for i in A:
        tree.insert(i)
        # tree.generate_graphviz(f"avl_tree_{i}.dot")

    tree.walk()

    tree.treeWalk()

    tree.levelWalk()

    tree.generate_graphviz('avl_tree.dot')


    print()
    print("Ende erreicht.")