import re
from Token import *
import re

class Lexer:
    def __init__(self):
        self.__pos = 0
        self.__code = ''
        self.__TokenArr = []
    def getTokenArr(self):
        return self.__TokenArr

    def setCode(self, code):
        self.__code = code
        self.__pos = 0
        self.__TokenArr = []

    def LexserAnalis(self):
        try:
            while self.__NextToken():
                continue
        except Exception as error:
            text, pos  = error.args
            print(text + ' ' + str(pos) + ": " + self.__code[self.__pos:self.__pos + 10])

    def __NextToken(self):
        if self.__pos == (len(self.__code) ):
            return False
        for TokenP in word.values():
            result = re.search('^' + TokenP.regexp, self.__code[self.__pos:])
            if result:
                self.__pos = self.__pos + len(result[0])
                self.__TokenArr.append(Token(TokenP.type, result[0], self.__pos))
                return True