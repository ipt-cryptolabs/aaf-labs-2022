import re


def parse(line):
    line = line.lstrip()
    command = re.sub(r'\s+', ' ', line)
    command = re.sub(r'\(\s*', '(', command) # + or * ?
    command = re.sub(r'\s*,\s*', ',', command)
    command = re.sub(r'\s*\)\s*', ')', command)
    split_command = command.split(' ')
    result_command = []
    if re.match(r'(?i)create\s+[a-zA-Z][a-zA-Z0-9_]*\s+\(.+\)\s*\;', line):
        parenthesizedExpression = re.findall(r'\(.*\)', command)
        parameters = parenthesizedExpression[0][1:-1]
        parameters = parameters + ','
        findParameters = re.findall(r'[a-zA-Z][a-zA-Z0-9_]*,', parameters)
        concatParameters = ''
        for i in findParameters:
            concatParameters += i
        if concatParameters == parameters:
            result_command.append("CREATE")
            del split_command[0]
            result_command.append(split_command[0])
            del split_command[0]
            split_command[0] = split_command[0].replace(split_command[0][0], '')
            split_command[0] = split_command[0].replace(split_command[0][-1], '')
            split_command[0] = split_command[0].replace(split_command[0][-1], '')
            result_command.append(split_command[0].split(','))
            print(result_command)
            return result_command
    elif re.match(r'(?i)(insert|insert\s+into)\s+[a-zA-Z][a-zA-Z0-9_]*\s+\(.+\)\s*\;', line):
        line = re.sub(r'\s*\)\s*;$', ',);', line)
        parenthesized_expression = re.findall(r'\(.*\)', line)
        parameters = parenthesized_expression[0][1:-1]
        parenthesizedExpression = re.findall(r'\s*\"\s*\w+\s*\"\s*\,\s*', parameters)
        concatParameters = ''
        for i in parenthesizedExpression:
            concatParameters += i
        if concatParameters == parameters:
            if re.match(r'(?i)(insert\s+into)', line):
                result_command.append('INSERT')
                del split_command[0]
                del split_command[0]
                result_command.append(split_command[0])
                del split_command[0]
                args = re.findall(r'\".*?\"', line)
                result_command.append(args)
                print(result_command)
                return result_command
    elif re.match(r'(?i)(select\s+from)\s+[a-zA-Z][a-zA-Z0-9_]*(|\s+(?i)(where)\s+[a-zA-Z][a-zA-Z0-9_]*\s+\>\s+([a-zA-Z][a-zA-Z0-9_]*|\s*\"\s*.*\s*\")|\s+(?i)(join)\s+[a-zA-Z][a-zA-Z0-9_]*(|\s+(?i)(on)\s+[a-zA-Z][a-zA-Z0-9_]*\s+\=\s+[a-zA-Z][a-zA-Z0-9_]*))\s*\;', line):
        split_command[-1] == split_command[-1][:-1]
        args = re.findall(r'\".*?\"', line)
        if args != []:
            split_command[-1] = args[0]
        print(split_command)
        result_command.append('SELECT')
        del split_command[0]
        del split_command[0]
        result_command.append(split_command[0])
        del split_command[0]
        print(split_command, result_command, sep='\n\n')
# SELECT FROM cats WHERE name > "Murzi  )  k";