import parser1

if __name__ == "__main__":
    command = None
    print('Enter:')
    line = input()
    while True:
        if line[-1] != ';':
            line = line + ' ' + input()
        else:
            command = parser1.parse(line)
            print('Enter:')
            line = ' '