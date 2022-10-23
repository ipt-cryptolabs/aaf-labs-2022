#include <iostream>
// #include "DB_terminal.h"
#include "tests.cpp"
#include "Database.h"

using namespace std;

int main(){
    // testAll();

    DB_terminal db;
    
    db.callCommand("CREATE    cats (age INDEXED, name, dish);");
    db.callCommand("INSERT INTO cats (\"7\", \"Murzik\", \"Sausages\");");
    db.callCommand("insert InTO cats (\"1\", \"Kyselut\", \"Sausages, with  double chease\");");
    db.callCommand("INSERT INTO cats (\"3\", \"Gladislav\", \"Brokoli\");");
    db.callCommand("INSERT INTO cats (\"5\", \"Kysimir\", \"fingers\");");
    db.callCommand("INSERT INTO cats (\"8\", \"Moushebor\", \"mouse\");");
    db.callCommand("INSERT INTO cats (\"13\", \"Vladivan\", \"Divanchic\");");
    db.callCommand("INSERT INTO cats (\"13\", \"Vladivan\", \"Divan\");");
    db.callCommand("INSERT INTO cats (\"6\", \"Pyzochos\", \"Cabels\");");
    std::cout << db.callCommand("SELECT FROM cats;") << std::endl;
    std::cout << db.callCommand("SELECT FROM cats WHERE age > \"5\";") << std::endl;
    std::cout << db.callCommand("SELECT FROM cats WHERE name > \"Ky\" ORDER_BY name DESC, dish ASC;") << std::endl;

    // db.start();

// CREATE    cats (age INDEXED, name, dish);
// INSERT INTO cats ("7", "Murzik", "Sausages");
// insert InTO cats ("1", "Kyselut", "Sausages, with  double chease");
// INSERT INTO cats ("3", "Gladislav", "Brokoli");
// INSERT INTO cats ("5", "Kysimir", "fingers");
// INSERT INTO cats ("8", "Moushebor", "mouse");
// INSERT INTO cats ("13", "Vladivan", "Divanchic");
// INSERT INTO cats ("13", "Vladivan", "Divan");
// INSERT INTO cats ("6", "Pyzochos", "Cabels");
// SELECT FROM cats;
// SELECT FROM cats WHERE age > "4";
// SELECT FROM cats ORDER_BY name DESC, dish ASC;
// SELECT FROM cats WHERE age > "4" ORDER_BY name DESC, dish ASC;
// exit*;   // for exitthe program 

    // Table t({"name", "age", "sex", "country"});
    
    // t.insert({"sergio", "34", "M", "34"});
    // t.insert({"tanya", "23", "F", "24"});
    // t.insert({"ricardo", "20", "yes", "13"});
    // t.insert({"tanya", "25", "F", "30"});
    // t.insert({"tanya", "25", "F", "31"});
    
    // std::cout << t.select() << std::endl;
    // std::cout << t.select("age", "<", "\"25\"") << std::endl;
    // std::cout << t.select("age", "<", "\"25\"", {{"age","DESC"}}) << std::endl;

    // std::cout << t.select("age", "<>", "country", {{"age","DESC"}}) << std::endl;
    // std::cout << t.select("age", "<>", "country") << std::endl;
    // std::cout << t.select({{"age","DESC"}}) << std::endl;
    


    return 0;
}