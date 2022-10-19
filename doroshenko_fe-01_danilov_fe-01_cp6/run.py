from lexer import Lexer
from parser import Parser


def run(text):
    lexer = Lexer(text)
    tokens, error = lexer.make_tokens()
    print('Lexer:', tokens)
    if error:
        return None, error
    parser = Parser(None)
    parser.setTokens(tokens)
    # print(parser.getTokens())
    parser.parse()
    return tokens, None
