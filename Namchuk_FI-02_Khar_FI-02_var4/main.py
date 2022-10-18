import parser1

def create(command):
    print(f"Table: {command[1]} with columns: {tuple(command[2])} was successfully created!")
def insert(command):
    print(f"Insert in {command[1]} values: {tuple(command[2])}")
def select(command):
    print(f"Select ready to use")
if __name__ == "__main__":
    command = None
    print('Enter:')
    line = input()
    while True:
        if line[-1] != ';':
            line = line + ' ' + input()
        else:
            command = parser1.parse(line)
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

