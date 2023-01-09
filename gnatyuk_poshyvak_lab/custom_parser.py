import regex as re
import Checker


def query_formatting(query: str):
    end = query.find(";")
    formatted_query = query[:end]
    if formatted_query[0] == ' ' or formatted_query[0] == '\t':
        formatted_query = query[1:]
    for i in range(len(formatted_query) - 1):
        if formatted_query[i] == ' ' and formatted_query[i + 1] == ' ':
            formatted_query[i] = ''

    return formatted_query


def is_correct(commands):
    i = 0
    for command in commands:
        if not Checker.is_syntax_correct(command):
            print("Wrong syntax", command)
            return 0
        if not Checker.is_query_correct(command):
            return 0
        i += 1
    return 1


def parse(commands):
    formatted_commands = [query_formatting(command) for command in commands]
    if not is_correct(formatted_commands):
        return 0
    for command in commands:
        command = str(command).split(' \t')
    return commands

