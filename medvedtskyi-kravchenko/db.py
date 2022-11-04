class table:
    name = ""
    column_params = []
    columns = []
    data = []
    
    def __init__(self, table_name: str, table_columns: list, table_params: list) -> None:
        self.name = table_name
        self.column_params = table_params
        self.columns = table_columns
    
    def add_row(self, row_data: list) -> None:
        old_data = self.data
        old_data.append(row_data)
        self.data = old_data
    
    def print_table(self) -> None:
        print(self.columns)
        for i in self.data:
            print(i)