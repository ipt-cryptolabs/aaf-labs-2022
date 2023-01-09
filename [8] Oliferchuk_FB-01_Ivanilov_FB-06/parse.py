import re

def input_list(inputline):
    inputline = inputline.upper().split()
    if not len(inputline) or len(inputline) < 2 and inputline[0] not in ["EXIT", "SHOW"]:
        return " ", -7
    key_words = ["CREATE", "INSERT", "SEARCH", "REMOVE", "EXIT", "PRINT_INDEX", "SHOW"]
    return (inputline[0], 100) if inputline[0] in key_words else (" ", -7)

def text_off(text):
    
    # видалення симвоілв після знаку ;
    find_end = lambda x: len(x) if x.find(";") == -1 else x.find(";")
    text = text[:find_end(text)] 

    # видалення символів після пробілу
    text = text.split()
    text = ' '.join(list(text))
    return text

def inputreader(inputline):

    inputline = inputline.split()
    name = inputline[1]

    # неправильне ім'я
    if re.search("[a-zA-Z]", name[0]) is None: # перша літера
        return name, -1
    if re.search("[a-zA-Z0-9_]*", name) is None: # інші символи
        return name, -2

    # забагато параметрів
    return (name, -4) if len(inputline) > 2 else (name, 100)


def input_ex(inputline):
    inputline = inputline.split()

    return -4 if len(inputline) > 1 else 100

def input_srch(inputline):
    inputline = inputline.split()
    name = inputline[1]
    usraction = ""
    # пошук WHERE
    if len(inputline) >= 3:
        # неправильний ввід/порядок вводу WHERE
        if inputline[2].upper() != "WHERE":
            return name, usraction, -8
        # пропущено usraction
        if len(inputline) == 3:
            return name, usraction, -9
        # "витягування" usraction
        usraction = inputline[3:]
        usraction = ' '.join(list(usrevent))
    return name, usraction, 100


def parse_insert(inputline):
    inputline = inputline.split()
    name = inputline[1]

    text = ""

    if len(inputline) < 3: # відсутність тексту
        return name, text, -12

    index = 0
    i = 0
    while (i < len(inputline)):
        if inputline[i][-1] == "\"":
            index = i
        i += 1
    i -= 1



    # неправильні ""        
    if inputline[2][0] != "\"" or inputline[-1][-1] != "\"": # пропущено подвійні лапки
        return name, text, -6

    # забагато параметрів 
    if i != index:
        return name, text, -4

    # отримання тексту
    text = ' '.join(list(inputline[2:index+1]))
    text = text.strip("\"").strip()
    print(f"'{text}'")
    return name, text, 100

def input_rem(inputline):
    inputline = inputline.split()
    usrevent = 0
    name = inputline[1]
    index = 0
    if len(inputline) == 2:
        usrevent = 1
    elif len(inputline) == 3:
        usrevent = 2
        index = inputline[2]
    else:
        return usrevent, name, index, -4
    return usrevent, name, index, 100

def input_outindex(inputline):
    inputline = inputline.split()
    name = inputline[1]
    return (name, -4) if len(inputline) > 2 else (name, 100)

def input_get(inputline):
    inputline = inputline.split()

    return -4 if len(inputline) > 1 else 100


def parse_usraction(usraction):

    if not len(usraction): # відсутність WHERE
        usrevent = 0
    # ключове слово
    elif usraction[0] == "\"" and usraction[-1] == "\"" \
        and usraction.count("\"") == 2:
        usraction = usraction[1:-1]
        usrevent = 1
    # ключове слово + '*'
    elif usraction[0] == "\"" and usraction[-2] == "\"" and usraction[-1] == "*":
        usraction = usraction[1:-2]
        usrevent = 2
    # keywordf <N> keywords
    elif usraction[0] == "\"" and usraction[-1] == "\"" \
        and usraction.count("\"") == 4 and usraction.index("<") < usraction.index(">"):
        keywordf = usraction[1:usraction.index("\"", 1,-1)]
        keywords = usraction[usraction.index("\"", usraction[1:].find("\"")+2, -1)+1:-1]
        N = usraction[usraction.index("<")+1:usraction.index(">")]
        usraction = [keywordf, keywords, int(N)]
        usrevent = 3
    else:
        return -1, usraction, -10
    return usrevent, usraction, 100
