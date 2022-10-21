class Parser:
    __pos = 0

    def __init__(self, DB):
        self.__tokens = []
        self.DB = DB

    def setTokens(self, tokens):
        self.__tokens = tokens

    def Insert(self, tokenLen):
        varsToInsert = list()
        if (self.__tokens[1].type != "VAR"):                     #
            raise Exception("Unknown table name")
        if (self.__tokens[2].type != "("):
            raise Exception("( Expected")
        if (self.__tokens[tokenLen - 1].type != ")"):
            raise Exception(") Expected")

        for i in range(3, tokenLen):
            if (self.__tokens[i].type == ")"):
                break
            if (i % 2 == 1):
                if (self.__tokens[i].type != "NUMBER"):
                    raise Exception("Unknown token on position ", i)
                varsToInsert.append(int(self.__tokens[i].text))
            if (i % 2 == 0):
                if (self.__tokens[i].type != "COM"):
                    raise Exception("Unknown token on position ", i)

        self.DB.Insert(self.__tokens[1].text, varsToInsert)

    def CreateTable(self, tokenLen):

        if (self.__tokens[1].type != "VAR"):
            raise Exception('Incorrect table name')

        if (self.__tokens[2].type != "("):
            raise Exception(' ( expected ')

        if (self.__tokens[3].type != "VAR"):
            raise Exception(' Incorrect field name ')

        if (self.__tokens[tokenLen - 1].type != ")"):
            raise Exception(' ) expected ')

        colums = list()

        indexedFields = list()

        colums.append(self.__tokens[3].text)

        oldTokenType = "VAR"
        if (tokenLen > 5):
            for i in range(4, tokenLen):
                newTokenType = self.__tokens[i].type
                if (
                        newTokenType != "INDEXED" and newTokenType != "COM" and newTokenType != ")" and oldTokenType == "VAR"):
                    raise Exception('Unexpected token on position ', i)
                if (newTokenType != "VAR" and oldTokenType == "COM"):
                    raise Exception('Unexpected token on position ', i)
                if (newTokenType != "COM" and oldTokenType == "INDEXED"):
                    raise Exception('Unexpected token on position ', i)
                if (newTokenType == ")" and (oldTokenType != "VAR" and oldTokenType != "INDEXED")):
                    raise Exception('Unexpected ) on position ', i)
                if (newTokenType == "INDEXED"):
                    indexedFields.append(self.__tokens[i - 1].text)
                    oldTokenType = "INDEXED"
                if (newTokenType == "VAR"):
                    colums.append(self.__tokens[i].text)
                    oldTokenType = "VAR"
                if (newTokenType == "COM"):
                    oldTokenType = "COM"
        self.DB.CreateTable(self.__tokens[1].text, colums, indexedFields)


    # def Select(self, tokenLen):
    #
    #     aggregationTypes = ['COUNT', 'MAX', 'AVG']
    #     allTokenTypes = []
    #
    #
    #     colums = list()
    #     tableName = ''
    #
    #     for i in range(0, tokenLen):
    #         allTokenTypes.append(self.__tokens[i].type)
    #         if self.__tokens[i].type in aggregationTypes:
    #
    #             aggFunctions.append(self.__tokens[i].text)
    #
    #     if (self.__tokens[1].type != "VAR" and self.__tokens[1].type != "ALL" and self.__tokens[
    #         1].type not in aggregationTypes):
    #         raise Exception("Unknown token on position 1")

    def parse(self):
        tokenLen = len(self.__tokens)
        if (tokenLen == 0):
            raise Exception('Empty token array!')

        if (self.__tokens[0].type != "CREATETABLE" and self.__tokens[0].type != "SELECT"  and self.__tokens[0].type != "INSERTINTO"):
            raise Exception('Unknown comand!')

        if (self.__tokens[0].type == "CREATETABLE"):
            self.CreateTable(tokenLen)

        if (self.__tokens[0].type == "INSERTINTO"):
            self.Insert(tokenLen)

        # if (self.__tokens[0].type == "SELECT"):
        #     self.Select(tokenLen)