from run import run


def test(command):
    tokens, error = run(command)


command_create = "CREATE cats cat_id INDEXED, cat_owner_id INDEXED, cat_name;"
command_insert = "INSERT INTO owners ('2', 'Kolya', '28');"
command_select = "SELECT FROM cats;"
command_where = "SELECT FROM cats WHERE name = 'Murzik';"
command_full_join = "SELECT FROM owners FULL_JOIN cats ON owner_id = cat_owner_id;"

db_test1 = "CREATE cats (cat_id, cat_owner_id, cat_name);"
db_test2 = "INSERT INTO cats ('2', 'Kolya', '28');"

test(command_create)
test(command_insert)
test(command_select)
test(command_where)
test(command_full_join)
