import regex as re
re_create = '(CREATE|create)[ ]+[a-zA-Z1-9_]+[ ]*[(]{1}([ ]*[a-zA-Z1-9]*[ ]*[\[(INDEXED|indexed)\]]?[,]?)+[)]{1}'
re_insert = '(INSERT|insert)[ ]+(INTO|into)?[ ]+[a-zA-Z1-9_]{2,}[ ]*[(]{1}[a-zA-Z1-9,\'" ]*[)]{1}[ ]*[\n]*(VALUES|values)[ ]*[(]{1}[ ]*[a-zA-Z1-9,\'" ]*[ ]*[)]{1}'
re_select = '(select)\s+((COUNT\(|SUM\(|MAX\(|MIN\(){1}\s*[\w]+(?<=\([\w]+)\)(\,\s*|\s+)+|\w+(\,\s*|\s+)+)+from\s+\w+(\s+group_by\s+[a-zA-Z1-9_, ]+)?((\s+where\s+[a-zA-Z1-9><=\-\'\"]+)(\s+group_by[a-zA-Z1-9_, ]+)?)?'

def querry_formatting(querry):
    if (querry[0] == ' '):
        querry = querry[1:]
    return querry.lower()


def is_querry_correct(querry):

    if (len(querry) == 0):
        print("Empty querry")
        return False
    elif (re.match(re_create, querry, flags=re.IGNORECASE)):
        print("Correct")
        return True
    elif (re.match(re_insert, querry, flags=re.IGNORECASE)):
        print("Correct")
        return True
    elif (re.match(re_select, querry, flags=re.IGNORECASE)):
        print("Correct")
        return True
    else:
        print("Wrong syntax", querry)
        return False




def main():
    print("You can start with these commands: \n CREATE table_name (column_name *[INDEXED] [, ...]); \n INSERT [INTO] table_name (“value” [, ...]) [0,0]; \n SELECT ... FROM ... ")

    lines = []
    while True:
        line = input('> ' if len(lines) == 0 else '... ')
        if line:
            lines.append(line)
            if ';' in line:
                break

    querry = ''.join(lines)
    querry = querry.replace('\n', ' ')
    commands = querry.split(';')
    commands.pop()
    i = 0
    querry_counter = len(commands)
    while i < querry_counter:
        commands[i] = querry_formatting(commands[i])
        if not is_querry_correct(commands[i]): 
            break
        i += 1
main()