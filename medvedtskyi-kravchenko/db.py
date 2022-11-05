from tabulate import tabulate

class table:
    
    def __init__(self, table_name: str, table_columns: list, table_params: list) -> None:
        self.name = table_name
        cols = []
        for i in table_columns:
            cols.append(i)
        self.columns = cols
        self.column_params = table_params
        self.data = []
    
    def new_row(self, row_data: list) -> None:
        self.data.append(row_data)
            
    def print_table(self) -> None:
        print(tabulate(self.data, headers=self.columns, tablefmt='grid'))

def select(t: table, column: str, data: str) -> table:
    col_id = [i for i, s in enumerate(t.columns) if s == column]
    if col_id == []:
        return table("select", t.columns, [])
    t2 = table("select", t.columns, [])
    for s in t.data:
        if(s[col_id[0]] == data):
            t2.new_row(s)
    return t2
    