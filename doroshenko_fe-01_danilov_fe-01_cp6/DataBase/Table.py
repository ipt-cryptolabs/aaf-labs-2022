#!/usr/bin/python
# -*- coding: utf-8 -*-
# from DataBase.Tree import Node

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
            self.columns[column][INDEX] = None
          
    def DoseColumnExist(self, column):
        if column not in self.columns:
            raise Exception('There is no such column as', column)
          
    def findInColumns(
        self,
        columns,
        groupByFields=[],
        fieldsToAggregate=[],
        ):

        for column in columns:
            self.DoseColumnExist(column)

    def Insert(self, varsToInsert):

        id = len(self.table)
        self.table.append(varsToInsert)
        for column in self.columns:
            if self.columns[column][INDEX]:
                self.columns[column][INDEX].insert(varsToInsert[self.columns[column][ID]],
                        id)
      
    def CheckNumberOfColumns(self, length):
        if length != len(self.columns.keys()):
            raise Exception('Table has this number of columns ',
                            len(self.columns))

    def CheckIfInColumns(self, columns):
        allCorrectColumns = len([column for column in columns
                                if column.text in self.columns])
        if len(columns) != allCorrectColumns:
            raise Exception('There is no such columns as', [column
                            for column in columns if column
                            not in self.columns])

    def Select(self, column_where, column_equals):
        if column_where is None:
            return (self.columns.keys(), self.table)

        self.DoseColumnExist(column_where)
        column_where_id = self.columns[column_where]['ID']
        result_table = []
        for row in self.table:
            if row[column_where_id] == column_equals:
                result_table.append(row)
        return (self.columns.keys(), result_table)
