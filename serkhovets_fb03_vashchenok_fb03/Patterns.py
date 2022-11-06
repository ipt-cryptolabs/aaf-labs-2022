import re

exit1 = re.compile("^[Ee][Xx][Ii][Tt]\s*;\s*$")
create = re.compile( "^[Cc][Rr][Ee][Aa][Tt][Ee]\s+[a-zA-Z][a-zA-Z0-9_]*\s+\(\s*[a-zA-Z][a-zA-Z0-9_]*(\s*,\s*[a-zA-Z][a-zA-Z0-9_]*)*\s*\)\s*;\s*$")
insert = re.compile( "^[Ii][Nn][Ss][Ee][Rr][Tt](\s+[Ii][Nn][Tt][Oo])?\s+[a-zA-Z][a-zA-Z0-9_]*\s+\(\s*\".+\"(\s*,\s*\".+\")*\s*\)\s*;\s*$")
select = re.compile("^[Ss][Ee][Ll][Ee][Cc][Tt]\s+[Ff][Rr][Oo][Mm]\s+[a-zA-Z][a-zA-Z0-9_]*\s*;\s*$")

probl_list = ["^[Cc][Rr][Ee][Aa][Tt][Ee]", "^[Ii][Nn][Ss][Ee][Rr][Tt]", "^[Ss][Ee][Ll][Ee][Cc][Tt]", "^[Ee][Xx][Ii][Tt]"]

patt_nums = ["[a-zA-Z][a-zA-Z0-9_]*", "(\".+?\")|([a-zA-Z][a-zA-Z0-9_]*)", "[a-zA-Z][a-zA-Z0-9_]*"]

pattern = [create, insert, select, exit1]
