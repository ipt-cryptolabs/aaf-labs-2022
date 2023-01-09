import re
from searchtree import Node

class Collection:
    def __init__(self):
        self.indx = 0
        self.docs = {}


def check_status(status, col ="", index = 0):
    statuses = {
        4: f"Following index {index} deleted from collection {col}",
        3: f"Collection {col} has been deleted",
        2: f"Text added to coll. '{col}' by index {index}",
        1: f"New coll. '{col}' has been created",
        0: "This command not found",
        -1: "Wrong first char in name",
        -2: "Wrong char in name",
        -3: "This name is already in use",
        -4: "Wrong parameter number",
        -5: "There is no such collection",
        -6: "Wrong \"\"",
        -7: "Wrong input",
        -8: "There is no WHERE",
        -9: "There is no condition",
        -10: "Wrong syntax",
        -11: "Wrong index",
        -12: "No text!",
        -13: "Nothing found",
        -14: "The collection is empty",
        -15: "This keyword is not found"
    }

    if status != 100:
        print(statuses[status])


def create(col, collection_elems):
    # перевірка на унікальність імені
    if col in collection_elems.keys():
        return collection_elems, col, -3

    collection_elems[col] = Collection()
    return collection_elems, col, 1

def insert(col, text, collection_elems, i_reversed):
    # неправильне ім'я        
    if collection_elems.get(col) is None:
        index = 0
        return collection_elems, i_reversed, col, index, -5
    

    doc = collection_elems[col].indx
    collection_elems[col].indx += 1
   
    collection_elems[col].docs.update({doc: text})
   

    words = re.split('[^a-zA-Z0-9_]+', text)
    while '' in words: words.remove('')
    words = [x.lower() for x in words]
 
    if col not in i_reversed.keys():
        i_reversed[col] = Node(words[0], doc, 0)
        range_list = range(1,len(words))
    else:  
        range_list = range(len(words))

    for i in range_list: 
        i_reversed[col].insert(words[i], doc, i)

    return collection_elems, i_reversed, col, doc, 2

def search(col, usraction, usrevent, collection_elems, i_reversed):
          
    if collection_elems.get(col) is None:
        return collection_elems, col, -5
    
    if collection_elems[col].docs == {}:
        return collection_elems, col, -14



    result = None

    if usrevent == 0:
        for doc in collection_elems[col].docs:
            print(f"{doc}: \"{collection_elems[col].docs[doc]}\"")
        result = True

    elif usrevent == 1:
        result = i_reversed[col].search1(usraction.lower())
        if result != None:
            for doc in result.keys():
                print(f"{doc}: \"{collection_elems[col].docs[doc]}\"")

    elif usrevent == 2:
        result = i_reversed[col].search2(usraction.lower())
        if result != []:
            set_docs = set()
            for elem in result:
                set_docs.update(elem.indexes.keys())

            for doc in set_docs:
                print(f"{doc}: \"{collection_elems[col].docs[doc]}\"")
        else: result = None

    elif usrevent == 3:
        wordf = usraction[0].lower()
        words = usraction[1].lower()
        n = usraction[2]

        # отримання інвертованих індексів для ключових слів
        wordf_i = i_reversed[col].search1(wordf)
        words_i = i_reversed[col].search1(words)

        if wordf_i is None or words_i is None: # неправильне ключове слово
            return collection_elems, col, -15


        docs = list(set(wordf_i.keys()) & set(words_i.keys())) # звичайні документи
        for doc in docs:
            found = False
            i, j = 0, 0
            while(i < len(words_i[doc]) and j < len(wordf_i[doc])):
                #print(i, j)
                if abs(words_i[doc][i] - wordf_i[doc][j]) == n:
                    print(f"{doc}: {collection_elems[col].docs[doc]}")
                    result = True 
                    found = True
                    break
                elif words_i[doc][i] - wordf_i[doc][j] < n: i += 1
                elif words_i[doc][i] - wordf_i[doc][j] > n: j += 1

            if found: continue

            i, j = 0, 0
            words_i, wordf_i = wordf_i, words_i # заміна wordf і words
            while(i < len(words_i[doc]) and j < len(wordf_i[doc])):
                #print(i, j)
                if abs(words_i[doc][i] - wordf_i[doc][j]) == n:
                    print(f"{doc}: {collection_elems[col].docs[doc]}")
                    result = True 
                    break
                elif words_i[doc][i] - wordf_i[doc][j] < n: i += 1
                elif words_i[doc][i] - wordf_i[doc][j] > n: j += 1

    if result is None:
        return collection_elems, col, -13

    return collection_elems, col, 100

def print_indexes(col, i_reversed):
    if col in i_reversed.keys():
        i_reversed[col].treeout()    
    else: print("Collection not found or is empty!")


def exit(inputline):
    pass
