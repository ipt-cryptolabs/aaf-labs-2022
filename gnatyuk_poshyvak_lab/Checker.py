import regex as re

re_create = '(CREATE|create)[ ]+[a-zA-Z1-9_]+[ ]*[(]{1}([ ]*[a-zA-Z1-9]*[ ]*[\[(INDEXED|indexed)\]]?[,]?)+[)]{1}'
re_insert = '(INSERT)[\s]+(INTO|into)[\s]+[\w]+[ ]+\([(\w+), ]+\)[\s]+(VALUES)[\s]+\([(\'\w+\W*\')|("\w+\W*"), ]+\);'
re_select = '(select)\s+((COUNT\(|SUM\(|MAX\(|MIN\(){1}\s*[\w]+(?<=\([\w]+)\)(\,\s*|\s+)+|\w+(\,\s*|\s+)+)+from\s+\w+(\s+group_by\s+[a-zA-Z1-9_, ]+)?((\s+where\s+[a-zA-Z1-9><=\-\'\"]+)(\s+group_by[a-zA-Z1-9_, ]+)?)?'
RE_LIST = [re_create, re_insert, re_select]
RESTRICTED_PREFIXES_DB = '-123456789@#$'
RESTRICTED_SYMBOLS_PARSER = ".,;':/\*|?&%$!+=()[]{}<>"


def clear_text(text: str, symbols: str):
    for item in symbols:
        text = text.replace(item, '')
    return text


def is_correct_column(column: str):
    if str(column)[0] in RESTRICTED_PREFIXES_DB:
        return False
    else:
        return True


def is_correct_row(row: list, table_rows: list, table_columns: list):
    if len(row) != len(table_columns):
        print("[!] Error. Row values count doesn't match column ones.")
        return False
    if not table_columns:
        print("[!] Error. There are no columns in table to insert row.")
    for index in range(0, len(table_columns) - 1):
        if table_columns[index].indexed and row[index] in table_rows[:][index]:
            print(f"[!] {row[index]} value already exists in table.")
            return False
    return True


def is_correct_title(title: str):
    if title in RESTRICTED_PREFIXES_DB:
        return False
    else:
        return True


def is_syntax_correct(query):
    if len(query) == 0:
        return False
    elif [re.match(exp_item, query, flags=re.IGNORECASE) for exp_item in RE_LIST]:
        return True
    else:
        return False


def is_query_correct(query: str):
    if query.lower().startswith('insert'):
        # searches all matches like "(val1, val2, ...)"
        pattern = re.compile('\([^\(\)]*\)')
        data = pattern.findall(query)
        columns = clear_text(data[0], '()').split(',')
        values = clear_text(data[1], '()"\'').split(',')
        if len(columns) != len(values):
            print("[!] Error. Number of arguments does not match columns number")
            return False

    elif query.lower().startswith('create'):
        pattern_columns = re.compile('\([^\(\)]*\)')
        pattern_table = re.compile('(?<=TABLE)\s+\w+\s*(?=\()', re.IGNORECASE)
        table_data = pattern_table.findall(query)[0]
        columns_data = pattern_columns.findall(query)
        if RESTRICTED_SYMBOLS_PARSER in table_data:
            print(f"[!] Error. Table '{table_data}' contains restricted symbols.")
            return False
        for column in columns_data:
            if RESTRICTED_SYMBOLS_PARSER in column:
                print(f"[!] Error. Column '{column}' contains restricted symbols.")
                return False

    elif query.lower().startswith('select'):
        columns_start = query.lower().find("select") + 6
        columns_end = query.lower().find('from')
        columns = query[columns_start:columns_end]
        columns = columns.lstrip().rstrip()
        if ' ' in columns:
            print('[!] Error. Column name may not have \' \' symbol.')
            return False
        table_title_start = query.lower().find('from') + 4
        table_title = query.lower()[table_title_start:].lstrip().rstrip()
        if ' ' in table_title:
            print('[!] Error. Table title may not have \' \' symbol.')
            return False

    return True
