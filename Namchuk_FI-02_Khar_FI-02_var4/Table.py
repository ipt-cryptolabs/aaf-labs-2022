from binaryTree import BinaryTree, Node
class Table:
    def __init__(self, args):
        self.name = args[1]
        self.columns = args[2]
        self.values = []
        self.check_indexed = []
        self.trees = []
    def Trees(self):
        j=0
        for i in self.check_indexed:
             if i == True:
                 tree = BinaryTree()
                 self.trees.append([tree, j])
             j+=1
    def insert(self, values):
        if len(self.columns) == len(values):
            if True not in self.check_indexed:
                self.values.append(values)
                print(f"Insert in {self.name} values: {tuple(values)}")
            else:
                self.values.append(values)
                for tree in self.trees:
                    index = tree[1]
                    tree[0].insert(tree[0].root, {values[index]: [values]})
                print(f"Insert in {self.name} values: {tuple(values)}")
        else:
            print("The number of values does not match the number of columns!")