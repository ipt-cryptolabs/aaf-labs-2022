from Pars1 import *

print("Welcome! We have some recommendations and small instruction for you.\nPlease, read it till the end before "
      "you start. Our recommendations:\n  1. If you want to create table, use 'CREATE table (column1,..., columnN);'\n "
      " 2. If you want to insert something, use 'INSERT [INTO] table_name (“value” [, ...]);'\n  3. If you want to see "
      "information from table, use 'SELECT FROM table_name;'\n  4. And if you want to finish your project and close "
      "the program, use 'EXIT;'\nThank you for your attention and have a nice work!\n")

while True:
    command = ""
    i = 0
    while True:
        if i == 0:
            our_input = input(">>> ")
        else:
            our_input = input("... ")
        i += 1
        command += (our_input + "\n")
        if ";" in our_input:
            break
    pars(command)
