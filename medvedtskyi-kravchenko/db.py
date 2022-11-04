import pandas as pd
import copy


class table:
    name = ""
    column_params = []
    columns = []
    data = pd.DataFrame()
    
    def __init__(self, table_name: str, table_columns: list, table_params: list) -> None:
        self.name = table_name
        self.column_params = table_params
        self.columns = table_columns
        df1 = {}
        for i in table_columns:
            df1[i] = []
        df = pd.DataFrame(df1)
        self.data = df
    
    def add_row(self, row: list) -> None:
        old_data = copy.deepcopy(self.data)
        addition_data1 = {}
        for i in range(len(self.columns)):
            addition_data1[self.columns[i]] = [row[i]]
        addition_data = pd.DataFrame(addition_data1)
        new_data = pd.concat([old_data, addition_data], ignore_index=True)
        self.data = new_data
    
    def delete_row(self, id: int) -> None:
        old_data = copy.deepcopy(self.data)
        new_data = old_data.drop(labels=id, axis=0)
        self.data = new_data