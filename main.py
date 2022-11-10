from func import *


class Parser:
    def __init__(self, collection):
        self.collection = collection # екземпляр класу Table

    def take_input(self):
        raw = input()
        raw = raw.lower().split()
        com_lst = []
        if raw[0] == "exit":
            return False
        for i in raw:
            if i == ';' or (';' in i):
                com_lst.append(i)
                break

            else:
                com_lst.append(i)
        return com_lst

    def call_functions_from_table(self):
        collection = self.collection
        parsed_input = self.take_input()
        if not parsed_input:
            return False
        elif parsed_input[0] == 'create':
            collection.create_collection(parsed_input[1], collection.collections)
        elif parsed_input[0] == 'insert':
            string_for_insert = ''
            for i in range(2, len(parsed_input)):
                string_for_insert += parsed_input[i]
                string_for_insert += ' '
            collection.insert(string_for_insert, collection.collections, parsed_input[1])
        elif parsed_input[0] == 'print_index':
            collection.print_index(collection.collections, parsed_input[1])
        return collection


collections = {}
new_collection = Table(collections)
parser = Parser(new_collection)
while True:
    new_collection = parser.call_functions_from_table()
    if not new_collection:
        break

