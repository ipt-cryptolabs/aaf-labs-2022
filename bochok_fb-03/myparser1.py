import re


def make_normal(line):
    line_wo_spaces = line
    start = 0
    is_found = False

    while True:
        line_wo_spaces = re.sub("^\s+", "", line_wo_spaces)
        line_wo_spaces = re.sub("\s+", " ", line_wo_spaces)
        line_wo_spaces = re.sub("\s*\(", " (", line_wo_spaces)
        line_wo_spaces = re.sub("\(\s+", "(", line_wo_spaces)
        line_wo_spaces = re.sub("\s*,\s*", ", ", line_wo_spaces)
        line_wo_spaces = re.sub("\s+\)", ")", line_wo_spaces)
        line_wo_spaces = re.sub(",\s*\)", ", )", line_wo_spaces)

        for i in range(start, len(line_wo_spaces)):

            if line_wo_spaces[i] == ";":

                is_found = True
                if line_wo_spaces[i - 1] == " ":
                    i -= 1
                line_wo_spaces = line_wo_spaces[0:i] + ";"
                break

        if is_found is True:
            break

        start = len(line_wo_spaces)
        line_wo_spaces += " " + input("...> ")

    return line_wo_spaces


def parse(line):

    if line == ";":
        return "Error: no command input."

    elif line[:6].lower() == "insert" or line[:11].lower() == "insert into":

        line = line.replace(";", "")
        for j in range(0, len(line)):
            if line[j] == "(":

                if line[-1] == ")":
                    command = line[0:j - 1].split(" ")

                    if len(command) != 2 and command[1].lower() != "into" or \
                        len(command) != 3 and command[1].lower() == "into" or \
                            len(command) == 1:
                        return "Error: command includes no or too many arguments in name section."

                    if command[1].lower() == "into":
                        command = [command[0] + command[1]] + command[2:]

                    if not re.match("[a-zA-Z]", command[1][0]):
                        return "Error: table names have to start with letter."
                    args = line[j + 1:-1]
                    if args[0] != "\"" or args[-1] != "\"":
                        return "Error: invalid syntax in argument section."

                    args_l = args.split("\", \"")

                    if len(args_l) == 1 and len(re.findall("\"", args_l[0])) == 2:
                        args_l[0] = args_l[0][1:-1]
                    elif len(args_l) > 1:
                        for k in range(0, len(args_l)):
                            if args_l[k] == "":
                                return "Error: invalid syntax in argument section."
                            elif k in range(1, len(args_l)-1) and len(re.findall("\"", args_l[k])) != 0:
                                return "Error: invalid syntax in argument section."
                            elif (k == 0 or k == len(args_l) - 1) and len(re.findall("\"", args_l[k])) == 1:
                                if k == 0:
                                    args_l[k] = args_l[k][1:]
                                else:
                                    args_l[k] = args_l[k][:-1]
                            elif (k == 0 or k == len(args_l) - 1) and len(re.findall("\"", args_l[k])) > 1:
                                return "Error: invalid syntax in argument section."
                            else:
                                continue
                    else:
                        return "Error: invalid syntax in argument section."

                    return command + args_l

                else:
                    return "Error: ) is missed or placed wrongly."
        return "Error: ( is missed or placed wrongly."

    elif line[:6].lower() == "create":

        line = line.replace(";", "")
        for j in range(0, len(line)):
            if line[j] == "(":

                if line[-1] == ")":
                    if len(line[0:j-1].split(" ")) != 2:
                        return "Error: command includes no or too many arguments in name section."
                    command = line[0:j-1].split(" ")

                    if not re.match("[a-zA-Z]", command[1][0]):
                        return "Error: table names have to start with letter."
                    args = line[j+1:-1].split(", ")
                    # args_d = dict()
                    for k in range(0, len(args)):

                        if args[k] == "":
                            return "Error: invalid syntax in argument section."
                        elif not re.match("[a-zA-Z]", args[k][0]):
                            return "Error: column names have to start with letter."
                        # elif args[k] in args_d.keys():
                        #     return "Error: columns of the table are not unique."
                        # elif re.match("[a-zA-Z][a-zA-Z0-9_]* [Ii][Nn][Dd][Ee][Xx][Ee][Dd]", args[k]):
                        #     col = re.sub(" [Ii][Nn][Dd][Ee][Xx][Ee][Dd]", "", args[k])
                        #     args_d[col] = 1
                        elif re.match("[a-zA-Z][a-zA-Z0-9_]*", args[k]) and len(re.findall(" ", args[k])) == 0:
                            continue
                        else:
                            return "Error: Invalid column name format."
                    return command + args

                else:
                    return "Error: ) is missed."
        return "Error: ( is missed."

    elif line[:11].lower() == "select from":

        line = line.replace(";", "")
        pattern = r'^[Ss][Ee][Ll][Ee][Cc][Tt]\s[Ff][Rr][Oo][Mm]\s[\w_]+'

        if re.match(pattern+"$", line):
            command = line.split(" ")
            return [command[0] + command[1]] + [command[2]]
        elif re.match(pattern+".+", line):
            test_join = r'\s[Ll][Ee][Ff][Tt]_[Jj][Oo][Ii][Nn]\s[\w_]+\s[Oo][Nn]\s[\w_]+\s\=\s[\w_]+'
            test_where = r'\s[Ww][Hh][Ee][Rr][Ee]\s[\w_]+\s<\s(([\w_]+)|([\"]\w+[\"]))'
            # print(re.match(test_join, line))
            if not re.match(pattern+test_join+test_where+"$", line):

                if re.match(pattern+test_join+"$", line):
                    command = line.split(" ")
                    return [command[0] + command[1]] + command[2:]
                else:
                    command = "Error: syntax error in LEFT_JOIN section."

                if re.match(pattern+test_where+"$", line):
                    command = line.split(" ")
                    return [command[0] + command[1]] + command[2:]
                else:
                    command = "Error: syntax error in WHERE section."

                return "Syntax error!"
            else:
                command = line.split(" ")
                command = [command[0] + command[1]] + command[2:]
                return command

        else:
            return "Error: table name is not given correctly."
    else:
        return "Error: unknown command."
