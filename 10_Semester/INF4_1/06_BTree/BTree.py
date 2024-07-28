from foundation import *

class BTreeNode(AlgoDatValue):
    """
    Represents a node in a B-tree.

    Attributes:
        n (int): The number of keys currently stored in the node.
        keys (AlgoDatArray): An array to store the keys.
        refs (list): A list to store references to child nodes.
        isLeaf (bool): Indicates whether the node is a leaf node.
    """

    def __init__(self, m):
        self.n = 0
        self.keys = AlgoDatArray(2 * m - 1)
        self.refs = [None] * (2 * m)
        self.isLeaf = True

    def __str__(self):
        return "(" + ", ".join([str(self.keys[i]) for i in range(0, self.n)]) + ")"
    

class BTree():

    def __init__(self, m):
        self.root = BTreeNode(m)
        self.__m = m

    def insert(self, key:int):
        """
        Inserts a key into the B-tree.

        Parameters:
        - key (int): The key to be inserted.

        Returns:
        - None
        """
        r = self.root

        if r.n == 2 * self.__m - 1:
            h = BTreeNode(self.__m)
            self.root = h
            h.isLeaf = False
            h.refs[0] = r
            h.n = 0
            self.splitChild(h, 0, self.__m)
            self.insertInNode(h, key)
        else:
            self.insertInNode(r, key)

    def insertInNode(self, start:BTreeNode, key:int):
        """
        Inserts a key into the B-tree node.

        Parameters:
        - start (BTreeNode): The starting node to insert the key.
        - key (int): The key to be inserted.

        Returns:
        None
        """
        i = start.n

        if start.isLeaf:
            while i >= 1 and key < start.keys[i - 1]:
                start.keys[i] = start.keys[i - 1]
                i -= 1
            
            start.keys[i] = key
            start.n += 1

        else:
            j = 0
            while j < start.n and key > start.keys[j]:
                j += 1
            
            if start.refs[j].n == 2 * self.__m - 1:
                self.splitChild(start, j, self.__m)

                if key > start.keys[j]:
                    j += 1
            
            self.insertInNode(start.refs[j], key)
    

    def search(self, value:int) -> BTreeNode:
        """
        Searches for a given value in the B-tree.

        Parameters:
        - value (int): The value to search for.

        Returns:
        - BTreeNode: The node containing the value, or None if the value is not found.
        """
        return self.__search(self.root, value)
    
    def __search(self, node:BTreeNode, value:int) -> BTreeNode:
        """
        Recursively searches for a given value in the B-tree.

        Args:
            node (BTreeNode): The current node being searched.
            value (int): The value to search for.

        Returns:
            BTreeNode: The node containing the value, or None if the value is not found.
        """
        i = 0

        while i < node.n and value > node.keys[i]:
            i += 1

        if i < node.n and value == node.keys[i]:
            return node
        
        if node.isLeaf:
            return None
        
        return self.__search(node.refs[i], value)

    def delete(self, value:int):
        """
        Deletes a value from the B-tree.

        Parameters:
        - value (int): The value to be deleted.

        Returns:
        - None
        """
        self.__delete(self.root, value)

    def __delete(self, node:BTreeNode, value:int):
        i = 0
        while i < node.n and value > node.keys[i]:
            i += 1

        if i < node.n and value == node.keys[i]:
            if node.isLeaf:
                # Case 1: The value is in a leaf node
                for j in range(i, node.n - 1):
                    node.keys[j] = node.keys[j + 1]
                node.n -= 1
            else:
                # Case 2: The value is in an internal node
                pred = self.__getPredecessor(node, i)
                node.keys[i] = pred
                self.__delete(node.refs[i], pred)
        else:
            if node.isLeaf:
                # Case 3: The value is not in the B-tree
                return
            else:
                # Case 4: The value may be in a child node
                if node.refs[i].n < self.__m:
                    self.__restoreOrder(node, i)
                self.__delete(node.refs[i], value)

    def __getPredecessor(self, node:BTreeNode, i:int) -> int:
        """
        Returns the predecessor of the key at index i in the given node.

        Parameters:
        - node (BTreeNode): The node containing the key.
        - i (int): The index of the key.

        Returns:
        - int: The predecessor of the key.
        """
        curr = node.refs[i]
        while not curr.isLeaf:
            curr = curr.refs[curr.n]
        return curr.keys[curr.n - 1]

    def __restoreOrder(self, node:BTreeNode, i:int):
        """
        Restores the order of the B-tree by borrowing a key from a sibling or merging nodes.

        Parameters:
        - node (BTreeNode): The parent node.
        - i (int): The index of the child node.

        Returns:
        - None
        """
        if i > 0 and node.refs[i - 1].n >= self.__m:
            # Borrow a key from the left sibling
            child = node.refs[i]
            sibling = node.refs[i - 1]

            # Shift keys in the child node to the right
            for j in range(child.n, 0, -1):
                child.keys[j] = child.keys[j - 1]
            child.n += 1

            # Move the key from the parent to the child node
            child.keys[0] = node.keys[i - 1]

            # Move the rightmost key from the left sibling to the parent
            node.keys[i - 1] = sibling.keys[sibling.n - 1]

            # Move the rightmost child reference from the left sibling to the child node
            if not child.isLeaf:
                for j in range(child.n, 0, -1):
                    child.refs[j] = child.refs[j - 1]
                child.refs[0] = sibling.refs[sibling.n]

            sibling.n -= 1

        elif i < node.n and node.refs[i + 1].n >= self.__m:
            # Borrow a key from the right sibling
            child = node.refs[i]
            sibling = node.refs[i + 1]

            # Move the key from the parent to the child node
            child.keys[child.n] = node.keys[i]

            # Move the leftmost key from the right sibling to the parent
            node.keys[i] = sibling.keys[0]

            # Shift keys in the right sibling to the left
            for j in range(0, sibling.n - 1):
                sibling.keys[j] = sibling.keys[j + 1]

            # Move the leftmost child reference from the right sibling to the child node
            if not child.isLeaf:
                child.refs[child.n + 1] = sibling.refs[0]

            sibling.n -= 1

        else:
            # Merge the child node with a sibling
            if i > 0:
                # Merge with the left sibling
                child = node.refs[i]
                sibling = node.refs[i - 1]

                # Move the key from the parent to the left sibling
                sibling.keys[sibling.n] = node.keys[i - 1]

                # Move keys and child references from the child node to the left sibling
                for j in range(0, child.n):
                    sibling.keys[sibling.n + j + 1] = child.keys[j]
                    sibling.refs[sibling.n + j + 1] = child.refs[j]

                sibling.refs[sibling.n + child.n + 1] = child.refs[child.n]

                sibling.n += child.n + 1

                # Shift keys and child references in the parent node to the left
                for j in range(i - 1, node.n - 1):
                    node.keys[j] = node.keys[j + 1]
                    node.refs[j + 1] = node.refs[j + 2]

                node.n -= 1

            else:
                # Merge with the right sibling
                child = node.refs[i]
                sibling = node.refs[i + 1]

                # Move the key from the parent to the child node
                child.keys[child.n] = node.keys[i]

                # Move keys and child references from the right sibling to the child node
                for j in range(0, sibling.n):
                    child.keys[child.n + j + 1] = sibling.keys[j]
                    child.refs[child.n + j + 1] = sibling.refs[j]

                child.refs[child.n + sibling.n + 1] = sibling.refs[sibling.n]

                child.n += sibling.n + 1

                # Shift keys and child references in the parent node to the left
                for j in range(i, node.n - 1):
                    node.keys[j] = node.keys[j + 1]
                    node.refs[j + 1] = node.refs[j + 2]

                node.n -= 1


    def getHeigth(self) -> int:
            """
            Returns the height of the B-tree.

            Returns:
                int: The height of the B-tree.
            """
            height = 0
            node = self.root

            while not node.isLeaf:
                node = node.refs[0]
                height += 1

            return height

    def splitChild(self, parent, i, m):
        """
        Splits a child node of the parent node at index i.

        Args:
            parent (BTreeNode): The parent node.
            i (int): The index of the child node to split.
            m (int): The order of the B-tree.

        Returns:
            None
        """
        child = parent.refs[i]
        h = BTreeNode(m)
        h.isLeaf = child.isLeaf
        h.n = m - 1

        for j in range(0, m - 1):
            h.keys[j] = child.keys[j + m]

        if not child.isLeaf:
            for j in range(0, m):
                h.refs[j] = child.refs[j + m]

            for j in range(m, child.n + 1):
                child.refs[j] = None

        child.n = m - 1

        for j in range(parent.n, i, -1):
            parent.refs[j + 1] = parent.refs[j]
            parent.keys[j] = parent.keys[j - 1]

        parent.refs[i + 1] = h
        parent.keys[i] = child.keys[m - 1]
        parent.n += 1
    
    def walk(self):
        """
        Prints the keys of the B-tree in ascending order.

        Returns:
        None
        """
        self.__walk(self.root)
        print()

    def __walk(self, node:BTreeNode):
        """
        Recursively prints the keys of the B-tree in ascending order.

        Args:
            node (BTreeNode): The current node being processed.

        Returns:
            None
        """
        if node is not None:
            if node.isLeaf:
                for i in range(0, node.n):
                    print(f"{node.keys[i]} ", end="")
            else:
                for i in range(0, node.n):
                    self.__walk(node.refs[i])
                    print(f"{node.keys[i]} ", end="")
                self.__walk(node.refs[node.n])

if __name__ == "__main__":

    file = 'C:\\Studium\\10_Semester\\INF4_1\\Praktikum\\06_BTree\\seq2.txt'

    m = 3

    print("B Tree 3")
    tree3 = BTree(3)

    A = read_int_sequence(file)
    for i in A:
        tree3.insert(i)

    # tree3.walk()

    print(f"Height: {tree3.getHeigth()}")

    find = 0
    print(f"Print node with value {find}:")
    node = tree3.search(find)
    print(node)

    print("Tree 3 done.")
    print("-----------------")

    print("B Tree 5:")
    tree5 = BTree(5)

    for i in A:
        tree5.insert(i)
    
    # tree5.walk()

    print(f"Height: {tree5.getHeigth()}")

    find = 0
    print(f"Print node with value {find}:")
    node = tree5.search(find)
    print(node)
    print("Tree 5 done.")

    print()
    print("Ende erreicht.")