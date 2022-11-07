from tabulate import tabulate

class table:
    
    def __init__(self, table_name: str, table_columns: list, table_params: list) -> None:
        self.name = table_name
        self.columns = table_columns
        self.column_params = table_params
        self.data = []
    
    def new_row(self, row_data: list) -> None:
        self.data.append(row_data)
            
    def print_table(self) -> None:
        print(tabulate(self.data, headers=self.columns, tablefmt='grid'))

    def get_col_id(self, column: str) -> int:
        col_id = [i for i, s in enumerate(self.columns) if s == column]
        if col_id == []:
            return -1
        else:
            return col_id[0]


def select(t: table, column: str, data: str) -> table:
    col_id = t.get_col_id(column)
    if col_id == -1:
        raise Exception("Column not found")
    t2 = table("select", t.columns, [])
    t2.data = [s for i, s in enumerate(t.data) if s[col_id] < data]
    return t2
    