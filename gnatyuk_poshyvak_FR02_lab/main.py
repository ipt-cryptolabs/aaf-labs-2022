from typing import List, Any
from Queries import *
import custom_parser
from db_engine import *


def main():
    print('''
    You can start with these commands: 
    \n # CREATE table_name (column_name *[INDEXED] [, ...]); 
    \n # INSERT INTO table_name (Column1, Column2, ...) VALUES (value1, Value2, ...); 
    \n # SELECT ... FROM ...
    
    \n # PRINT
    \n # SAVE   
     ''')
    try:
        run_DB()
        db_name = 'main_db'
        while True:
            lines = []
            while True:
                line = input('> ' if len(lines) == 0 else '... ')
                if line:
                    lines.append(line)
                    if ';' in line:
                        break
            db = get_DB(db_name)

            query = ''.join(lines)
            query = query.replace('\n', ' ')
            commands = query.split(';')
            commands.pop()
            commands = [x + ';' for x in commands]
            queries = custom_parser.parse(commands)

            for query in queries:
                if query == 'save':
                    db.save()
                if query == 'print':
                    db.print()

                if type(query) == QCreate:
                    new_table = Table(query.table_title, query.columns)
                    db.create_table(new_table)

                if type(query) == QInsert:
                    insert_values = query.values
                    insert_columns = query.columns

                    table = db.get_table(query.table_title)
                    table.insert_row(insert_columns, insert_values)

                if type(query) == QSelect:
                    columns = query.columns
                    table = db.get_table(query.table_title)
                    values = table.get_values(query.columns)
                    print(values)
    except:
        print('')


def test():
    c1 = Column('asad')
    c2 = [Column('asd'), Column('fasg')]
    print(c1 in c2)


# test()
main()
