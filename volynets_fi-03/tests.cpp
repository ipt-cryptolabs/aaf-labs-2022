#include <string>
#include <algorithm>
#include "only_linux_colors.cpp"
#include "DB_terminal.h"
#include "Database.h"

bool test(bool rez, std::string fail_info){
    if(!rez){
        std::cout << BOLDRED << fail_info << RESET << std::endl;
    }

    return rez;
}

bool testStringsEquiw(std::string rez, std::string value){
    if(rez != value){
        std::cout << BOLDRED << "Error, must be: " << value << " while get: " + rez << RESET << std::endl;
        return false;
    }

    return true;
}

bool TokenVectorsAreEquiv(std::vector<Token> v1, std::vector<Token> v2){
    bool are_equal = true;

    if(v1.size() != v2.size()){
        return 0;
    }

    for(int i = 0; i < v1.size(); ++i){
        if(v1.at(i).getType() != v2.at(i).getType() || v1.at(i).getValue() != v2.at(i).getValue()){
            are_equal = false;
        }
    }

    return are_equal;
}

bool Test_TokenVectorsAreEquiv(){
    bool testsArePased = true;
    
    std::vector<Token> v1, v2;

    v1 = {Token("sdf", "sdfsd"),Token("sdf", "sdfsd")};
    v2 = {Token("sdf", "sdfsd"),Token("sdf", "sdfsd")};
    testsArePased &= TokenVectorsAreEquiv(v1, v2);

    v1 = {Token("sdf", "sdfsd")};
    v2 = {Token("sdf", "sdfsd"),Token("sdf", "sdfsd")};
    testsArePased &= !TokenVectorsAreEquiv(v1, v2);

    v1 = {Token("sdf", "sdfsd"),Token("sdf", "sdfsf")};
    v2 = {Token("sdf", "sdfsd"),Token("sdf", "sdfsd")};
    testsArePased &= !TokenVectorsAreEquiv(v1, v2);

    v1 = {Token("sdf", "sdfsd"),Token("sdf", "sdfsd")};
    v2 = {Token("sdf", "sdfsfd"),Token("sdf", "sdfsd")};
    testsArePased &= !TokenVectorsAreEquiv(v1, v2);

    if(!testsArePased){
        std::cerr << "TokenVectorsAreEquiv is wrong" << std::endl;
    }

    return testsArePased;
}

bool test_Token_pushValue(){
    bool testsArePased = true;
    Token t;
    char c;
    std::string rez = "";

    c = 'g';
    t.pushValue(c);
    rez = t.getValue();
    testsArePased &= testStringsEquiw(rez, "g");

    t.setValue("dfgre");
    c = 'g';
    t.pushValue(c);
    rez = t.getValue();
    testsArePased &= testStringsEquiw(rez, "dfgreg");

    return testsArePased;
}

bool test_DB_terminal_nextCommand(){ // only manual testing
    bool testsArePased = true;
    DB_terminal db;
    std::string command = db.nextCommand();

    testsArePased &= testStringsEquiw(command, "sdfhj jsdfkas a sjfdlk;");

    return testsArePased;
}

bool test_toUpperCase(){
    bool testsArePased = true;
    std::string rez = "";

    rez = toUpperCase("");
    testsArePased &= testStringsEquiw(rez, "");

    rez = toUpperCase("f");
    testsArePased &= testStringsEquiw(rez, "F");
    
    rez = toUpperCase("F");
    testsArePased &= testStringsEquiw(rez, "F");

    rez = toUpperCase("sdjhjafhdshafkahsf");
    testsArePased &= testStringsEquiw(rez, "SDJHJAFHDSHAFKAHSF");

    rez = toUpperCase("Some text");
    testsArePased &= testStringsEquiw(rez, "SOME TEXT");

    rez = toUpperCase("QWERTY");
    testsArePased &= testStringsEquiw(rez, "QWERTY");
    
    return testsArePased;
}

bool test_interpretToken_string(){
    bool testsArePased = true;
    std::string rez = "";
    std::string t;
    Interpreter i;

    t = "CREATE";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _COMMAND_TOKEN_ , "error on: " + t);

    t = "create";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _COMMAND_TOKEN_ , "error on: " + t);

    t = "ORDER_BY";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _COMMAND_TOKEN_ , "error on: " + t);

    t = "\"dsfGsdaf\"";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _VALUE_TOKEN_ , "error on: " + t);

    t = "dsfGsdaf";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _NAME_TOKEN_ , "error on: " + t);

    t = "\"\"";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _UNDEFINED_TOKEN_ , "error on: " + t);

    t = "\"hkjafhsd78sdf\"";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _VALUE_TOKEN_ , "error on: " + t);

    t = "\"hsdfkhkjhafs";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _UNDEFINED_TOKEN_ , "error on: " + t);

    t = "<>";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _COMPARISON_TOKEN_ , "error on: " + t);

    t = "<=";
    rez = i.interpretToken(t).getType();
    testsArePased &= test(rez == _COMPARISON_TOKEN_ , "error on: " + t);
    
    return testsArePased;
}

