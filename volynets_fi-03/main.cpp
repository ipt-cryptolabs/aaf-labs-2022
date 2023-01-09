#include <iostream>
// #include "DB_terminal.h"
#include "tests.cpp"
#include "Database.h"

using namespace std;

int main(){
    DB_terminal db;
    
    db.start();

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
