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
    std::cout << db.callCommand("SELECT FROM cats WHERE age <= \"5\";") << std::endl; 
    std::cout << db.callCommand("SELECT FROM cats WHERE name > \"Ky\" ORDER_BY name DESC, dish ASC;") << std::endl;

    // db.start();

    /////////////////////////////////////////////////////////
    //////////////////// Excample commands: /////////////////
    /////////////////////////////////////////////////////////
    
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

    return 0;
}