bool test_isCorrectLiteral_char(){
    bool testsArePased = true;
    char c = ' ';

    c = 'a';
    testsArePased &= test(isCorrectLiteral(c), "error on " + std::string(1, c));

    c = 'S';
    testsArePased &= test(isCorrectLiteral(c), "error on " + std::string(1, c));

    c = '5';
    testsArePased &= test(isCorrectLiteral(c), "error on " + std::string(1, c));

    c = '_';
    testsArePased &= isCorrectLiteral(c);

    std::string s = "hjhksf_hj34";
    testsArePased &= test(isCorrectLiteral(s.at(1)), "error on " + std::string(1, s.at(1)));

    c = ',';
    testsArePased &= test(!isCorrectLiteral(c), "error on " + std::string(1, c));
    c = '"';
    testsArePased &= test(!isCorrectLiteral(c), "error on " + std::string(1, c));

    if(!testsArePased){
        std::cerr << "isCorrectLiteral_char test is failed" << std::endl;
    }
    
    return testsArePased;
}

bool test_isCorrectLiteral_string(){
    bool testsArePased = true;
    std::string s = "";

    s = "a";
    testsArePased &= test(isCorrectLiteral(s), "error on " + s);

    s = "S";
    testsArePased &= test(isCorrectLiteral(s), "error on " + s);

    s = "\"sdf\"";
    testsArePased &= test(!isCorrectLiteral(s), "error on " + s);

    s = "5";
    testsArePased &= test(isCorrectLiteral(s), "error on " + s);

    s = "_";
    testsArePased &= test(isCorrectLiteral(s), "error on " + s);

    s = "sdf_sdf45_";
    testsArePased &= test(isCorrectLiteral(s), "error on " + s);

    s = ",";
    testsArePased &= test(!isCorrectLiteral(s), "error on " + s);

    s = "sdfdsf sdfa";
    testsArePased &= test(!isCorrectLiteral(s), "error on " + s);

    s = "3sdfdsf_sdfa";
    testsArePased &= test(isCorrectLiteral(s), "error on " + s);

    if(!testsArePased){
        std::cerr << "isCorrectLiteral_string test is failed" << std::endl;
    }
    
    return testsArePased;
}

bool test_convertStringCommandToStringVector(){
    bool testsArePased = true;
    Interpreter i;
    std::string command = "";
    std::vector<std::string> rez, answ;

    command = "CREATE students (name INDEXED, group);";
    rez = i.convertStringCommandToStringVector(command);
    answ = {"CREATE",
            "students",
            "(",
            "name",
            "INDEXED",
            ",",
            "group",
            ")",
            ";"
            };
    testsArePased &= test(rez == answ, "error on " + command);

    command = "CREATE students (name INDEXED, group);";
    rez = i.convertStringCommandToStringVector(command);
    answ = {"CREATE",
            "students",
            "(",
            "name",
            "INDEXED",
            ",",
            "group",
            ")",
            ";"
            };
    testsArePased &= test(rez == answ, "error on " + command);

    command = "SELECT FROM table_name "
                "WHERE value_x > \"45\" "
                "ORDER_BY column_name DESC, id ASC;";
    rez = i.convertStringCommandToStringVector(command);
    answ = {"SELECT",
            "FROM",
            "table_name",
            "WHERE",
            "value_x",
            ">",
            "\"45\"",
            "ORDER_BY",
            "column_name",
            "DESC",
            ",",
            "id",
            "ASC",
            ";"
            };
    testsArePased &= test(rez == answ, "error on " + command);
    
    return testsArePased;
}

