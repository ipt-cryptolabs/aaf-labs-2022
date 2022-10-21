import re
import functions
import myparser


while True:
    line = input("   > ")
    if line != "":
        result = myparser.make_normal(line)

        print(result)
        func = myparser.parse(result)
        print(func)
        if func[0].lower() == "create":
            functions.create(func)
        elif func[0][0:6].lower() == "insert":
            functions.insert(func)
        elif func[0][0:6].lower() == "select":
            functions.select(func)
    else:
        break
