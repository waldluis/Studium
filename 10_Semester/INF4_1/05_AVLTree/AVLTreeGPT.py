class AVLNode:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1


class AVLTree:
    def __init__(self):
        self.root = None

    def insert(self, root, key):
        if not root:
            return AVLNode(key)
        elif key < root.key:
            root.left = self.insert(root.left, key)
        else:
            root.right = self.insert(root.right, key)

        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

        balance = self.get_balance(root)

        # Left Left Case
        if balance > 1 and key < root.left.key:
            return self.rotate_right(root)

        # Right Right Case
        if balance < -1 and key > root.right.key:
            return self.rotate_left(root)

        # Left Right Case
        if balance > 1 and key > root.left.key:
            root.left = self.rotate_left(root.left)
            return self.rotate_right(root)

        # Right Left Case
        if balance < -1 and key < root.right.key:
            root.right = self.rotate_right(root.right)
            return self.rotate_left(root)

        return root

    def rotate_left(self, z):
        y = z.right
        T2 = y.left

        y.left = z
        z.right = T2

        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))

        return y

    def rotate_right(self, z):
        y = z.left
        T3 = y.right

        y.right = z
        z.left = T3

        z.height = 1 + max(self.get_height(z.left), self.get_height(z.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))

        return y

    def get_height(self, root):
        if not root:
            return 0
        return root.height

    def get_balance(self, root):
        if not root:
            return 0
        return self.get_height(root.left) - self.get_height(root.right)

    def generate_graphviz(self, filename):
        with open(filename, 'w') as f:
            f.write("digraph AVLTree {\n")
            self._generate_graphviz_recursive(self.root, f)
            f.write("}")

    def _generate_graphviz_recursive(self, root, f):
        if root:
            if root.left:
                f.write(f'"{root.key}" -> "{root.left.key}";\n')
                self._generate_graphviz_recursive(root.left, f)
            if root.right:
                f.write(f'"{root.key}" -> "{root.right.key}";\n')
                self._generate_graphviz_recursive(root.right, f)


# Example usage:
avl_tree = AVLTree()
keys = [-59,52,46,14,-50,58,-87,-77,34,15,50,47,51,48]

for key in keys:
    avl_tree.root = avl_tree.insert(avl_tree.root, key)

avl_tree.generate_graphviz("avl_tree_graphviz.dot")