bool test_convertStringVectorCommandToTokenVector(){
    bool testsArePased = true;
    std::string command = "";
    std::vector<Token> rez;
    std::vector<Token> answ;
    Interpreter i;

    command = "CREATE students (name INDEXED, group);";
    rez = i.convertStringVectorCommandToTokenVector(i.convertStringCommandToStringVector(command));
    answ = {Token(_COMMAND_TOKEN_, "CREATE"),
            Token(_NAME_TOKEN_, "students"), 
            Token(_OPEN_BRACKET_TOKEN_, "("),
            Token(_NAME_TOKEN_, "name"),
            Token(_COMMAND_TOKEN_, "INDEXED"),
            Token(_COMMA_TOKEN_, ","),
            Token(_NAME_TOKEN_, "group"),
            Token(_CLOSE_BRACKET_TOKEN_, ")"),
            Token(_EOC_TOKEN_, ";"),
            };
    testsArePased &= test(TokenVectorsAreEquiv(rez, answ), "error on: " + command);
    if(!testsArePased){
        printCommand(rez);
    }

    command = "SELECT FROM table_name "
                "WHERE value_x > \"45\" "
                "ORDER_BY column_name DESC, id ASC;";
    rez = i.convertStringVectorCommandToTokenVector(i.convertStringCommandToStringVector(command));
    answ = {Token(_COMMAND_TOKEN_, "SELECT"),
            Token(_COMMAND_TOKEN_, "FROM"),
            Token(_NAME_TOKEN_, "table_name"),
            Token(_COMMAND_TOKEN_, "WHERE"), 
            Token(_NAME_TOKEN_, "value_x"),
            Token(_COMPARISON_TOKEN_, ">"),
            Token(_VALUE_TOKEN_, "\"45\""),
            Token(_COMMAND_TOKEN_, "ORDER_BY"),
            Token(_NAME_TOKEN_, "column_name"),
            Token(_COMMAND_TOKEN_, "DESC"),
            Token(_COMMA_TOKEN_, ","),
            Token(_NAME_TOKEN_, "id"),
            Token(_COMMAND_TOKEN_, "ASC"),
            Token(_EOC_TOKEN_, ";"),
            };
    testsArePased &= test(TokenVectorsAreEquiv(rez, answ), "error on: " + command);
    if(!testsArePased){
        printCommand(rez);
    }

    command = "INSERT INTO cats (“1”, “Murzik”, “Sausages”);";
    rez = i.convertStringVectorCommandToTokenVector(i.convertStringCommandToStringVector(command));
    answ = {Token(_COMMAND_TOKEN_, "INSERT"),
            Token(_COMMAND_TOKEN_, "INTO"),
            Token(_NAME_TOKEN_, "cats"),
            Token(_OPEN_BRACKET_TOKEN_, "("),
            Token(_VALUE_TOKEN_, "\"1\""),
            Token(_COMMA_TOKEN_, ","),
            Token(_VALUE_TOKEN_, "\"“Murzik”\""),
            Token(_COMMA_TOKEN_, ","),
            Token(_VALUE_TOKEN_, "\"“Sausages”\""),
            Token(_OPEN_BRACKET_TOKEN_, ")"),
            Token(_EOC_TOKEN_, ";"),
            };
    testsArePased &= test(TokenVectorsAreEquiv(rez, answ), "error on: " + command);
    if(!testsArePased){
        printCommand(rez);
    }

    return testsArePased;
}

bool test_interpretCommand(){
    bool testsArePased = true;
    std::string command = "", rez = "", answ = "";
    Interpreter i;

    command = "CREATE students (name INDEXED, group);";
    rez = i.interpretCommand(command);
    answ = "Create table students\nname group \nname \n";
    testsArePased &= test(rez == answ, "error on: " + command + "\nRezult is: \n" + rez);
    
    command = "INSERT INTO cats (\"1\", \"Murzik\", \"Sausages\");";
    rez = i.interpretCommand(command);
    answ = "insert cats\n\"1\" \"Murzik\" \"Sausages\" \n";
    testsArePased &= test(rez == answ, "error on: " + rez);

    command = "SELECT FROM table_name WHERE value_x > \"45\" ORDER_BY column_name DESC, id ASC;";
    rez = i.interpretCommand(command);
    answ = "select table_name\nvalue_x > \"45\"\ncolumn_name:DESC id:ASC \n";
    testsArePased &= test(rez == answ, "error on: " + rez);

    return testsArePased;
}

