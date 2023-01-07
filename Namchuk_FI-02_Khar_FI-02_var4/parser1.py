import re


def parse(line):
    line = line.lstrip()
    command = re.sub(r'\s+', ' ', line)
    command = re.sub(r'\(\s*', '(', command)  # + or * ?
    command = re.sub(r'\s*,\s*', ',', command)
    command = re.sub(r'\s*\)\s*', ')', command)
    split_command = command.split(' ')
    result_command = []
    if re.match(r'(?i)create\s+[a-zA-Z][a-zA-Z0-9_]*\s*\(.+\)\s*\;', line):
        parenthesizedExpression = re.findall(r'\(.*\)', command)
        parameters = parenthesizedExpression[0][1:-1]
        parameters = parameters + ','
        if re.match(r'.+\s+(?i)indexed\s*.+', parameters):
            findParameters = re.findall(r'([a-zA-Z][a-zA-Z0-9_]* (?i)indexed,|[a-zA-Z][a-zA-Z0-9_]*,)', parameters)
            concatParameters = ''
            if findParameters == []:
                return "Incorrect command syntax"
            for i in findParameters:
                concatParameters += i
                i = i.split(' ')
                if re.match(r'(?i)indexed', i[0]):
                    return f"Сolumn can not be named {i[0]}"
            if concatParameters == parameters:
                result_command.append("CREATE")
                table_name = re.findall(r'[a-zA-Z][a-zA-Z0-9_]*\(', split_command[1])
                if table_name != []:
                    split_command[1] = table_name
                    split_command[1] = split_command[1][0][:-1]
                    parenthesizedExpression[0] = re.sub(r'\)', ');', parenthesizedExpression[0])
                    split_command.append(parenthesizedExpression[0])
                result_command.append(split_command[1])
                parameters_split = parameters.split(',')
                del parameters_split[-1]
                result_command.append(parameters_split)
                return result_command
            else:
                return "Incorrect command syntax"
        else:
            findParameters = re.findall(r'[a-zA-Z][a-zA-Z0-9_]*,', parameters)
            concatParameters = ''
            if findParameters == []:
                return "Incorrect command syntax"
            for i in findParameters:
                concatParameters += i
            if concatParameters == parameters:
                result_command.append("CREATE")
                table_name = re.findall(r'[a-zA-Z][a-zA-Z0-9_]*\(', split_command[1])
                if table_name != []:
                    split_command[1] = table_name
                    split_command[1] = split_command[1][0][:-1]
                    parenthesizedExpression[0] = re.sub(r'\)', ');', parenthesizedExpression[0])
                    split_command.append(parenthesizedExpression[0])
                result_command.append(split_command[1])
                split_command[2] = split_command[2].replace(split_command[2][0], '')
                split_command[2] = split_command[2].replace(split_command[2][-1], '')
                split_command[2] = split_command[2].replace(split_command[2][-1], '')
                result_command.append(split_command[2].split(','))
                return result_command
            else:
                return "Incorrect command syntax"
    elif re.match(r'(?i)(insert|insert\s+into)\s+[a-zA-Z][a-zA-Z0-9_]*\s*\(.+\)\s*\;', line):
        line = re.sub(r'\s*\)\s*;$', ',);', line)
        parenthesized_expression = re.findall(r'\(.*\)', line)
        parameters = parenthesized_expression[0][1:-1]
        parenthesizedExpression = re.findall(r'\s*\"\s*.+\s*\"\s*\,\s*', parameters)
        concatParameters = ''
        for i in parenthesizedExpression:
            concatParameters += i
        if concatParameters == parameters:
            result_command.append('INSERT')
            args = re.findall(r'\".*?\"', line)
            i = 0
            while i < len(args):
                args[i] = args[i][1:-1]
                i += 1
            if re.match(r'(?i)(insert\s+into)', line):
                result_command.append(split_command[2])
                result_command.append(args)
            else:
                result_command.append(split_command[1])
                result_command.append(args)
            result_command[1] = re.sub(r'\(.+', '', result_command[1])
        else:
            return "Incorrect command syntax"
        return result_command
    elif re.match(
            r'(?i)(select\s+from)\s+[a-zA-Z][a-zA-Z0-9_]*((|\s+(?i)(join)\s+[a-zA-Z][a-zA-Z0-9_]*(|\s+(?i)(on)\s+[a-zA-Z][a-zA-Z0-9_]*\s+\=\s+[a-zA-Z][a-zA-Z0-9_]*)|\s+(?i)(where)\s+[a-zA-Z][a-zA-Z0-9_]*\s+\>\s+([a-zA-Z][a-zA-Z0-9_]*|\s*\"\s*.*\s*\"))|\s+(?i)(join)\s+[a-zA-Z][a-zA-Z0-9_]*(|\s+(?i)(on)\s+[a-zA-Z][a-zA-Z0-9_]*\s+\=\s+[a-zA-Z][a-zA-Z0-9_]*)\s+(?i)(where)\s+[a-zA-Z][a-zA-Z0-9_]*\s+\>\s+([a-zA-Z][a-zA-Z0-9_]*|\s*\"\s*.*\s*\"))\s*\;',
            line):
        split_command[-1] = split_command[-1][:-1]
        args = re.findall(r'\".*?\"', line)
        if args != []:
            split_command[-1] = args[0]
        result_command.append("SELECT")
        result_command.append(split_command[2])
        if len(split_command) == 5:
            result_command.append("JOIN")
            result_command.append(split_command[4])
        elif len(split_command) == 7:
            result_command.append("WHERE")
            result_command.append(split_command[4])
            result_command.append(split_command[6])
        elif len(split_command) == 9 and re.match(r'(?i)(on)', split_command[5]):
            result_command.append("JOIN")
            result_command.append(split_command[4])
            result_command.append("ON")
            result_command.append(split_command[6])
            result_command.append(split_command[8])
        elif len(split_command) == 9 and re.match(r'(?i)(where)', split_command[5]):
            result_command.append("JOIN")
            result_command.append(split_command[4])
            result_command.append("WHERE")
            result_command.append(split_command[6])
            result_command.append(split_command[8])
        elif len(split_command) == 13:
            result_command.append("JOIN")
            result_command.append(split_command[4])
            result_command.append("ON")
            result_command.append(split_command[6])
            result_command.append(split_command[8])
            result_command.append("WHERE")
            result_command.append(split_command[10])
            result_command.append(split_command[12])
        return result_command
    else:
        return "Incorrect command syntax"
