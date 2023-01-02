import Checker
from Checker import *
from Queries import *
from db_engine import *


def query_formatting(query: str):
    end = query.find(";")
    formatted_query = query[:end]
    if formatted_query[0] == ' ' or formatted_query[0] == '\t':
        formatted_query = query[1:]
    for i in range(len(formatted_query) - 1):
        if formatted_query[i] == ' ' and formatted_query[i + 1] == ' ':
            formatted_query[i] = ''

    return formatted_query


# if not qsl returns the same
def decompose_query(str_query: str):
    if str_query.lower().startswith('insert'):
        # searches all matches like "(val1, val2, ...)"
        pattern = re.compile('\([\w, ]+\)')
        pattern_table = re.compile('(?<=INTO)\s+\w+\s*(?=\()', re.IGNORECASE)

        data = pattern.findall(str_query)
        columns_str = clear_text(data[0], '()').split(',')
        values = clear_text(data[1], '()"\'').split(',')

        table_title = clear_text(pattern_table.findall(str_query)[0], ' ')
        return QInsert(table_title, columns_str, values)

    elif str_query.lower().startswith('create'):
        pattern_columns = re.compile('\([\w, \[\]]+\)')
        pattern_table = re.compile('(?<=CREATE)\s+\w+\s*(?=\()', re.IGNORECASE)

        a = pattern_table.findall(str_query)
        table_title = clear_text(a[0], ' ')

        columns_titles = pattern_columns.findall(str_query)
        columns_titles = ''.join([clear_text(x, '() ') for x in columns_titles])
        columns_titles = columns_titles.split(',')
        indexed_columns = []
        for column in columns_titles:
            if 'indexed' in column.lower():
                indexed_columns.append(column)

        formatted_columns_titles = []

        for column in columns_titles:
            if '[' in column:
                formatted_columns_titles.append(column[:column.index('[')])
            else:
                formatted_columns_titles.append(column)

        formatted_indexed_titles = []
        for indexed_column in indexed_columns:
            formatted_indexed_titles.append(indexed_column[:indexed_column.index('[')])
        if not Checker.is_correct_indexed(formatted_columns_titles, formatted_indexed_titles):
            return 0

        column_list = []
        for column_title in formatted_columns_titles:
            tmp_column = Column(column_title)
            if column_title in formatted_indexed_titles:
                tmp_column.indexed = True
            column_list.append(tmp_column)

        return QCreate(table_title, column_list)

    elif str_query.lower().startswith('select'):
        columns_start = str_query.lower().find("select") + 6
        columns_end = str_query.lower().find('from')
        columns_str = str_query[columns_start:columns_end].lstrip().rstrip()
        columns = []
        #TODO
        for column in columns_str:
            columns.append(Column())

        table_title_start = str_query.lower().find('from') + 4
        table_title_end = len(str_query) - 1
        table = clear_text(str_query[table_title_start: table_title_end], ' (),')

        return QSelect(table, columns_str)

    elif str_query.lower() == 'save' or str_query.lower() == 'print':
        return str_query.lower()
    else:
        return None


def is_correct(commands):
    i = 0
    for command in commands:
        if not is_syntax_correct(command):
            print("Wrong syntax", command)
            return 0
        if not is_query_correct(command):
            return 0
        i += 1
    return 1


def parse(commands):
    formatted_commands = list()
    for command in commands:
        formatted_commands.append(query_formatting(command))

    if not is_correct(formatted_commands):
        return 0

    queries = []
    for command in formatted_commands:
        queries.append(decompose_query(command))

    return queries
