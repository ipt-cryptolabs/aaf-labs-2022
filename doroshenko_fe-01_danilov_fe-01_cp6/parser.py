class Parser:
    __pos = 0

    def __init__(self, DB):
        self.__tokens = []
        self.DB = DB

    def setTokens(self, tokens):
        self.__tokens = tokens

    def getTokens(self):
        return self.__tokens

    def CreateTable(self, tokenLen):

        if self.__tokens[1].type != "STR":
            raise Exception("Incorrect table name")

        if self.__tokens[2].type != "LPAREN":
            raise Exception(" ( expected ")

        if self.__tokens[3].type != "STR":
            raise Exception("Incorrect field name")

        if self.__tokens[-2].type != "RPAREN":
            raise Exception(" ) expected ")

        if self.__tokens[-1].type != 'SEMICOLON':
            raise Exception(' ; expected ')

        colums = list()

        indexedFields = list()

        colums.append(self.__tokens[3].value)

        oldTokenType = "STR"
        if tokenLen > 5:
            for i in range(4, tokenLen):
                newTokenType = self.__tokens[i].type

                if newTokenType != "INDEXED" and newTokenType != "COMMA" \
                        and newTokenType != "RPAREN" and newTokenType != "SEMICOLON" and oldTokenType == "STR":
                    raise Exception('Unexpected token on position ', i)
                if newTokenType != "STR" and oldTokenType == "COMMA":
                    raise Exception("Unexpected token on position ", i)
                if newTokenType != "COMMA" and oldTokenType == "INDEXED":
                    raise Exception("Unexpected token on position ", i)
                if newTokenType == 'RPAREN' and (oldTokenType != "STR" and oldTokenType != "INDEXED"):
                    raise Exception('Unexpected ) on position ', i)
                if newTokenType == "INDEXED":
                    indexedFields.append(self.__tokens[i - 1].value)
                    oldTokenType = "INDEXED"
                if newTokenType == "STR":
                    colums.append(self.__tokens[i].value)
                    oldTokenType = "STR"
                if newTokenType == "COMMA":
                    oldTokenType = "COMMA"

        print(self.__tokens[1].value, colums, indexedFields)
        self.DB.CreateTable(self.__tokens[1].value, colums, indexedFields)

    def Insert(self, tokenLen):
        STRsToInsert = list()
        if self.__tokens[1].type != "INTO":
            raise Exception("Unknown table name")
        if self.__tokens[3].type != "LPAREN":
            raise Exception("( Expected")
        if self.__tokens[-2].type != 'RPAREN':
            raise Exception(") Expected")

        for i in range(4, tokenLen):
            if self.__tokens[i].type == "STR":
                STRsToInsert.append(str(self.__tokens[i].value))
            elif self.__tokens[i].type == "RPAREN":
                break
            elif self.__tokens[i].type == "COMMA" or self.__tokens[i].type == "QUOTE":
                continue
            else:
                raise Exception(") Expected")

        print(self.__tokens[2].value, STRsToInsert)

        self.DB.Insert(self.__tokens[2].value, STRsToInsert)

  
    def Select(self):
        column_where = None
        column_equals = None

        if self.__tokens[1].type != "FROM":
            raise Exception("Unknown token on position 2")
        if self.__tokens[2].type == "STR":
            table_name = self.__tokens[2].value
            if self.__tokens[3].type == "SEMICOLON":
                self.DB.Select(table_name, None, None)
                print(table_name, column_where, column_equals)

            elif self.__tokens[3].type == 'WHERE' \
                    and self.__tokens[4].type == 'STR' and \
                    self.__tokens[5].type == 'EQUALS' and \
                    self.__tokens[6].type == 'QUOTE' and \
                    self.__tokens[7].type == 'STR' and \
                    self.__tokens[8].type == 'QUOTE':
                column_where = self.__tokens[4].value
                column_equals = self.__tokens[7].value
                print(table_name, column_where, str(column_equals))
                self.DB.Select(table_name, column_where, column_equals)
                

            elif self.__tokens[3].type == "FULL_JOIN" \
                    and self.__tokens[4].type == "STR" and \
                    self.__tokens[5].type == "ON" and \
                    self.__tokens[6].type == "STR" and \
                    self.__tokens[7].type == "EQUALS" and \
                    self.__tokens[8].type == "STR":
                print(table_name, self.__tokens[4].value, self.__tokens[6].value,  self.__tokens[8].value)
                #self.DB.SelectJoin(table_name1, table_name2, column_1, column_2)
                pass
            else:
                raise Exception("Invalid syntax")


    def parse(self):
        tokenLen = len(self.__tokens)
        if tokenLen == 0:
            raise Exception("Empty token array!")

        if self.__tokens[0].type != "CREATE" and self.__tokens[0].type != "SELECT" \
                and self.__tokens[0].type != "DELETE" and self.__tokens[0].type != "INSERT":
            raise Exception("Unknown comand!")

        if self.__tokens[0].type == "CREATE":
            self.CreateTable(tokenLen)

        if self.__tokens[0].type == "INSERT":
            self.Insert(tokenLen)

        if self.__tokens[0].type == "SELECT":
            self.Select()
