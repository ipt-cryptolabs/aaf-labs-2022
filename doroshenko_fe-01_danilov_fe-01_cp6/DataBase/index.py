from DataBase.Table import Table
from prettytable import PrettyTable

class DataBase:
    def __init__(self):
        self.dataBase = {}
        self.allTablesName = []
    def PrintDB(self):
        for Table in  self.allTablesName:
            Tab = self.dataBase[Table]
            print(Tab.columns)
            print(Tab.indexedColumns)
            print(Tab.table)
            for key in Tab.indexes.keys():
                print(key, end=": ")
                Tab.indexes[key].PrintTree()
                print()

    def CreateTable(self, name, columns, indexes):
        if name not in self.allTablesName:
            self.allTablesName.append(name)
            self.dataBase[name] = Table(columns, indexes)
            print(f'Table "{name}" created successfully')
        else :
            raise Exception ('Table with this name already exists')

    def Insert(self, name, varsToInsert):
        self.DoseTableExist(name)
        self.dataBase[name].CheckNumberOfColumns(len(varsToInsert))
        self.dataBase[name].Insert(varsToInsert)
        print('row inserted in table', name)

    def Select(self, table_name, column_where, column_equals):
        self.DoseTableExist(table_name)
        data = self.dataBase[table_name].Select(column_where, column_equals)
        print('====',table_name.upper(),'====')
        self.PrintTable(data[0], data[1])
          
        
    def DoseTableExist(self, name):
        if name not in self.allTablesName:
            raise Exception ('There is no table with name', name)
          
    def PrintTable(self, names, rows):
        table =  PrettyTable()
        table.field_names = names
        table.add_rows(rows)
        print(table)

    




