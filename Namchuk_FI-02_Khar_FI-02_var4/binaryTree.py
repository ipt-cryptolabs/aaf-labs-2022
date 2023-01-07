class Node:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data


class BinaryTree:
    def __init__(self):
        self.root = None

    def insert(self, path, data):
        if self.root == None:
            self.root = Node(data)
            return
        else:
            if path:
                if path.data > data:
                    if path.left != None:
                        path = path.left
                        self.insert(path, data)
                    else:
                        path.left = Node(data)
                else:
                    if path.right != None:
                        path = path.right
                        self.insert(path, data)
                    else:
                        path.right = Node(data)
            else:
                path = Node(data)
    def prnt(self, root):
        if root.left:
            self.prnt(root.left)
        print(root.data)
        if root.right:
            self.prnt(root.right)


tree = BinaryTree()
tree.insert(tree.root, 5)
tree.insert(tree.root, 10)
tree.insert(tree.root, 2)
tree.insert(tree.root, 4)
tree.prnt(tree.root)
print("done")