import re


def parse(line):
<<<<<<< HEAD
    result_command = []
    line = line.lstrip() # remove spaces on the left
    command = re.sub(r'\s+', ' ', line) # replace tabulate symbols on the space
    command = re.sub(r'\(\s*', '(', command) # replace tabulate symbols after ( on '('
    command = re.sub(r'\s*,\s*', ',', command) # replace tabulate symbols before and after coma on ','
    command = re.sub(r'\s*\)', ',)', command) # replace tabulate symbols before ) on ')'
    split_command = command.split(' ')
    if re.match(r'(?i)create\s+[a-zA-Z][a-zA-Z0-9_]*\s+\(.+\)\s*\;', line):
        parenthesized_expression = re.findall(r'\(.*\)', command)
        parameters = parenthesized_expression[0][1:-1]
        find_parameters = re.findall(r'[a-zA-Z][a-zA-Z0-9_]*,', parameters)
        concat_parameters = ''
        for i in find_parameters:
            concat_parameters += i
        if concat_parameters == parameters:
            result_command.append("CREATE")
            del split_command[0]
=======
    line = line.lstrip()
    line = line.replace(line[-1], '')
    command = re.sub(r'\s+', ' ', line)
    command = re.sub(r'\(\s*', '(', command) # + or * ?
    command = re.sub(r'\s*,\s*', ',', command)
    command = re.sub(r'\s*\)', ')', command)
    split_command = command.split(' ')
    result_command = []
    if re.match(r'(?i)create', split_command[0]):
        result_command.append("CREATE")
        del split_command[0]
        if re.match(r'[a-zA-Z][a-zA-Z0-9_]*', split_command[0]):
>>>>>>> 9ff7440d55277bd403288098beea1e0039d6a8f0
            result_command.append(split_command[0])
            del split_command[0]
            split_command[0] = split_command[0].replace(split_command[0][0], '')
            split_command[0] = split_command[0].replace(split_command[0][-1], '')
<<<<<<< HEAD
            split_command[0] = split_command[0].replace(split_command[0][-1], '')
            result_command.append(split_command[0].split(','))
            print(result_command)
            return result_command
        else:
            return "Wrong syntax"
    elif re.match(r'(?i)(insert|insert\s+into)\s+[a-zA-Z][a-zA-Z0-9_]*\s+\(.+\)\s*\;', line):
        line = re.sub(r'\s*\)', ',)', line)
        parenthesized_expression = re.findall(r'\(.*\)', line)
        #parenthesized_expression = re.sub(r'(?i)(insert|insert\s+into)\s+[a-zA-Z][a-zA-Z0-9_]*\s+\(.+\)\s*\;', line)
        parameters = parenthesized_expression[0][1:-1]
        #parameters = parameters + ','
        if re.match(r'(?:\s*["]\s*\w+\s*["]\s*[,]\s*)+', parameters):
           print(parenthesized_expression[0])
        """args = re.findall(r'\".*?\"', line)  # extract arguments from line in "..."
        print(args)
        if len(args) != 0:
            for i in range(len(args)):
                args[i] = re.sub(r'\"', '', args[i])
                result_command.append(args)
        else:
            print('Wrong syntax')
            return"""
            # INSERT cats ("10", "1", "Murzik");
            # INSERT cats ("  10 ", "   1 ", "   Murzik  "  );

    """if len(args)!=0:
        #fllflfd
        else:
            print('Wrong syntax')"""
=======
            result_command.append(split_command[0].split(','))
            return result_command
>>>>>>> 9ff7440d55277bd403288098beea1e0039d6a8f0
