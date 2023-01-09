class Table:  # class for all data. table = collection(instance of a class)
    def __init__(self, collections):
        self.collections = collections  # dictionary of collection name and values

    def create_collection(self, collection_name, collections):
        collection_name = collection_name[:-1]
        collections[collection_name] = []
        print("New collection added.")

    def insert(self, value, collections, collection_name):
        value = value[:-2]
        value = value[1:]
        value = value.replace('"', '')
        list_of_values = collections[collection_name]
        list_of_values.append(value)
        print("Insert new value.")

    def find_indixes(self, list_to_check, item_to_find):  # find all indexes for all elements
        indixes = []
        for idx, value in enumerate(list_to_check):
            if value == item_to_find:
                indixes.append(idx + 1)
        return indixes

    def take_words_unique(self, collections, collection_name):
        list_of_values = collections[collection_name]
        list_with_unique_elements = []
        for val in list_of_values:
            val = val.lower()
            list_from_elements = list(val.split(" "))
            for word in list_from_elements:
                if word not in list_with_unique_elements:
                    list_with_unique_elements.append(word)
        return list_with_unique_elements

    def find_indexes_for_words(self, collections, collection_name, number_of_doc, el_to_find):
        list_of_values_collection = collections[collection_name]
        current_dc = list_of_values_collection[number_of_doc]
        current_dc = current_dc.lower()
        list_of_curr_dc = list(current_dc.split(" "))
        indexes = self.find_indixes(list_of_curr_dc, el_to_find)
        return "dc" + str(number_of_doc + 1) + " => " + str(indexes)

    def print_index(self, collections, collection_name):
        collection_name = collection_name[:-1]
        list_of_val = collections[collection_name]
        list_with_unique_elements = self.take_words_unique(collections, collection_name)
        for word in list_with_unique_elements:
            print('"' + word + '"' + ":")
            for num in range(len(list_of_val)):
                print(self.find_indexes_for_words(collections, collection_name, num, word))

    def search_without_options(self, collections, collection_name):  # SEARCH wiki_articles;
        collection_name = collection_name[:-1]
        list_of_values = collections[collection_name]
        for index in range(len(list_of_values)):
            print("dc" + str(index + 1))
            print('"' + list_of_values[index] + '"')

    def search_by_keyword(self, collections, collection_name, keyword):
        keyword = keyword[:-2]
        keyword = keyword[1:]
        list_of_values = collections[collection_name]
        sample_to_print = []
        for current_dc in list_of_values:
            current_dc1 = current_dc.lower()
            list_of_curr_dc = list(current_dc1.split(" "))
            if keyword in list_of_curr_dc:
                sample_to_print.append(list_of_values.index(current_dc))
                print("dc" + str(list_of_values.index(current_dc) + 1) + ":")
                print('"' + current_dc + '"')
            else:
                print("no dc found")


collections = {}

#
# print("------------------creating Class Table--------------------------------------------------------")
# new_colletion = Table(collections)
# # print("---------------------------------creating new collections-------------------------------------")
# new_colletion.create_collection("First collection;", collections)
# new_colletion.create_collection("Second collection", collections)
# print("---------------------------------inserting new values------------------------------------------")
# new_colletion.insert("he likes how he eats ice", collections,"First collection" )
# new_colletion.insert("He likes how he drives", collections,"First collection" )
# new_colletion.insert("he drives fast", collections,"Second collection" )
# print("---------------------------------collection preview--------------------------------------------")
# print(collections)
# print("---------------------------------function(print all unique word in collection) check-----------")
# #new_colletion.print_index(collections, "First collection")
# print(new_colletion.take_words_unique(collections, "First collection"))
# print("---------------------------------printing indexes----------=------------------------------------")
# new_colletion.print_index(collections, "First collection")
# print("---------------------------------searching without options--------------------------------------")
# new_colletion.search_without_options(collections, "First collection")
# print("----------------------------------search with keyword-------------------------------------------")
# new_colletion.search_by_keyword(collections, "First collection", "drives")
# print("------------------")
# new_colletion.search_by_keyword(collections, "First collection", "he")
