class Token:
  def __init__(self, type, text, pos):
    self.type = type
    self.text = text
    self.pos = pos


class TokenP:
  def __init__(self, type, comand):
    self.type = type
    self.comand = comand


word = {
  'CREATETABLE': TokenP('CREATETABLE', 'CREATETABLE'),
  'INDEXED': TokenP('INDEXED', 'INDEXED'),
  'COM': TokenP('COM', ','),
  '(': TokenP('(', '\\('),
  ')': TokenP(')', '\\)'),
  '[': TokenP('[', '\\['),
  ']': TokenP(']', '\\]'),
  'VAR': TokenP('VAR', '[_a-z][_a-z0-9]+'),
  'NUMBER': TokenP('NUMBER', '[-+]?[0-9]+'),
  'SELECT': TokenP('SELECT', 'SELECT'),
  'FROM': TokenP('FROM', 'FROM'),
  'INSERTINTO': TokenP('INSERTINTO', 'INSERTINTO'),
  'WHERE': TokenP('WHERE', 'WHERE'),
  'EQUAL': TokenP('EQUAL', '='),
  'NOT_EQUAL': TokenP('NOT_EQUAL', '!='),
  'MORE_EQUAL': TokenP('MORE_EQUAL', '>='),
  'LESS_EQUAL': TokenP('LESS_EQUAL', '<='),
  'LESS': TokenP('LESS', '<'),
  'MORE': TokenP('MORE', '>'),
  'ALL': TokenP('ALL', '\\*'),
  'COUNT': TokenP('COUNT', 'COUNT$'),
  'MAX': TokenP('MAX', 'MAX')
}