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

bool test_interpretToken(){
    bool testsArePased = true;
    std::string rez = "";
    Token t;
    Interpreter i;

    t.setValue("CREATE");
    i.interpretToken(t);
    rez = t.getType();
    testsArePased &= testStringsEquiw(rez, _COMMAND_TOKEN_);
    
    t.setValue("create");
    i.interpretToken(t);
    rez = t.getType();
    testsArePased &= testStringsEquiw(rez, _COMMAND_TOKEN_);

    t.setValue("ORDER_BY");
    i.interpretToken(t);
    rez = t.getType();
    testsArePased &= testStringsEquiw(rez, _COMMAND_TOKEN_);

    t.setValue("\"dsfGsdaf\"");
    i.interpretToken(t);
    rez = t.getType();
    testsArePased &= testStringsEquiw(rez, _VALUE_TOKEN_);

    t.setValue("dsfGsdaf");
    i.interpretToken(t);
    rez = t.getType();
    testsArePased &= testStringsEquiw(rez, _NAME_TOKEN_);

    try{
        t.setValue("\"\"");
        i.interpretToken(t);
    }catch(char const* e){
        rez = t.getType();
        testsArePased &= testStringsEquiw(rez, _UNDEFINED_TOKEN_);
    }

    try{
        t.setValue("\"hkjafhsd78sdf\"");
        i.interpretToken(t);
    }catch(char const* e){
        rez = t.getType();
        testsArePased &= testStringsEquiw(rez, _UNDEFINED_TOKEN_);
    }

    try{
        t.setValue("\"hsdfkhkjhafs");
        i.interpretToken(t);
    }catch(char const* e){
        rez = t.getType();
        testsArePased &= testStringsEquiw(rez, _UNDEFINED_TOKEN_);
    }
    
    return testsArePased;
}

bool test_interpretCommand(){
    bool testsArePased = true;
    std::vector<Token> rez, answ;
    Interpreter i;

    rez = i.interpretCommand("CREATE students (name, group);");
    answ = {Token(_COMMAND_TOKEN_, "CREATE"),
            Token(_NAME_TOKEN_, "students"), 
            Token(_OPEN_BRACKET_TOKEN_, "("),
            Token(_NAME_TOKEN_, "name"),
            Token(_NAME_TOKEN_, "group"),
            Token(_CLOSE_BRACKET_TOKEN_, ")"),
            Token(_EOC_TOKEN_, ";"),
            };
    testsArePased &= TokenVectorsAreEquiv(rez, answ);



    if(!testsArePased){
        std::cerr << "interpretCommand is wrong" << std::endl;
    }
    
    return testsArePased;
}

bool test_2(){
    bool testsArePased = true;
    
    return testsArePased;
}

bool test_3(){
    bool testsArePased = true;
    
    return testsArePased;
}

bool test_4(){
    bool testsArePased = true;
    
    return testsArePased;
}





bool testAll(){
    bool testsArePased = true; 

    std::cout << "test Token.pushValue()..." << std::endl;
    testsArePased &= test_Token_pushValue();
    
    std::cout << "test toUpperCase()..." << std::endl;
    testsArePased &= test_toUpperCase();

    std::cout << "test interpretToken()..." << std::endl;
    testsArePased &= test_interpretToken();

    std::cout << "test TokenVectorsAreEquiv()..." << std::endl;
    testsArePased &= Test_TokenVectorsAreEquiv();

    std::cout << "test interpretCommand()..." << std::endl;
    testsArePased &= test_interpretCommand();


    
    
    // std::cout << "test toUpperCase..." << std::endl;
    // testsArePased &= test_DB_terminal_nextCommand();


    std::cout << "All tests are pased" << std::endl;

    return testsArePased;
}
