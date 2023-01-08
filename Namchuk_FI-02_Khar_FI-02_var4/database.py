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
            return
        elif len(command)>2 and (command[1] not in self.tables.keys() or command[3] not in self.tables.keys()):
            if command[1] not in self.tables.keys():
                print(f"Table with name {command[1]} doesn`t exists")
                return
            if (command[3] not in self.tables.keys()) and ('JOIN' in command):
                print(f"Table with name {command[3]} doesn`t exists")
                return
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
            if command[3] not in table.columns:
                print(f"There is no such column with name {command[3]}")
                return
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
                if command[4] not in table.columns:
                    print(f"There is no such column with name {command[4]}")
                    return
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
            if len(table_1.columns + table_2.columns) != len(set(table_1.columns + table_2.columns)):
                print("Сolumns in tables are not unique!")
                return
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
            if len(table_1.columns + table_2.columns) != len(set(table_1.columns + table_2.columns)):
                print("Сolumns in tables are not unique!")
                return
            if command[5] not in table_1.columns:
                print(f"There is no such column with name {command[5]}")
                return
            elif command[6] not in table_2.columns:
                print(f"There is no such column with name {command[6]}")
                return
            index_column_1 = table_1.columns.index(command[5])
            index_column_2 = table_2.columns.index(command[6])
            if len(table_1.values) == len(table_2.values):
                values = []
                i = 0
                while i < len(table_1.values):
                    j = 0
                    while j < len(table_2.values):
                        if table_1.values[i][index_column_1] == table_2.values[j][index_column_2]:
                            values.append(table_1.values[i] + table_2.values[j])
                        j += 1
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
            table_1 = self.tables[command[1]]
            table_2 = self.tables[command[3]]
            if len(table_1.columns + table_2.columns) != len(set(table_1.columns + table_2.columns)):
                print("Сolumns in tables are not unique!")
                return
            values = []
            if len(table_1.values) == len(table_2.values):
                if command[9][0] == '"':
                    if command[8] in table_1.columns:
                        index_column_where_1 = table_1.columns.index(command[8])
                        check_table = 1
                    elif command[8] in table_2.columns:
                        index_column_where_1 = table_2.columns.index(command[8])
                        check_table = 2
                    else:
                        print(f"There is no such column with name {command[8]}")
                        return
                    command[9] = command[9][1:-1]
                    index_column_join_1 = table_1.columns.index(command[5])
                    index_column_join_2 = table_2.columns.index(command[6])
                    i = 0
                    while i < len(table_1.values):
                        j = 0
                        while j < len(table_2.values):
                            if check_table == 1:
                                if (table_1.values[i][index_column_where_1] > command[9]) and (table_1.values[i][index_column_join_1] == table_2.values[j][index_column_join_2]): #6
                                    values.append(table_1.values[i] + table_2.values[j])
                            elif check_table == 2:
                                if (table_2.values[i][index_column_where_1] > command[9]) and (table_1.values[i][index_column_join_1] == table_2.values[j][index_column_join_2]): #6
                                    values.append(table_1.values[i] + table_2.values[j])
                            j += 1
                        i += 1
                    if values == []:
                        i = 0
                        while i < len(table_1.values):
                            values.append(table_1.values[i] + table_2.values[i])
                            i += 1
                        table = [[*table_1.columns, *table_2.columns], *values]
                        tab = PrettyTable(table[0])
                        tab.add_rows(table[1:])
                        print(tab)
                    else:
                        table = [[*table_1.columns, *table_2.columns], *values]
                        tab = PrettyTable(table[0])
                        tab.add_rows(table[1:])
                        print(tab)
                else:
                    table_1 = self.tables[command[1]]
                    table_2 = self.tables[command[3]]
                    values = []
                    if command[8] in table_1.columns:
                        index_column_where_1 = table_1.columns.index(command[8])
                        check_table_1 = 1
                    elif command[8] in table_2.columns:
                        index_column_where_1 = table_2.columns.index(command[8])
                        check_table_1 = 2
                    else:
                        print(f"There is no such column with name {command[8]}")
                        return
                    if command[9] in table_1.columns:
                        index_column_2 = table_1.columns.index(command[9])
                        check_table_2 = 1
                    elif command[9] in table_2.columns:
                        index_column_2 = table_2.columns.index(command[9])
                        check_table_2 = 2
                    else:
                        print(f"There is no such column with name {command[9]}")
                        return
                    i = 0
                    index_column_join_1 = table_1.columns.index(command[5])
                    index_column_join_2 = table_2.columns.index(command[6])
                    while i < len(table_1.values):
                        j = 0
                        while j < len(table_2.values):
                            if check_table_1 == 1 and check_table_2 == 1:
                                if (table_1.values[i][index_column_where_1] > table_1.values[i][index_column_2]) and (table_1.values[i][index_column_join_1] == table_2.values[j][index_column_join_2]):
                                    values.append(table_1.values[i] + table_2.values[j])
                            elif check_table_1 == 1 and check_table_2 == 2:
                                if (table_1.values[i][index_column_where_1] > table_2.values[i][index_column_2]) and (table_1.values[i][index_column_join_1] == table_2.values[j][index_column_join_2]):
                                    values.append(table_1.values[i] + table_2.values[j])
                            elif check_table_1 == 2 and check_table_2 == 1:
                                if (table_2.values[i][index_column_where_1] > table_1.values[i][index_column_2]) and (table_1.values[i][index_column_join_1] == table_2.values[j][index_column_join_2]):
                                    values.append(table_1.values[i] + table_2.values[j])
                            else:
                                if (table_2.values[i][index_column_where_1] > table_2.values[i][index_column_2]) and (table_1.values[i][index_column_join_1] == table_2.values[j][index_column_join_2]):
                                    values.append(table_1.values[i] + table_2.values[j])
                            j += 1
                        i += 1
                    if values == []:
                        i = 0
                        while i < len(table_1.values):
                            values.append(table_1.values[i] + table_2.values[i])
                            i += 1
                        table = [[*table_1.columns, *table_2.columns], *values]
                        tab = PrettyTable(table[0])
                        tab.add_rows(table[1:])
                        print(tab)
                    else:
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
        elif (command[2] == "JOIN") and (command[4] == "WHERE"):
            table_1 = self.tables[command[1]]
            table_2 = self.tables[command[3]]
            if len(table_1.columns + table_2.columns) != len(set(table_1.columns + table_2.columns)):
                print("Сolumns in tables are not unique!")
                return
            values = []
            if len(table_1.values) == len(table_2.values):
                if command[6][0] == '"':
                    if command[5] in table_1.columns:
                        index_column_1 = table_1.columns.index(command[5])
                        check_table = 1
                    elif command[5] in table_2.columns:
                        index_column_1 = table_2.columns.index(command[5])
                        check_table = 2
                    else:
                        print(f"There is no such column with name {command[5]}")
                        return
                    command[6] = command[6][1:-1]
                    i = 0
                    while i < len(table_1.values):
                        if check_table == 1:
                            if table_1.values[i][index_column_1] > command[6]:
                                values.append(table_1.values[i] + table_2.values[i])
                        elif check_table == 2:
                            if table_2.values[i][index_column_1] > command[6]:
                                values.append(table_1.values[i] + table_2.values[i])
                        i += 1
                    if values == []:
                        i = 0
                        while i < len(table_1.values):
                            values.append(table_1.values[i] + table_2.values[i])
                            i += 1
                        table = [[*table_1.columns, *table_2.columns], *values]
                        tab = PrettyTable(table[0])
                        tab.add_rows(table[1:])
                        print(tab)
                    else:
                        table = [[*table_1.columns, *table_2.columns], *values]
                        tab = PrettyTable(table[0])
                        tab.add_rows(table[1:])
                        print(tab)
                else:
                    table_1 = self.tables[command[1]]
                    table_2 = self.tables[command[3]]
                    values = []
                    if command[5] in table_1.columns:
                        index_column_1 = table_1.columns.index(command[5])
                        check_table_1 = 1
                    elif command[5] in table_2.columns:
                        index_column_1 = table_2.columns.index(command[5])
                        check_table_1 = 2
                    else:
                        print(f"There is no such column with name {command[5]}")
                        return
                    if command[6] in table_1.columns:
                        index_column_2 = table_1.columns.index(command[6])
                        check_table_2 = 1
                    elif command[6] in table_2.columns:
                        index_column_2 = table_2.columns.index(command[6])
                        check_table_2 = 2
                    else:
                        print(f"There is no such column with name {command[5]}")
                        return
                    i = 0
                    while i < len(table_1.values):
                        if check_table_1 == 1 and check_table_2 == 1:
                            if table_1.values[i][index_column_1] > table_1.values[i][index_column_2]:
                                values.append(table_1.values[i] + table_2.values[i])
                        elif check_table_1 == 1 and check_table_2 == 2:
                            if table_1.values[i][index_column_1] > table_2.values[i][index_column_2]:
                                values.append(table_1.values[i] + table_2.values[i])
                        elif check_table_1 == 2 and check_table_2 == 1:
                            if table_2.values[i][index_column_1] > table_1.values[i][index_column_2]:
                                values.append(table_1.values[i] + table_2.values[i])
                        else:
                            if table_2.values[i][index_column_1] > table_2.values[i][index_column_2]:
                                values.append(table_1.values[i] + table_2.values[i])
                        i += 1
                    if values == []:
                        i = 0
                        while i < len(table_1.values):
                            values.append(table_1.values[i] + table_2.values[i])
                            i += 1
                        table = [[*table_1.columns, *table_2.columns], *values]
                        tab = PrettyTable(table[0])
                        tab.add_rows(table[1:])
                        print(tab)
                    else:
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