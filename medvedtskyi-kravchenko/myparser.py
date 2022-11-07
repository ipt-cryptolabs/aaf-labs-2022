from pyparsing import *

def parse(a: str) -> tuple[str, str, list]:
    table_name = (Word(alphas + '_'))('Name_Of_Table')
    column = Word(alphas + '_')
    column_names = (column + ZeroOrMore(Suppress(', ') + column))('modules')
    command_name = one_of(["CREATE", "INSERT INTO", "SELECT FROM"])('command')
    condition = (Word(alphas + '_') + Suppress('<') + Word(alphas + '_'))('cond')
    where_statement = (Suppress('WHERE') + condition + Suppress(';'))('wherest')
    create_and_insert_statement = (Suppress('(') + column_names + Suppress(');'))('crst')
    last = Or([where_statement, create_and_insert_statement])('laast')
    stop_command = ('exit' + Suppress(';'))('command')
    parse_module = Or([command_name + table_name + last, stop_command])
    res = parse_module.parseString(a)
    return res.command.__str__(), res.Name_Of_Table.__str__(), res.laast
