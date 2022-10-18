#include <iostream>
// #include "DB_terminal.h"
#include "tests.cpp"
#include "Database.h"

using namespace std;

int main(){
    testAll();

    // DB_terminal db;
    // db.start();

    // CREATE students (name INDEXED, group, cats_name );
    // INSERT INTO cats ("1", "Murzik", "Sausages");
    // insert InTO cats ("1", "Murzik", "Sausages");
    // SELECT FROM table_name WHERE value_x > "45" ORDER_BY column_name DESC, id ASC;
    // exit*;   // for exitthe program 

    Table t({"name", "age", "sex", "country"});
    
    t.insert({"sergio", "34", "M", "34"});
    t.insert({"tanya", "23", "F", "24"});
    t.insert({"ricardo", "20", "yes", "13"});
    t.insert({"tanya", "25", "F", "30"});
    t.insert({"tanya", "25", "F", "31"});
    t.print();
    // t.select("name", ">", "age", {{"age","DESC"}});
    // t.select("name", ">", "age", {{"name","ASC"}, {"age","DESC"}});
    std::cout << t.select("age", ">", "\"25\"", {{"age","DESC"}});
    std::cout << t.select("age", "<>", "country", {{"age","DESC"}});


    return 0;
}