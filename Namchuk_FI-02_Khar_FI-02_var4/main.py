import parser1
from Table import Table

if __name__ == "__main__":
    database = {}
    command = None
    print('Enter:')
    line = input()
    while True:
        if line[-1] != ';':
            line = line + ' ' + input()
        else:
            command = parser1.parse(line)
            #print(command)
            if command[0] == 'CREATE':
                Table.create(command, database)
            elif command[0] == 'INSERT':
                Table.insert(command, database)
            elif command[0] == 'SELECT':
                Table.select(command, database)
            else:
                print(command)
            print('Enter:')
            line = ' '