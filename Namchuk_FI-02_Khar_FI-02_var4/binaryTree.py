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
            if [*data][0] == [*path.data][0]:
                path.data[[*path.data][0]].append(*data[[*data][0]])
                return
            if path:
                if [*path.data][0] > [*data][0]:
                    if path.left != None:
                        path = path.left
                        self.insert(path, data)
                    else:
                        if path.left != None:
                            data[[*data][0]] = data[[*data][0]][0]
                        path.left = Node(data)
                else:
                    if path.right != None:
                        path = path.right
                        self.insert(path, data)
                    else:
                        if path.right != None:
                            data[[*data][0]] = data[[*data][0]][0]
                        path.right = Node(data)
            else:
                path = Node(data)
    def search_equal(self, value):
        acc = []
        self._search_equal(value, acc, self.root)
        return acc
    def _search_equal(self, value, acc, path):
        if path is None:
            return
        if [*path.data][0] == value:
            for i in path.data[[*path.data][0]]:
                acc.append(i)
        if [*path.data][0] > value:
            self._search_equal(value, acc, path.left)
            self._search_equal(value, acc, path.right)
        else:
            self._search_equal(value, acc, path.right)
    def search_more(self, value):
        acc = []
        self._search_more(value, acc, self.root)
        return acc
    def _search_more(self, value, acc, path):
        if path is None:
            return
        if [*path.data][0] > value:
            for i in path.data[[*path.data][0]]:
                acc.append(i)
        if [*path.data][0] > value:
            self._search_more(value, acc, path.left)
            self._search_more(value, acc, path.right)
        else:
            self._search_more(value, acc, path.right)
'''tree = BinaryTree()
tree.insert(tree.root, {3: [[4]]})
tree.insert(tree.root, {3: [[3]]})
tree.insert(tree.root, {6: [[6]]})
tree.insert(tree.root, {7: [[7]]})
tree.insert(tree.root, {8: [[8]]})
tree.insert(tree.root, {4: [[4]]})
tree.insert(tree.root, {8: [[8]]})
tree.insert(tree.root, {9: [[9]]})
tree.insert(tree.root, {0: [[0]]})
tree.insert(tree.root, {9: [[9]]})
tree.insert(tree.root, {8: [[8]]})
print(tree.search_equal(8))
print(tree.search_more(5))'''
