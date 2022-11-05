def create(args):
    print(f"The table {args[1]} has been created!")
    return


def insert(args):
    print(f"1 row has been added to {args[1]}!")
    return


def select(args):
    line = f"Selecting from table {args[1]}"
    if len(args) == 2:
        line += "..."
    elif len(args) == 8:
        line += f"\nleft_join table {args[3]} on columns: {args[5]}, {args[-1]}"
    elif len(args) == 6:
        line += f"\ncondition: {args[3]} {args[4]} {args[5]}"
    else:
        line += f"""\nleft_join table {args[3]} on columns {args[5]}, {args[7]}
condition: {args[9]} {args[10]} {args[11]}"""
    print(line)
    return
