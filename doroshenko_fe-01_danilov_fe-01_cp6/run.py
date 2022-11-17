from lexer import Lexer
from parser import Parser
from DataBase.index import DataBase

DB = DataBase()
def run(text):
    lexer = Lexer(text)
    tokens, error = lexer.make_tokens()
    if error:
        return None, error
    parser = Parser(DB)
    parser.setTokens(tokens)
    # print(parser.getTokens())
    parser.parse()
    return tokens, None
