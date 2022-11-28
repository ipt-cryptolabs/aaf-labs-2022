from tabulate import tabulate


class Table:

    def __init__(self, args):
        self.title = args[1]
        self.columns = args[2:]
        self.rows = list()
        self.rows_c = 0

    def __str__(self):
        return tabulate(self.rows, headers=self.columns, tablefmt="psql")

    def insert_row_inside_table(self, args):
        if len(self.columns) != len(args) - 2:
            print("Error: number of inserted values does not match to the number of columns.")
        else:
            self.rows.append(args[2:])
            self.rows_c += 1
            print(f"1 row with values {tuple(args[2:])} has been added to {args[1]}!\nRows in table: {self.rows_c}")
        return


class DB:

    def __init__(self):
        self.tables = dict()

    def create(self, args):
        if args[1] in self.tables.keys():
            print(f"CREATE Error: The table {args[1]} already exists.")
        else:
            new_tab = Table(args)
            self.tables[args[1]] = new_tab
            print(f"The table {args[1]} with columns {tuple(args[2:])} has been created!")
        return

    def insert_row(self, args):
        if args[1] not in self.tables.keys():
            print(f"INSERT Error: table {args[1]} does not exist.")
        else:
            self.tables[args[1]].insert_row_inside_table(args)
        return

    def select(self, args):
        line = f"Selecting from table {args[1]}"

        if len(args) == 2:
            if args[1] not in self.tables.keys():
                print(f"SELECT Error: table {args[1]} does not exist.")
            else:
                print(line + "...")
                print(self.tables[args[1]])

        elif len(args) == 8:
            line += f"\nleft_join table {args[3]} on columns: {args[5]}, {args[-1]}"
            print(line)
        elif len(args) == 6:
            line += f"\ncondition: {args[3]} {args[4]} {args[5]}"
            print(line)
        else:
            line += f"""\nleft_join table {args[3]} on columns {args[5]}, {args[7]}
    condition: {args[9]} {args[10]} {args[11]}"""
            print(line)
        return
