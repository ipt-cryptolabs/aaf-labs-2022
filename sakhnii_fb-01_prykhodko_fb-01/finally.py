import re
import os
from prettytable import PrettyTable

pattern_create = re.compile("^[Cc][Rr][Ee][Aa][Tt][Ee]\s+[a-zA-Z][a-zA-Z0-9_]*\s+\(\s*[a-zA-Z][a-zA-Z0-9_]*(\s+[Ii][Nn][Dd][Ee][Xx][Ee][Dd])?(\s*,\s*[a-zA-Z][a-zA-Z0-9_]*(\s+[Ii][Nn][Dd][Ee][Xx][Ee][Dd])?)*\s*\)\s*;\s*$")
pattern_insert = re.compile("^[Ii][Nn][Ss][Ee][Rr][Tt](\s+[Ii][Nn][Tt][Oo])?\s+[a-zA-Z][a-zA-Z0-9_]*\s+\(\s*\".+\"(\s*,\s*\".+\")*\s*\)\s*;\s*$")
pattern_select = re.compile("^[Ss][Ee][Ll][Ee][Cc][Tt]\s+[Ff][Rr][Oo][Mm]\s+[a-zA-Z][a-zA-Z0-9_]*(\s+[Ww][Hh][Ee][Rr][Ee]\s+[a-zA-Z][a-zA-Z0-9_]*\s+[><=]\s+(([a-zA-Z][a-zA-Z0-9_]*)|(\".+\")))?(\s+[Oo][Rr][Dd][Ee][Rr]_[Bb][Yy]\s+[a-zA-Z][a-zA-Z0-9_]*(\s+(([Aa][Ss][Cc])|([Dd][Ee][Ss][Cc])))?(\s*,\s*[a-zA-Z][a-zA-Z0-9_]*(\s+(([Aa][Ss][Cc])|([Dd][Ee][Ss][Cc])))?)*)?\s*;\s*$")
pattern_exit = re.compile("^[Ee][Xx][Ii][Tt]\s*;\s*$")
pattern_clear = re.compile("^[Cc][Ll][Ee][Aa][Rr]\s*;\s*$")
patterns = [pattern_create, pattern_insert, pattern_select, pattern_exit, pattern_clear]
print("Welcome to our program, which was created by students of group FB-01: Prykhodko Ihor and Sakhnii Nazar \n\n"
      "To test the command line interface, please ENTER basic database query commands (To finish type \"EXIT\")")
