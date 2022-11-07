class Table:
    def __init__(self, args):
        self.name = args[1]
        self.columns = args[2]
        self.values = []
    def insert(self, values):
        self.values.append(values)
        print(f"Insert in {self.name} values: {tuple(values)}")
