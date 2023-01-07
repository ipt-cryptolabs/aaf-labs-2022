import parser1
from Table import Table
from database import DataBase

if __name__ == "__main__":
    dataBase = DataBase()
    command = None
    line = ' '
    print('Enter:')
    line = line + input()
    while True:
        if line[-1] != ';':
            line = line + ' ' + input()
        else:
            command = parser1.parse(line)
            if command[0] == 'CREATE':
                dataBase.append_table(command)
            elif command[0] == 'INSERT':
                if command[1] in dataBase.tables.keys():
                    dataBase.tables[command[1]].insert(command[2])
                else:
                    print(f"Table with name {command[1]} doesn`t exists")
            elif command[0] == 'SELECT':
                dataBase.select(command)
            else:
                print(command)
            print('Enter:')
            line = ' '