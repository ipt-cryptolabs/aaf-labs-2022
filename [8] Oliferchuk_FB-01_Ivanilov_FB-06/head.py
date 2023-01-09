import userinput
import parse

collection_elems = {}
i_reversed = {} 

print("Enter userinput")

while True:
    status = 0

    text = ""

    while ";" not in text: # багатолінійне введення
        text += " "
        text += input(">>")

    text = parse.text_off(text)


    inputline, status = parse.input_list(text)
    userinput.check_status(status)
    if status == -7:
        continue

    if inputline == "CREATE":

        name, status = parse.inputreader(text)
        userinput.check_status(status)
        if status <= 0: continue # перевірка на помилку
        collection_elems, name, status = userinput.create(name, collection_elems)
        userinput.check_status(status, name)

    elif inputline == "INSERT":

        name, text, status = parse.parse_insert(text)
        userinput.check_status(status)
        if status <= 0: continue # перевірка на помилку
        collection_elems, i_reversed, name, index, status = userinput.insert(name, text, collection_elems, i_reversed)
        userinput.check_status(status, name, index)

    elif inputline == "REMOVE":
        usrevent, name, index, status = parse.input_rem(text)
        userinput.check_status(status)
        if status <= 0: continue # перевірка на помилку
        collection_elems, name, i_reversed, index, status = userinput.remove(usrevent, name, collection_elems, i_reversed, index)
        userinput.check_status(status)


    elif inputline == "SEARCH":
        name, usraction, status = parse.input_srch(text)
        userinput.check_status(status)
        if status <= 0: continue # перевірка на помилку
        usrevent, usraction, status = parse.parse_usraction(usraction)
        userinput.check_status(status)
        if status <= 0: continue

        collection_elems, name, status = userinput.search(name, usraction, usrevent, collection_elems, i_reversed)
        userinput.check_status(status)

    elif inputline == "PRINT_INDEX":
        name, status = parse.input_outindex(text)
        userinput.check_status(status)
        if status < 0: continue
        userinput.print_indexes(name, i_reversed)

    elif inputline == "SHOW":
        status = parse.input_get(text)
        userinput.check_status(status)
        if status < 0: continue
        print(collection_elems)

    elif inputline == "EXIT":
        status = parse.input_ex(text)
        userinput.check_status(status)
        if status < 0: continue
        break
    else:
        userinput.check_status(0)
