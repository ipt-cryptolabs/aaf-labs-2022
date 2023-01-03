import Checker


class Query:
    pass


class QSelect(Query):
    def __init__(self, table_title: str, columns: list):
        self.columns = columns
        self.table_title = table_title


class QInsert(Query):
    def __init__(self, table_title: str, columns: list, values: list):
        self.columns = columns
        self.table_title = table_title
        self.values = values


class QCreate(Query):
    def __init__(self, table_title: str, columns: list):
        self.table_title = table_title
        self.columns = columns
