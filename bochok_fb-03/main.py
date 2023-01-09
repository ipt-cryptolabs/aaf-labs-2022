import db_functions
import myparser1

crude_db = db_functions.DB()

while True:
    line = input("   > ")
    result = myparser1.make_normal(line)

    # print(result)
    func = myparser1.parse(result)
    # print(func)
    if func[0].lower() == "create":
        crude_db.create(func)
    elif func[0][0:6].lower() == "insert":
        crude_db.insert_row(func)
    elif func[0][0:6].lower() == "select":
        crude_db.select(func)
    else:
        print(func)
