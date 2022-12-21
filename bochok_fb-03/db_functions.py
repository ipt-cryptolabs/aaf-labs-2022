from tabulate import tabulate
from bin_s_tree import Node, BinarySearchTree


class Table:

    def __init__(self, args):
        self.title = args[1]
        self.columns = args[2].keys()
        self.rows = list()
        self.rows_c = 0
        self.indexed = [x for x in args[2].keys() if args[2][x] == 1]

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
        print(args[2])
        if args[1] in self.tables.keys():
            print(f"CREATE Error: The table {args[1]} already exists.")
        else:
            new_tab = Table(args)
            self.tables[args[1]] = new_tab
            print(f"The table {args[1]} with columns {tuple(args[2].keys())} has been created!")
            print(new_tab.indexed)
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
            if args[1] not in self.tables.keys() or args[3] not in self.tables.keys():
                print(f"SELECT Error: table {args[1] if args[1] not in self.tables.keys() else args[3]} "
                      f"does not exist.")
                return
            elif args[5] not in self.tables[args[1]].columns or \
                    args[7] not in self.tables[args[3]].columns:
                exp = args[5] not in self.tables[args[1]].columns
                print(f"SELECT Error: the column {args[5] if exp else args[7]} "
                      f"does not exist in table {args[1] if exp else args[3]}")
                return
            else:
                line += f"\nleft_join table {args[3]} on columns: {args[5]}, {args[-1]}"

                our_table = self.tables[args[1]]
                joined_table = self.tables[args[3]]

                index1 = our_table.columns.index(args[5])
                index2 = joined_table.columns.index(args[7])

                columns = our_table.columns + joined_table.columns
                columns.remove(args[7])

                tab_join = Table([0, "temp", *columns])

                for i in our_table.rows:
                    matched = False
                    for j in joined_table.rows:
                        if i[index1] == j[index2]:
                            tab_join.rows.append(i+j)
                            tab_join.rows[-1].pop(len(our_table.columns)+index2)
                            matched = True

                    if not matched:
                        tab_join.rows.append(i+([""] * (len(joined_table.columns)-1)))

            print(line)
            print(tab_join)
            return

        elif len(args) == 6:
            if args[1] not in self.tables.keys():
                print(f"SELECT Error: table {args[1]} does not exist.")
            elif args[3] not in self.tables[args[1]].columns:
                print(f"SELECT Error: the column {args[3]} does not exist in table {args[1]}.")
            else:
                line += f"\ncondition: {args[3]} < {args[5]}:"
                our_table = self.tables[args[1]]
                index1 = our_table.columns.index(args[3])
                tab_where = Table([0, "temp", *our_table.columns])
                if args[5][0] == '"':
                    string = args[5][1:-1]
                    for i in our_table.rows:
                        if i[index1] < string:
                            tab_where.rows.append(i)
                else:
                    if args[5] not in our_table.columns:
                        print(f"SELECT Error: the column {args[5]} does not exist in table {args[1]}.")
                        return
                    else:
                        index2 = our_table.columns.index(args[5])
                        for i in our_table.rows:
                            if i[index1] < i[index2]:
                                tab_where.rows.append(i)

                print(line)
                print(tab_where)
                return

        else:
            if args[1] not in self.tables.keys() or args[3] not in self.tables.keys():
                print(f"SELECT Error: table {args[1] if args[1] not in self.tables.keys() else args[3]} "
                      f"does not exist.")
                return
            elif args[5] not in self.tables[args[1]].columns or \
                    args[7] not in self.tables[args[3]].columns:
                exp = args[5] not in self.tables[args[1]].columns
                print(f"SELECT Error: the column {args[5] if exp else args[7]} "
                      f"does not exist in table {args[1] if exp else args[3]}")
                return
            elif args[9] not in self.tables[args[1]].columns and \
                    args[9] not in self.tables[args[3]].columns:
                print(f"SELECT Error: the column {args[9]} "
                      f"does not exist in table {args[1]} or {args[3]}.")
                return
            else:
                line += f"""\nleft_join table {args[3]} on columns {args[5]}, {args[7]}\ncondition: {args[9]} < {args[11]}..."""

                our_table = self.tables[args[1]]
                joined_table = self.tables[args[3]]

                index1 = our_table.columns.index(args[5])
                index2 = joined_table.columns.index(args[7])

                columns = our_table.columns + joined_table.columns
                # columns.remove(args[7])

                tab_join_where = Table([0, "temp", *columns])

                for i in our_table.rows:
                    matched = False
                    for j in joined_table.rows:
                        if i[index1] == j[index2]:
                            tab_join_where.rows.append(i + j)
                            matched = True

                    if not matched:
                        tab_join_where.rows.append(i + [""] * (len(joined_table.columns)))

                index_wh1 = tab_join_where.columns.index(args[9])

                if args[11][0] == '"':
                    string = args[11][1:-1]
                    i = 0
                    while i < len(tab_join_where.rows):
                        if tab_join_where.rows[i][index_wh1] >= string or tab_join_where.rows[i][index_wh1] == "":
                            tab_join_where.rows.pop(i)
                        else:
                            tab_join_where.rows[i].pop(len(our_table.columns) + index2)
                            i += 1

                elif args[11] not in tab_join_where.columns:
                    print(f"SELECT Error: the column {args[9]} does not exist.")
                    return

                else:
                    index_wh2 = tab_join_where.columns.index(args[11])
                    i = 0
                    while i < len(tab_join_where.rows):
                        if tab_join_where.rows[i][index_wh1] >= tab_join_where.rows[i][index_wh2] \
                                or tab_join_where.rows[i][index_wh2] == "":
                            tab_join_where.rows.pop(i)
                        else:
                            tab_join_where.rows[i].pop(len(our_table.columns) + index2)
                            i += 1

                tab_join_where.columns.pop(len(our_table.columns) + index2)

                print(line)
                print(tab_join_where)
                return
