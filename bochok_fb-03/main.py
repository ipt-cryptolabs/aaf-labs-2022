import re
import functions
import myparser1


while True:
    line = input("   > ")
    if line != "":
        result = myparser1.make_normal(line)

        func = myparser1.parse(result)
        
        if func[0].lower() == "create":
            functions.create(func)
        elif func[0][0:6].lower() == "insert":
            functions.insert(func)
        elif func[0][0:6].lower() == "select":
            functions.select(func)
    else:
        break
