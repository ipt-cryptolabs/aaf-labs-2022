import os
import pickle
import Checker

db_path = './Databases'
databases = list()


class Column:
    def __init__(self, title: str, isIndexed: bool = False):
        self.title = title
        self.indexed = isIndexed


class Table:
    def __init__(self, title: str, columns: list):  # list of Column
        if not Checker.is_correct_title(str(title)):
            print(f'[!] Table title may not start with {str(title)[0]}')
            del self
        self.title = title

        if not columns:
            self.columns = list()
        else:
            for column in columns:
                if not Checker.is_correct_column(str(column.title)):
                    print(f'[!] Column may not start with {str(column[0])}. Table {title} was not created')
                    del self
            self.columns = columns

        self.rows = list()

    def insert_row(self, row: list):
        if Checker.is_correct_row(self.columns, self.rows, row):
            self.rows.append(row)


class DB:
    def __init__(self, name: str):
        self.name = name
        self.tables = list()
        if os.path.isfile(db_path + '/' + name):
            print(f"[!] Error. DB with the name '{name}' already exists.")
            del self

    def create_table(self, table: Table):
        if table:
            self.tables.append(table)
            save_DB(self)
            return 1
        print("[!] Error. Empty table given.")
        return 0


def save_DB(db: DB, path: str = db_path):
    with open(db.name + '.senseidb', 'w') as f:
        serialized_db = pickle.dumps(db)
        f.write(str(serialized_db))


def load_DBs(path: str = db_path):
    filenames = os.listdir(path)
    temp_databases = list()
    for filename in filenames:
        with open(filename + '.senseidb', 'r') as f:
            deserialized_db = pickle.dumps(filename + '.senseidb')
            temp_databases.append(deserialized_db)
    return temp_databases


def upload_DBs(path: str = db_path):
    for db in databases:
        save_DB(db)


def run_DB():
    global databases
    global db_path

    custom_path = False
    # db_path = input("> Enter path:")
    if not db_path:
        db_path = './Databases'
    if not os.path.isdir(db_path):
        os.mkdir(db_path)
        return 0
    databases = load_DBs(db_path)
