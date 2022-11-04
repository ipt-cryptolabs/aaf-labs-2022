import db

t1 = db.table("table1", ["id", "name", "bd"], ["", "", ""])
t1.add_row(["1", "kost", "10"])
t1.add_row(["2", "kost", "20"])
t1.print_table()
