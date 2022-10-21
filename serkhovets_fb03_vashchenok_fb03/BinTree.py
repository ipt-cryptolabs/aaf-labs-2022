class Node:
    def __init__(self, value, id):
        self.left = None
        self.right = None
        self.value = value
        self.ids = [id]

    def insert(self, value, id):
        if self.value != None:
            if value < self.value:
                if self.left is None:
                    self.left = Node(value, id)
                else:
                    self.left.insert(value, id)
            elif value > self.value:
                if self.right is None:
                    self.right = Node(value, id)
                else:
                    self.right.insert(value, id)
            else:
                self.ids.append(id)
        else:
            self.value = value
            self.ids = [id]

    def find(self, value, node=False):
        n = self
        while n != None:
            if value < n.value:
                n = n.left
            elif value > n.value:
                current = n.right
            else:
                return n.ids if not node else n
        return [] if not node else node



    def getID(self, arr=[]):
        if self.left:
            self.left.getID(arr)
        arr += self.ids
        if self.right:
            self.right.getID(arr)
        return arr


    def PrintTree(self):
        if self.left:
            self.left.PrintTree()
        print(self.value, self.ids, end=', ')
        if self.right:
            self.right.PrintTree()

