class table:
    name = ""
    column_params = []
    columns = []
    data = []
    
    def __init__(self, table_name: str, table_columns: list, table_params: list) -> None:
        self.name = table_name
        cols = ["id"]
        for i in table_columns:
            cols.append(i)
        self.columns = cols
        self.column_params = table_params
    
    def new_row(self, row_data: list) -> None:
        def add_row(rd_id: int, rd: list) -> None:
            new_data = [str(rd_id)]
            for i in rd:
                new_data.append(i)
            old_data = self.data
            old_data.append(new_data)
            self.data = old_data
        if self.data != []:
            row_id = int(self.data[-1][0]) + 1
        else:
            row_id = 0
        add_row(row_id, row_data)
            
    def print_table(self) -> None:
        print(self.name)
        print(self.columns)
        for i in self.data:
            print(i)
    
    def get_row(self, row_id: int) -> list:
        for s in self.data:
            if int(s[0]) == row_id:
                return s 
        return []
    
    def where(self, column_name: str, data: str) -> int:
        col_id = -1
        for i, s in enumerate(self.columns):
            if s == column_name:
                col_id = i
                break
        if col_id == -1:
            return col_id
        for s in self.data:
            if(s[col_id] == data):
                return int(s[0])
        return -1
        