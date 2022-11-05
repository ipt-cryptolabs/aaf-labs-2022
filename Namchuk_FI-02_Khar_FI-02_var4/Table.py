from prettytable import PrettyTable


class Table:
    def __init__(self, args):
        self.name = args[1]
        self.columns = args[2]
        self.values = []

    @classmethod
    def create(cls, command, database):
        table = Table(command)
        database[table.name] = table
        print(f"Table: {command[1]} with columns: {tuple(command[2])} was successfully created!")

    @classmethod
    def insert(cls, command, database):
        database[command[1]].values.append(command[2])
        print(f"Insert in {command[1]} values: {tuple(command[2])}")

    @classmethod
    def select(cls, command, database):
        values_table = database[command[1]].values
        columns_table = database[command[1]].columns
        if command == ['SELECT', command[1]]:
            table = [columns_table, *values_table]
            tab = PrettyTable(table[0])
            tab.add_rows(table[1:])
            print(tab)
        elif command[2] == "WHERE":
            table = database[command[1]]
            values = []
            index_column = table.columns.index(command[3])
            if command[4][0] == '"':
                command[4] = command[4][1:-1]
                i = 0
                while i < len(table.values):
                    if table.values[i][index_column] > command[4]:
                        values.append(table.values[i])    
                    i+=1
                table = [table.columns, *values]
                tab = PrettyTable(table[0])
                tab.add_rows(table[1:])
                print(tab)
        elif (command[2] == "JOIN") and (len(command)==4):
            table_1 = database[command[1]]
            table_2 = database[command[3]]
            if len(table_1.values) == len(table_2.values):
                values = []
                i = 0
                while i < len(table_1.values):
                    values.append(table_1.values[i]+table_2.values[i])
                    i += 1
                table = [[*table_1.columns, *table_2.columns], *values]
                tab = PrettyTable(table[0])
                tab.add_rows(table[1:])
                print(tab)
            else:
                values = []
                i = 0
                while i < len(table_1.values):
                    j = 0
                    while j < len(table_2.values):
                        values.append(table_1.values[i]+table_2.values[j])
                        j += 1
                    i += 1
                table = [[*table_1.columns, *table_2.columns], *values]
                tab = PrettyTable(table[0])
                tab.add_rows(table[1:])
                print(tab)
        elif (command[2] == "JOIN") and (command[4] == "ON") and (len(command) == 7):
            pass
        elif (command[2] == "JOIN") and (command[4] == "ON") and (command[7] == "WHERE"):
            pass
        elif (command[2] == "JOIN") and (command[4] == "WHERE"):
            pass