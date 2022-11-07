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
    tables = []
    while True:
        query = str(input("> "))
        try:
            command, table_name, data = myparser.parse(query)
            if command == "['exit']":
                break
            list_data = data.asList()
            if command == "CREATE":
                if search_table(tables, table_name) == -1:
                    tables.append(table(table_name, list_data, []))
                    print(f"Succesfully created table \"{table_name}\"")
                else:
                    print("Table with this name already exists")
            if command == "INSERT INTO":
                table_id = search_table(tables, table_name)
                if table_id == -1:
                    print("Table doesn\'t exists")
                else:
                    if len(tables[table_id].columns) == len(list_data):
                        tables[table_id].new_row(list_data)
                        print(f"Succesfully inserted into \'{table_name}\'")
                    else:
                        print(f"\'{table_name}\' have {len(tables[table_id].columns)} columns, but you gave {len(list_data)} arguments")
            if command == "SELECT FROM":
                table_id = search_table(tables, table_name)
                if table_id == -1:
                    print("Table doesn\'t exists")
                else:
                    select(tables[table_id], list_data[0], list_data[1]).print_table()
              
        except Exception as e:
            print(str(e))
    
    
    
    # i, j, k = myparser.parse('SELECT FROM kost WHERE name < kossst;')
    # print(type(i), i)
    # print(type(j), j)
    # print(type(k), k)
    # tables = []
    # tables.append(table(j, ['name', 'bd'], []))
    # tables[0].new_row(['kost', 'ut'])
    # tables[0].new_row(['kosst', 'ut'])
    # tables[0].new_row(['kossst', 'ut'])
    # tables[0].new_row(['kosssst', 'ut'])
    # select(tables[0], k[0], k[1]).print_table()