import db

t1 = db.table("table1", ["name", "bd"], ["", "", ""])
t1.new_row(["kost3", "10"])
t1.new_row(["kost3", "20"])
t1.new_row(["kost", "10"])
t1.print_table()

sel = db.select(t1, "names", "kost3")
sel.print_table()