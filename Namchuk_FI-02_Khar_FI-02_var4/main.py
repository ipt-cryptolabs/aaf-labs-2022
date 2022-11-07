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
                dataBase.tables[command[1]].insert(command[2])
            elif command[0] == 'SELECT':
                dataBase.select(command)
            else:
                print(command)
            print('Enter:')
            line = ' '