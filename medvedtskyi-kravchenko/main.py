from db import *
import myparser

def search_table(t: list, name: str) -> int: # returns id of table or -1 if table not found
    res = -1
    for i, s in enumerate(t):
        if s.name == name:
            res = i
            break
    return res
            
if __name__ == "__main__":
    print("Command examples:")
    print(" > CREATE some_table (first_column, second_column);")
    print(" > INSERT INTO some_table (\"1\", \"some data\");")
    print(" > SELECT * FROM some_table;")
    print(" > SELECT FROM some_table WHERE second_column < \"some datb\";")
    print("Starting program...")
    tables = []
    while True:
        query = str(input("> "))
        try:
            result = myparser.parse(query)
            command = result[0]
            if command == "exit":
                break
            table_name = result[1]
            if result[0] == "CREATE":
                column_names = []
                for i in range(2, len(result)):
                    column_names.append(result[i])
                if search_table(tables, table_name) == -1:
                    tables.append(table(table_name, column_names, []))
                    print(f"Succesfully created table \"{table_name}\"")
                else:
                    print("Table with this name already exists")
            if result[0] == "INSERT INTO":
                table_id = search_table(tables, table_name)
                if table_id == -1:
                    print("Table doesn\'t exists")
                else:
                    data = []
                    for i in range(2, len(result)):
                        data.append(result[i])
                    if len(tables[table_id].columns) == len(data):
                        tables[table_id].new_row(data)
                        print(f"Succesfully inserted into \'{table_name}\'")
                    else:
                        print(f"\'{table_name}\' have {len(tables[table_id].columns)} columns, but you gave {len(data)} arguments")
            if command == "SELECT FROM":
                table_id = search_table(tables, table_name)
                if table_id == -1:
                    print("Table doesn\'t exists")
                else:
                    data = []
                    for i in range(2, len(result)):
                        data.append(result[i])
                    select(tables[table_id], data[0], data[1]).print_table()
            if command == "SELECT * FROM":
                table_id = search_table(tables, table_name)
                if table_id == -1:
                    print("Table doesn\'t exists")
                else:
                    tables[table_id].print_table()
        except Exception as e:
            print(str(e))