tables = {}
table_indexes = {}
while True:
    command = ""
    i = 0
    while True:
        if i==0:
            line = input(">>> ")
        else:
            line = input("... ")
        i+=1
        command += (line + "\n")
        if ";" in line:
            break
    result = -1
    for i in range(len(patterns)):
        if patterns[i].match(command):
            result = i
            break
    if result == -1:
        if bool(re.match("^[Cc][Rr][Ee][Aa][Tt][Ee]", command)):
            print("Incorrect \"CREATE\" syntax.\n"
                  "Try to make query in next format → CREATE {table_name} ({column_name_№1} [,..., {column_name_№n}]);")
        elif bool(re.match("^[Ii][Nn][Ss][Ee][Rr][Tt]", command)):
            print("Incorrect \"INSERT\" syntax. \n"
                  "Try to make query in next format → INSERT [INTO] {table_name} ({value_№1} [,..., {value_№n}]);")
        elif bool(re.match("^[Ss][Ee][Ll][Ee][Cc][Tt]", command)):
            print("Incorrect \"SELECT\" syntax. \n"
                  "Try to make query in next format → SELECT FROM {table_name};")
        elif bool(re.match("^[Ee][Xx][Ii][Tt]", command)):
            print("Incorrect \"EXIT\" syntax. \n"
                  "Format of \"EXIT\" command: EXIT;")
        elif bool(re.match("^[Cc][Ll][Ee][Aa][Rr]", command)):
            print("Incorrect \"CLEAR\" syntax. \n"
                  "Format of \"CLEAR\" command: CLEAR;")
        else:
            print("Unknown command :-(")
    else:
        if result == 0:
            tokens_create = re.findall("[a-zA-Z][a-zA-Z0-9_]*", command)  
            print("Tokens of \"CREATE\" command:")
            print(tokens_create)
            if tokens_create[1] in tables:
                print("Error. Table with this name is already exist.")
                continue
            else:
                column_names = []
                indexes = {}
                error_check = 0
                for i in range(2,len(tokens_create)):
                    if bool(re.match("[Ii][Nn][Dd][Ee][Xx][Ee][Dd]", tokens_create[i])):
                        indexes[tokens_create[i-1]] = []
                    else:
                        if tokens_create[i] in column_names:
                            print("Error. Can not create table with 2 similar names of columns.")
                            error_check = 1
                            break
                        column_names.append(tokens_create[i])    
                if error_check:
                    continue
                tables[tokens_create[1]] = [tuple(column_names)]
                table_indexes[tokens_create[1]] = indexes
                print(tables)
                print(table_indexes)
        elif result == 1:
            tokens_insert_values = re.findall("\".+?\"",command)
            tokens_insert_name = re.findall("[a-zA-Z][a-zA-Z0-9_]*(?=(?:[^\"]*\"[^\"]*\")*[^\"]*\Z)",command)
            print("Tokens of \"INSERT\" command:")
            print(tokens_insert_values)
            print(tokens_insert_name)
            table_name = tokens_insert_name[-1]
            if table_name not in tables:
                print("Error. No such table")
                continue
            table = tables[table_name]
            if len(tokens_insert_values) != len(table[0]):
                print("Error. Number of tokens not matching the number of columns")
                continue
            if table_name in table_indexes:
                column_names = table[0]
                indexes = table_indexes[table_name]
                for i in range(len(column_names)):
                    if column_names[i] in indexes:
                        indexes[column_names[i]].append((len(table)-1,tokens_insert_values[i]))
                        indexes[column_names[i]].sort(key = lambda x: x[1])
            table.append((len(table) - 1,tokens_insert_values))
            print(tables)
            print(table_indexes)
        elif result == 2:
            tokens_select = re.findall("[a-zA-Z][a-zA-Z0-9_]*(?=(?:[^\"]*\"[^\"]*\")*[^\"]*\Z)", command)
            print("Tokens of \"SELECT\" command:")
            print(tokens_select)
            table_name = tokens_select[2]
            table = tables[table_name]
            output_table = PrettyTable()
            output_table.field_names = table[0]
            if len(tokens_select) == 3:
                output_table.add_rows([item[1] for item in table[1:]]) 
            else:
                rows = []
                order_by_index = 3
                if re.search("[Ww][Hh][Ee][Rr][Ee]", command) != None:
                    order_by_index = 5
                    def check_condition(condition: str,parametr_1: str,parametr_2: str) -> bool:
                        if condition == ">":
                            if parametr_1 > parametr_2:
                                return True
                        elif condition == "<":
                            if parametr_1 < parametr_2:
                                return True
                        else:
                            if parametr_1 == parametr_2:
                                return True
                        return False
                    parametr_1 = tokens_select[4]
                    if parametr_1 not in table[0]:
                        print("Error: Command_Where parametr_1 - no such column",parametr_1)
                        continue
                    index_1 = table[0].index(parametr_1)
                    condition = re.search("[<>=]",command).group()
                    parametr_2 = re.findall("\".+?\"",command)
                    if not parametr_2:
                        order_by_index = 6
                        parametr_2 = tokens_select[5]
                        if parametr_2 not in table[0]:
                            print("Error: Command_Where parametr_2 - no such column",parametr_2)
                            continue
                        index_2 = table[0].index(parametr_2)
                        for row in table[1:]:
                            if check_condition(condition,row[1][index_1],row[1][index_2]):
                                rows.append(row)
                    else:
                        parametr_2 = parametr_2[0]
                        for row in table[1:]:
                            if check_condition(condition,row[1][index_1],parametr_2):
                                rows.append(row)
                if re.search("[Oo][Rr][Dd][Ee][Rr]_[Bb][Yy]", command) != None:
                    if order_by_index == 3:
                        rows = table[1:]
                    rev = False
                    error_check = 0
                    for param in tokens_select[:order_by_index:-1]:
                        if bool(re.match("[Aa][Ss][Cc]",param)) or bool(re.match("[Dd][Ee][Ss][Cc]",param)):
                            if bool(re.match("[Dd][Ee][Ss][Cc]",param)):
                                rev = True
                            continue
                        if param not in table[0]:
                            print("Error: Order_by_command parametr - no such column",param)
                            error_check = 1
                            break
                        if param in table_indexes[table_name]:
                            temp_rows = []
                            ids = []
                            indexes = table_indexes[table_name][param]
                            for i in indexes[:: -1 if rev else 1]:
                                for row in rows:
                                    if row[0] == i[0]:
                                        temp_rows.append(row)
                                        break
                            rows = temp_rows
                        else:
                            j = table[0].index(param)
                            rows.sort(key = lambda x: x[1][j], reverse = rev)
                        rev = False
                    if error_check:
                        continue  
                for row in rows:
                    output_table.add_row(row[1])
            print(output_table)
        elif result == 3:
            break
        elif result == 4:
            os.system('cmd /c "cls"')
#create test (a,b indexed,c);
#insert test ("a","b","c");
#insert test ("2","1","3");
#insert test ("r","t","f");
#insert test ("ab","bc","cd");
#select from test where b > "b";
#select from test order_by a;
#insert test ("a","b","c");
#insert test ("a","1","6");
#insert test ("k","t","y");
#insert test ("k","g","o");
#select from test order_by a,b;


