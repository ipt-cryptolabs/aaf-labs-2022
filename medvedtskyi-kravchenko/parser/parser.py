from pyparsing import *

a = 'CREATE students (name, group, ggg, bbb, sss, aaa);'
# a = 'SELECT FROM kost WHERE name = kosssst;'
# a = 'INSERT INTO kot (huh, wtfimdoing, irgr);'

table_name = (Word(alphas + '_'))('Name_Of_Table')
column = Word(alphas + '_')
column_names = (column + ZeroOrMore(Suppress(', ') + column))('modules')
command_name = one_of(["CREATE", "INSERT INTO", "SELECT FROM"])('command')
condition = (Word(alphas + '_') + Suppress('=') + Word(alphas + '_'))('cond')
where_statement = (Suppress('WHERE') + condition + Suppress(';'))('wherest')
create_and_insert_statement = (Suppress('(') + column_names + Suppress(');'))('crst')
last = Or([where_statement, create_and_insert_statement])('laast')
parse_module = command_name + table_name + last

#print(parse_module.parseString(a))
res = parse_module.parseString(a)
print(res.command)
print(res.Name_Of_Table)
print(res.laast)