bool test_less_than_key_operator(){
    bool testsArePased = true;
    less_than_key ltk = less_than_key({"name", "second_name", "age", "town"},{{"name","ASC"}, {"age","DESC"}});
    std::vector<std::string> v1, v2;
    
    v1 = {"serhi", "goh", "23", "misisippi"};
    v2 = {"aerhi", "goh", "23", "misisippi"};
    testsArePased &= test(!ltk(v1, v2), "error on 1.");

    v1 = {"aserhi", "goh", "23", "misisippi"};
    v2 = {"serhi", "goh", "23", "misisippi"};
    testsArePased &= test(ltk(v1, v2), "error on 2.");

    v1 = {"serhi", "goh", "23", "misisippi"};
    v2 = {"serhi", "goh", "23", "misisippi"};
    testsArePased &= test(!ltk(v1, v2), "error on 3.");

    v1 = {"serhi", "goh", "24", "misisippi"};
    v2 = {"serhi", "goh", "23", "misisippi"};
    testsArePased &= test(ltk(v1, v2), "error on 4.");

    v1 = {"serhi", "goh", "24", "misisippi"};
    v2 = {"serhi", "goh", "53", "misisippi"};
    testsArePased &= test(!ltk(v1, v2), "error on 5.");

    v1 = {"serhi", "agoh", "53", "misisippi"};
    v2 = {"serhi", "goh", "53", "misisippi"};
    testsArePased &= test(ltk(v1, v2), "error on 6.");

    v1 = {"serhi", "goh", "53", "misisippi"};
    v2 = {"serhi", "agoh", "53", "misisippi"};
    testsArePased &= test(!ltk(v1, v2), "error on 7.");

    return testsArePased;
}

bool test_compare(){
    bool testsArePased = true;
    std::string s1 = "", s2 = "", comp = "";

    s1 = "astring";
    s2 = "string";
    comp = "<";
    testsArePased &= test(compare(s1, s2, comp), "error on b1.");
    
    s2 = "astring";
    testsArePased &= test(!compare(s1, s2, comp), "error on b2.");
    
    comp = "<=";
    testsArePased &= test(compare(s1, s2, comp), "error on b3.");
    
    comp = "==";
    testsArePased &= test(compare(s1, s2, comp), "error on b4.");

    comp = ">=";
    testsArePased &= test(compare(s1, s2, comp), "error on b5.");

    s1 = "astring";
    comp = ">=";
    testsArePased &= test(compare(s1, s2, comp), "error on b6.");

    s1 = "sdf";
    s2 = "aaa";
    comp = ">=";
    testsArePased &= test(compare(s1, s2, comp), "error on b7.");

    comp = "<>";
    testsArePased &= test(compare(s1, s2, comp), "error on b8.");

    s1 = "asd";
    s2 = "asd";
    comp = "<>";
    testsArePased &= test(!compare(s1, s2, comp), "error on b9.");

    return testsArePased;
}

bool testAll(){
    bool testsArePased = true; 

    ////////////////////////////////////////////////////////////
    //////////////////// DB_terminal tests /////////////////////
    ////////////////////////////////////////////////////////////
    
    std::cout << "test Token.pushValue()..." << std::endl;
    testsArePased &= test_Token_pushValue();
    
    std::cout << "test toUpperCase()..." << std::endl;
    testsArePased &= test_toUpperCase();

    std::cout << "test interpretToken()..." << std::endl;
    testsArePased &= test_interpretToken_string();

    std::cout << "test TokenVectorsAreEquiv()..." << std::endl;
    testsArePased &= Test_TokenVectorsAreEquiv();

    std::cout << "test isCorrectLiteral_char()..." << std::endl;
    testsArePased &= test_isCorrectLiteral_char();

    std::cout << "test isCorrectLiteral_string()..." << std::endl;
    testsArePased &= test_isCorrectLiteral_string();

    std::cout << "test convertStringCommandToStringVector()..." << std::endl;
    testsArePased &= test_convertStringCommandToStringVector();
    
    //////////////////////////////////////////////////////////
    ////////////////// less_than_key tests ///////////////////
    //////////////////////////////////////////////////////////
    
    std::cout << "test less_than_key operator()..." << std::endl;
    testsArePased &= test_less_than_key_operator();

    std::cout << "test compare()..." << std::endl;
    testsArePased &= test_compare();

    // std::cout << "test compare..." << std::endl;
    // testsArePased &= test_compare();

    // std::cout << "test compare..." << std::endl;
    // testsArePased &= test_compare();

    // std::cout << "test compare..." << std::endl;
    // testsArePased &= test_compare();

    // std::cout << "test compare..." << std::endl;
    // testsArePased &= test_compare();

    // std::cout << "test compare..." << std::endl;
    // testsArePased &= test_compare();




    //////////////////////////////////////////////////////////
    //////////////////// Database tests //////////////////////
    //////////////////////////////////////////////////////////
    
    
    // std::cout << "test toUpperCase..." << std::endl;
    // testsArePased &= test_DB_terminal_nextCommand();

    if(testsArePased){
        std::cout << "All tests are pased" << std::endl;
    }else{
        std::cout << BOLDRED << "tests are failed" << RESET << std::endl;
    }
    

    return testsArePased;
}
