import parser1
from Table import Table
from database import DataBase

if __name__ == "__main__":
    dataBase = DataBase()
    command = None
    line = ' '
    print('Enter:')
    line = line + input()
    while True:
        if line[-1] != ';':
            line = line + ' ' + input()
        else:
            command = parser1.parse(line)
            if command[0] == 'CREATE':
                dataBase.append_table(command)
            elif command[0] == 'INSERT':
                if command[1] in dataBase.tables.keys():
                    dataBase.tables[command[1]].insert(command[2])
                else:
                    print(f"Table with name {command[1]} doesn`t exists")
            elif command[0] == 'SELECT':
                dataBase.select(command)
            else:
                print(command)
            print('Enter:')
            line = ' '


"""
create t(x INDEXED, y, z INDEXED);
insert t("aaa", "zz1", "zz1");
insert t("aaa", "zz2", "zz1");
insert t("mmm", "mmm", "zz1");
insert t("xxx", "bbb", "zz1");
insert t("yyy", "bbb", "zz1");
select from t;
select from t where x > "g";
"""


"""
create t1(a, b);
insert t1("aaa", "b1");
insert t1("aaa", "b2");
insert t1("bbb", "b3");
insert t1("ccc", "b4");
insert t1("www", "b5");
insert t1("xxx", "b6");
create t2(x, y);
insert t2("aaa", "y1");
insert t2("bbb", "y2");
insert t2("bbb", "y3");
insert t2("ccc", "y4");
insert t2("yyy", "y5");
insert t2("zzz", "y6");
SELECT FROM t1 JOIN t2 ON a = x;
SELECT FROM t1 JOIN t2 ON a = x where b > "0";
SELECT FROM t1 JOIN t2 ON a = x where y > b;
SELECT FROM t1 JOIN t2 where b > y;
"""