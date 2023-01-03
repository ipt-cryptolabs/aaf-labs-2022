import os
import pickle
import Checker

db_path = 'Databases/'

# To simplify workflow we have only one db instead of whole list:

databases = []


# databases = list()


class Column:
    def __init__(self, title: str, isIndexed: bool = False):
        self.title = title
        self.indexed = isIndexed

    def __eq__(self, other):
        if self.title == other.title:
            return True
        return NotImplemented


class Table:
    def __init__(self, title: str, columns: list):  # list of Column
        if not Checker.is_correct_title(str(title)):
            print(f'[!] Table title may not start with {str(title)[0]}')
            del self
        self.title = title
        self.columns = []

        if columns:
            for column in columns:
                if not Checker.is_correct_column(column):
                    del self
                    return
            self.columns = columns
        self.rows = list()

    def get_indexed(self):
        indexed = []
        for column in self.columns:
            if column.indexed:
                indexed.append(column)
        return indexed

    def insert_row(self, columns: list, row: list):
        if Checker.is_correct_row(row, self.rows, self.columns):
            columns_id = []
            for column in columns:
                if column in self.columns:
                    columns_id.append(int(self.columns.index(column)))

            row_to_insert = []
            tmp_counter = 0
            for col_index in range(len(self.columns)):
                if col_index in columns_id:
                    row_to_insert.append(row[tmp_counter])
                    tmp_counter += 1
                else:
                    row_to_insert.append(None)

            self.rows = row_to_insert
        else:
            return 0

    def get_values(self, columns: list):
        if not Checker.is_correct_select(self.columns, columns):
            return None
        columns_id = []
        for column in columns:
            if column in self.columns:
                columns_id.append(int(self.columns.index(column)))

        result = []
        for index in columns_id:
            result.append(self.rows[index])

        return result


class DB:
    def __init__(self, name: str):
        self.name = name
        self.tables = list()
        if os.path.isfile(db_path + '/' + name):
            print(f"[!] Error. DB with the name '{name}' already exists.")
            del self

    def create_table(self, table: Table):
        if table:
            if table.title in [x.title for x in self.tables]:
                print(f'[!] Error. Table with title {table.title} already exists.')
                return 0
            self.tables.append(table)
            self.save()
            return 1
        print("[!] Error. Empty table given.")
        return 0

    def get_table(self, table_title):
        table = list(filter(lambda x: x.title == table_title, self.tables))
        if table:
            return table[0]
        else:
            print(f"[!] Error. There is no '{table_title}' table in list")

    def save(self):
        with open(db_path + self.name + '.senseidb', 'wb') as f:
            pickle.dump(self, f)

    def print(self):
        print(f"DB name: {self.name}")
        for table in self.tables:
            print(f'\t> {table.title}')
            for column in table.columns:
                if column and column.indexed:
                    print(f'\t  - ({column.title}) [indexed]')
                else:
                    print(f'\t  - ({column.title})')
            print(f'\tRows count: {len(table.rows)}')


# def save_DB(db: DB, path: str = db_path):
#     with open(db.name + '.senseidb', 'w') as f:
#         serialized_db = pickle.dumps(db)
#         f.write(str(serialized_db))

def get_DB(name: str):
    db = list(filter(lambda x: x.name == name, databases))
    if db:
        return db[0]
    else:
        print(f"[!] Error. There is no '{name}' database in the list")


def load_DBs(path: str = db_path):
    filenames = os.listdir(path)
    temp_databases = list()

    for filename in filenames:
        db_filepath = bytes(db_path + filename, encoding='UTF-8')
        with open(db_filepath, 'rb') as f:
            deserialized_db = pickle.load(f)
            temp_databases.append(deserialized_db)

    return temp_databases


def run_DB(db_title: str = 'main_db'):
    global databases
    global db_path

    custom_path = False
    # db_path = input("> Enter path:")
    if not db_path:
        db_path = './Databases'
    if not os.path.isdir(db_path):
        os.mkdir(db_path)
    databases = load_DBs(db_path)
    if not databases:
        item = DB(db_title)
        databases.append(item)

# def upload_DBs(path: str = db_path):
#     for db in databases:
#         with open(db_path + db.name + '.senseidb', 'w') as f:
#             serialized_db = pickle.dumps(db)
#             f.write(str(serialized_db))

# def load(self, path: str = db_path):
#     if self.name+'.senseidb' in os.listdir(path):
#         with open(db_path + self.name + '.senseidb', 'r') as f:
#             item = f.read()
#             self.__dict__ = pickle.loads(item)
#             databases.append(self)
