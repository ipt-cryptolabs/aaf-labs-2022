from Table import Table
from prettytable import PrettyTable

class DataBase:
    def __init__(self):
        self.tables = {}
    def append_table(self, command):
        if command[1] in self.tables.keys():
            print(f"Table with name {command[1]} already exists")
        else:
            table = Table(command)
            self.tables[command[1]] = table
            print(f"Table: {command[1]} with columns: {tuple(command[2])} was successfully created!")
    def select(self, command):
        if len(command)<= 2 and command[1] not in self.tables.keys():
            print(f"Table with name {command[1]} doesn`t exists")
        elif len(command)>2:
            if command[1] not in self.tables.keys():
                print(f"Table with name {command[1]} doesn`t exists")
            if command[3] not in self.tables.keys():
                print(f"Table with name {command[3]} doesn`t exists")
        else:
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
                index_column_1 = table.columns.index(command[3])
                if command[4][0] == '"':
                    command[4] = command[4][1:-1]
                    i = 0
                    while i < len(table.values):
                        if table.values[i][index_column_1] > command[4]:
                            values.append(table.values[i])
                        i += 1
                    if values == []:
                        table = [table.columns, *table.values]
                        tab = PrettyTable(table[0])
                        tab.add_rows(table[1:])
                        print(tab)
                    else:
                        table = [table.columns, *values]
                        tab = PrettyTable(table[0])
                        tab.add_rows(table[1:])
                        print(tab)
                else:
                    index_column_2 = table.columns.index(command[4])
                    i = 0
                    while i < len(table.values):
                        if table.values[i][index_column_1] > table.values[i][index_column_2]:
                            values.append(table.values[i])
                        i += 1
                    if values == []:
                        table = [table.columns, *table.values]
                        tab = PrettyTable(table[0])
                        tab.add_rows(table[1:])
                        print(tab)
                    else:
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
                table_1 = self.tables[command[1]]
                table_2 = self.tables[command[3]]
                index_column_1 = table_1.columns.index(command[5])
                index_column_2 = table_2.columns.index(command[6])
                if len(table_1.values) == len(table_2.values):
                    values = []
                    i = 0
                    while i < len(table_1.values):
                        if table_1.values[i][index_column_1] == table_2.values[i][index_column_2]:
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
            elif (command[2] == "JOIN") and (command[4] == "ON") and (command[7] == "WHERE"):
                pass
            """elif (command[2] == "JOIN") and (command[4] == "WHERE"):
                table_1 = self.tables[command[1]]
                table_2 = self.tables[command[3]]
                index_column_1 = table_1.columns.index(command[3])
                if command[6][0] == '"':
                    command[6] = command[6][1:-1]
                    i = 0
                    if len(table_1.values) == len(table_2.values):
                        while i < len(table_1.values):
                            if table.values[i][index_column_1] > command[4]:
                                values.append(table.values[i])
                            i += 1
                        if values == []:
                            table = [table.columns, *table.values]
                            tab = PrettyTable(table[0])
                            tab.add_rows(table[1:])
                            print(tab)
                        else:
                            table = [table.columns, *values]
                            tab = PrettyTable(table[0])
                            tab.add_rows(table[1:])
                            print(tab)"""
        '''
        CREATE cats (name, group);
        CREATE owners (name2, group2);
        INSERT INTO cats ("1", "Vasya");
        INSERT INTO cats ("2", "Vasya");
        INSERT INTO owners ("1", "Vasya");
        INSERT INTO owners ("3", "Vasya");
        select from cats join owners on name = name2;
        '''