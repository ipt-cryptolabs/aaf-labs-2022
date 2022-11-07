from Table import Table
from prettytable import PrettyTable

class DataBase:
    def __init__(self):
        self.tables = {}
    def append_table(self, command):
        table = Table(command)
        self.tables[command[1]] = table
        print(f"Table: {command[1]} with columns: {tuple(command[2])} was successfully created!")
    def select(self, command):
        values_table = self.tables[command[1]].values
        columns_table = self.tables[command[1]].columns
        if command == ['SELECT', command[1]]:
            table = [columns_table, *values_table]
            tab = PrettyTable(table[0])
            tab.add_rows(table[1:])
            print(tab)
        elif command[2] == "WHERE":
            table = self.tables[command[1]]
            values = []
            index_column = table.columns.index(command[3])
            if command[4][0] == '"':
                command[4] = command[4][1:-1]
                i = 0
                while i < len(table.values):
                    if table.values[i][index_column] > command[4]:
                        values.append(table.values[i])
                    i += 1
                table = [table.columns, *values]
                tab = PrettyTable(table[0])
                tab.add_rows(table[1:])
                print(tab)
        elif (command[2] == "JOIN") and (len(command) == 4):
            table_1 = self.tables[command[1]]
            table_2 = self.tables[command[3]]
            if len(table_1.values) == len(table_2.values):
                values = []
                i = 0
                while i < len(table_1.values):
                    values.append(table_1.values[i] + table_2.values[i])
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
                        values.append(table_1.values[i] + table_2.values[j])
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
