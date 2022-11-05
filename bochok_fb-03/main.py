import functions
import myparser1

while True:
    line = input("   > ")
    result = myparser1.make_normal(line)

    # print(result)
    func = myparser1.parse(result)
    # print(func)
    if func[0].lower() == "create":
        functions.create(func)
    elif func[0][0:6].lower() == "insert":
        functions.insert(func)
    elif func[0][0:6].lower() == "select":
        functions.select(func)
    else:
        print(func)
