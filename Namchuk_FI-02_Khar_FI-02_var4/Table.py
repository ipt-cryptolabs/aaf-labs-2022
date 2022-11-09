class Table:
    def __init__(self, args):
        self.name = args[1]
        self.columns = args[2]
        self.values = []
    def insert(self, values):
        if len(self.columns) == len(values):
            self.values.append(values)
            print(f"Insert in {self.name} values: {tuple(values)}")
        else:
            print("The number of values does not match the number of columns!")