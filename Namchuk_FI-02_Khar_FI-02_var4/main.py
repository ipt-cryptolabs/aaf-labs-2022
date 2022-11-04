import parser1
from Table import Table


def create(command):
    table = Table(command)
    database[table.name]=table
    print(f"Table: {command[1]} with columns: {tuple(command[2])} was successfully created!")


def insert(command):
    database[command[1]].values.append(command[2])
    print(f"Insert in {command[1]} values: {tuple(command[2])}")


def select(command):
    values_table = database[command[1]].values
    columns_table = database[command[1]].columns
    if command == ['SELECT', command[1]]:
        print(*columns_table)
        for i in range(len(values_table)):
            print(*values_table[i])


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
                create(command)
            elif command[0] == 'INSERT':
                insert(command)
            elif command[0] == 'SELECT':
                select(command)
            else:
                print(command)
            print('Enter:')
            line = ' '