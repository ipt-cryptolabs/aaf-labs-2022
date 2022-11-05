import db

t1 = db.table("table1", ["name", "bd"], ["", "", ""])
t1.new_row(["kost", "10"])
t1.new_row(["kost3", "20"])
t1.print_table()
print(t1.get_row(1))
print(t1.get_row(0))
print(t1.get_row(2))
print(t1.get_row(t1.where("name", "kost3")))
