from Patterns, Token import *
import re


def pars(command):
    patt_num = -1
    for i in range(len(pattern)):
        if pattern[i].match(command):
            patt_num = i
            break

    if patt_num == -1:
        if bool(re.match(probl_list[0], command)):
            print("Incorrect 'CREATE' syntax.")
        elif bool(re.match(probl_list[1], command)):
            print("Incorrect 'INSERT' syntax.")
        elif bool(re.match(probl_list[2], command)):
            print("Incorrect 'SELECT' syntax.")
        elif bool(re.match(probl_list[3], command)):
            print("Incorrect 'EXIT' syntax.")
        else:
            print("This command is unfinded:(")

    else:
        if patt_num == 0:
            created = re.findall(patt_nums[0], command)
            print("Info from 'CREATE':")
            print(created)
        elif patt_num == 1:
            inserted = re.findall(patt_nums[1], command)
            print("Info from 'INSERT':")
            print(inserted)
        elif patt_num == 2:
            selected = re.findall(patt_nums[2], command)
            print("Info from 'SELECT':")
            print(selected)
        elif patt_num == 3:
            print("Thank you for your good choice of application!")
            quit()
