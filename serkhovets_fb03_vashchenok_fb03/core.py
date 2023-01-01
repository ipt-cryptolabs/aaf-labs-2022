"""
Core file
"""
import pandas as pd
import pickle
from prettytable import PrettyTable


class Table:
    def __init__(self, name_table: str, titles: list, index=None):
        if index is None:
            index = {}
        self.name_table = name_table
        self.titles = []
        self.index = index
        for pos in range(len(titles)):
            if titles[pos] != titles[pos].upper():
                self.titles.append(titles[pos])
        self.items = []

    def __lt__(self, other):
        return self.name_table < other.name_table

    def __str__(self):
        return self.name_table

    def add_items(self, items: list):
        if len(items) != len(self.titles) and len(self.titles) > len(items):
            for num in range(len(self.titles) - len(items)):
                items.append("")
            self.items.append(items)
        elif len(self.titles) < len(items):
            self.items.append(items[:len(self.titles)])
        else:
            self.items.append(items)

    # def get_item(self, title):
    #     position = self.titles.index(title)
    #     return self.items[position]

    def get_titles(self):
        return self.titles

    def get_items(self):
        return self.items

    def get_name(self):
        return self.name_table

    def print(self):
        # +----+--------+----------------+
        # | id | name   | favourite_food |
        # +----+--------+----------------+
        # | 1  | Murzik | Sausages       |
        # | 2  | Pushok | Fish           |
        # +----+--------+----------------+
        if len(self.items) == 0:
            table = PrettyTable([self.name_table])
            table.add_row([" --- No items --- "])
            print(table)
            return False
        table = PrettyTable(self.titles)
        for item in self.items:
            table.add_row(item)
        print(table)


class SQL:
    def __init__(self):
        self.tables = []

    def __add__(self, table: Table):
        self.tables.append(table)
        self.tables.sort()

    def append(self, table: Table):
        self.tables.append(table)
        self.tables.sort()

    def print_tables(self):
        table = PrettyTable(["TABLES"])
        if len(self.tables) == 0:
            table.add_row([" --- No table --- "])
        else:
            for table_name in self.tables:
                table.add_row([str(table_name)])
        print(table)

    def print_table(self, title):
        for table in self.tables:
            if str(table) == title:
                table.print()
                return True
        print(f"Sorry... no table {title} :(")
        return False

    def function_print_table(self, title, vars: list, symbols: list):
        try:
            if len(vars) >= 2:
                and_check = None
                d = {}
                for table in self.tables:
                    if str(table) == title:
                        titles = table.get_titles()
                        items = table.get_items()
                        for i in range(len(titles)):
                            temp_list = []
                            for item in items:
                                temp_list.append(item[i])
                            d[titles[i]] = temp_list
                        break
                pdframe = [pd.DataFrame(data=d), pd.DataFrame(data=d)]
                if "OR" in vars:
                    vars.remove("OR")
                    and_check = False
                elif "AND" in vars:
                    vars.remove("AND")
                    and_check = True
                s = 0
                for num_var in range(0, len(vars)-1, 2):
                    temp = pdframe[s][vars[num_var]].to_list()
                    temp_list = []
                    for i in pdframe[s][vars[num_var]].to_list():
                        if symbols[s] == "<=":
                            if i <= vars[num_var + 1]:
                                temp_list.append(i)
                        elif symbols[s] == ">=":
                            if i >= vars[num_var + 1]:
                                temp_list.append(i)
                        elif symbols[s] == "=" or symbols[s] == "==":
                            if i == vars[num_var + 1]:
                                temp_list.append(i)
                        elif symbols[s] == "<":
                            if i < vars[num_var + 1]:
                                temp_list.append(i)
                        elif symbols[s] == ">":
                            if i > vars[num_var + 1]:
                                temp_list.append(i)
                        else:
                            continue
                    for i in temp_list:
                        temp[temp.index(i)] = "%"
                    for num in range(len(temp)):
                        if temp[num] != "%":
                            pdframe[s] = pdframe[s].drop(num)
                    pdframe[s].reset_index(drop=True, inplace=True)
                    s += 1
                if and_check:
                    pdframe = pdframe[0].merge(pdframe[1], how='inner')
                else:
                    pdframe = pdframe[0].merge(pdframe[1], how='outer')
                data = []
                titles = []
                for i in pdframe.keys():
                    titles.append(i)
                    data += pdframe[i].to_list()
                result = []
                for num in range(int(len(data) / len(titles))):
                    result.append(list(data[x] for x in range(num, len(data), int(len(data) / len(titles)))))
                if len(result) == 0:
                    table = PrettyTable(["Sorry"])
                    table.add_row([" --- No items --- "])
                    print(table)
                    return False
                table = PrettyTable(titles)
                for item in result:
                    table.add_row(item)
                print(table)
                return True
            return False
        except Exception:
            print(f"Sorry... Check your input! :(")

    def get_tables(self):
        return self.tables

    def get_table(self, title):
        for table in self.tables:
            if str(table) == title:
                return table
        return False


if __name__ == '__main__':
    with open("MySQL.pickle", 'rb') as f:
        MySQL = pickle.load(f)
    MySQL.print_table("cats")
    MySQL.function_print_table("cats", ['name', 'Murzik', 'OR', 'name', 'Pushok'], ['=', '='])
