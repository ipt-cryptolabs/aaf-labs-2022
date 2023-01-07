import re

from exceptions import IllegalCharError
from config import *


class Token:

  def __init__(self, type_, value=None):
    self.type = type_
    self.value = value

  def __repr__(self):
    if self.value:
      return f'{self.type}:{self.value}'
    return f'{self.type}'


class Position:

  def __init__(self, idx, ln, col, ftxt):
    self.idx = idx
    self.ln = ln
    self.col = col
    self.ftxt = ftxt

  def advance(self, current_char):
    self.idx += 1
    self.col += 1

    if current_char == '\n':
      self.ln += 1
      self.col = 0

    return self

  def copy(self):
    return Position(self.idx, self.ln, self.col, self.ftxt)


class Lexer:

  def __init__(self, text):
    self.text = text
    self.pos = Position(-1, 0, -1, text)
    self.current_char = None
    self.advance()

  def advance(self):
    self.pos.advance(self.current_char)
    self.current_char = self.text[self.pos.idx] if self.pos.idx < len(
      self.text) else None

  def make_tokens(self):
    tokens = []

    while self.current_char:
      if self.current_char in ' \t':
        self.advance()
      elif self.current_char == '(':
        tokens.append(Token(TT_LPAREN, TT_LPAREN))
        self.advance()
      elif self.current_char == ')':
        tokens.append(Token(TT_RPAREN, TT_RPAREN))
        self.advance()
      elif self.current_char == ',':
        tokens.append(Token(TT_COMMA, TT_COMMA))
        self.advance()
      elif self.current_char == ';':
        tokens.append(Token(TT_SEMICOLON, TT_SEMICOLON))
        self.advance()
      elif self.current_char == "\"":
        tokens.append(Token(TT_QUOTE, TT_QUOTE))
        self.advance()
      elif self.current_char == "=":
        tokens.append(Token(TT_EQUALS, TT_EQUALS))
        self.advance()

      elif self.is_allow_char(self.current_char):
        tokens.append(self.make_string())

      else:
        pos_start = self.pos.copy()
        char = self.current_char
        self.advance()
        return [], IllegalCharError(pos_start, self.pos, "'" + char + "'")
    return tokens, None

  def make_string(self):
    some_str = ''
    while self.current_char and self.is_allow_char(self.current_char):
      if self.current_char == '\"':
        break
      else:
        some_str += self.current_char
      self.advance()
    if some_str.upper() in KEYWORDS:
      return Token(some_str.upper(), some_str.upper())
    return Token(TT_STR, str(some_str))

  @staticmethod
  def is_allow_char(string):
    pattern = re.compile(r'[a-zA-Z0-9_]')
    if pattern.match(string):
      return True
    else:
      return False
