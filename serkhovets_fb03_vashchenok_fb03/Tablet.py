from BinTree import *
from Operation import *

ID = 'ID'
INDEX = 'INDEX'


class Table:
    def __init__(self, columns, indexesColumn):
        self.table = list()
        self.columns = dict()
        i = 0
        for column in columns:
            self.columns[column] = {}
            self.columns[column][ID] = i
            i += 1
            if column in indexesColumn:
                self.columns[column][INDEX] = Node(None, None)
                continue
            self.columns[column][INDEX] = None

    def IndexCondition(self, index, condition, number):
        if condition.type == 'EQUAL':
            return self.columns[index][INDEX].find(number)
        if condition.type == 'NOT_EQUAL':
            return self.columns[index][INDEX].find(number)
        # if condition.type == 'MORE_EQUAL':
        #
        # if condition.type == 'MORE':
        #
        # if condition.type == 'MORE_LESS':
        #
        # if condition.type == 'LESS':

    def Condition(self, a, condition, b):
        i = 0
        IDs = []
        for row in self.table:
            if not row:
                continue
            value = row[self.columns[a][ID]]
            if operations[condition.type](value, b):
                IDs.append(i)
            i += 1
        return IDs


    def Insert(self, insertVar):
        id = len(self.table)
        self.table.append(insertVar)
        for column in self.columns:
            if self.columns[column][INDEX]:
                self.columns[column][INDEX].insert(insertVar[self.columns[column][ID]], id)

    def CheckColumns(self, length):
        if length != len(self.columns.keys()):
            raise Exception('Table has this number of columns ', len(self.columns))



    def Select(self, a, condition, b):
        if a.type == b.type:
            rows = []
            i = 0
            for row in self.table:
                if not row:
                    continue
                if operations[condition.type](row[self.columns[a.text][ID]], row[self.columns[b.text][ID]]):
                    rows.append(i)
                i += 1
            return rows
        elif a.type == 'VAR':
            if self.columns[a.text][INDEX]:
                return self.IndexCondition(a.text, condition, int(b.text))
            return self.Condition(a.text, condition, int(b.text))
        elif self.columns[b.text][INDEX]:
            if self.columns[b.text][INDEX]:
                return self.IndexCondition(b.text, condition, int(a.text))
            return self.Condition(int(a.text), condition, b.text)


