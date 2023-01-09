from pyparsing import *



def parse(a: str) -> list:
    table_name = (Word(alphas + '_'))('Name_Of_Table')
    column_name = Word(alphas + '_')
    columns = (column_name + ZeroOrMore(Suppress(', ') + column_name))('columns')
    word = (Suppress('\"') + Word(alphas + '_' + ' ' + nums) + Suppress('\"'))
    data = (word + ZeroOrMore(Suppress(', ') + word))
    condition = (column_name + Suppress('<') + word)('cond')
    stop_command = ('exit' + Suppress(';'))('command')
    create_command = ("CREATE" + table_name + Suppress('(') + columns + Suppress(');'))
    insert_command = ("INSERT INTO" + table_name + Suppress('(') + data + Suppress(');'))
    select_all = ("SELECT * FROM" + table_name + Suppress(';'))
    select_with_where = ("SELECT FROM" + table_name + Suppress('WHERE') + condition + Suppress(';'))
    select_command = Or([select_all, select_with_where])
    parse_module = Or([create_command, insert_command, select_command, stop_command])
    res = parse_module.parseString(a)
    return res
