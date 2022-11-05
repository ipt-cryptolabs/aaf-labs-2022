from matplotlib.pyplot import table
from pyparsing import *

a = 'CREATE students (name, group, ggg, bbb, sss, aaa);'

table_name = (Word(alphas + '_'))('Name_Of_Table')
column = Word(alphas + '_')
column_names = (column + ZeroOrMore(Suppress(', ') + column))('modules')
parse_module = 'CREATE' + table_name + Suppress('(') + column_names + Suppress(');')

#print(parse_module.parseString(a))
res = parse_module.parseString(a)
mass = res.modules.asList()
Name_Of_Table = res.Name_Of_Table
print(res.modules.asList())
print(res.Name_Of_Table)
