import parser1

if __name__ == "__main__":
    print('Enter:')
    line = input()
    while True:
        if line[-1] != ';':
            line = line + ' ' + input()
        else:
            parser1.parse(line)
            print('Enter:')
            line = ' '