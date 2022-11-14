#include "CLI.h"


void CLI::Run() {
    Info();

    while(true){
        std::string input;
        std::string res_input;

        while(true){
            if(res_input.empty()){
                std::cout << "> ";
            }
            else{
                std::cout << "... ";
            }

            std::getline(std::cin, input);
            input += '\n';

            auto it = input.find(';');
            if(it != std::string::npos){
                res_input += std::string(input.begin(), input.begin() + it + 1);
                break;
            }
            res_input += input;
        }

        try{
            Lexer lexer(res_input);
            Parser parser(&lexer);
            Interpreter interpreter(&parser, new DBImpl());

            interpreter.Interpret();
        }
        catch (Exception& exception){
            std::cout<< exception.what() << std::endl;
        }
    }
}

void CLI::Info() {
    std::cout << "---\tDB based on R-Tree\t---\n\n";
}
