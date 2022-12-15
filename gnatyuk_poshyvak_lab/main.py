from typing import List, Any

import custom_parser
import db_engine as db


def main():
    print('''
    You can start with these commands: 
    \n # CREATE table_name (column_name *[INDEXED] [, ...]); 
    \n # INSERT INTO table_name (Column1, Column2, ...) VALUES ("value1", "Value2", ...); 
    \n # SELECT ... FROM ...
     \n # exit 
     ''')

    db.run_DB()
    while True:
        lines = []
        while True:
            line = input('> ' if len(lines) == 0 else '... ')
            if line:
                lines.append(line)
                if ';' in line:
                    break
        if ''.join(lines).replace(' ', '').replace('\t', '') == 'exit':
            break

        query = ''.join(lines)
        query = query.replace('\n', ' ')
        commands = query.split(';')
        commands.pop()
        commands = [x + ';' for x in commands]
        commands = custom_parser.parse(commands)
        print(commands)


main()
