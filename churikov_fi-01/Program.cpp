#include "Program.hpp"
#include "Parser.hpp"
#include <iostream>
#include <sstream>


std::string Program::input() {
    std::stringstream ss;
    std::string buff;
    std::string::size_type pos;
    std::cout << ">";
    std::getline(std::cin, buff);
    while ((pos = buff.find(';')) == std::string::npos) {
        ss << buff << std::endl;
        std::cout << "...";
        std::getline(std::cin, buff);
    }
    ss << buff.substr(0, pos) << ';';
    return ss.str();
}

void Program::output(const std::string &str) {
    std::cout << str << std::endl;
}

void Program::run() {
    std::string inp{};
    while (true) {
        inp = input();
        std::shared_ptr<ParsingResult> parsingResult = Parser::parse(inp);
        switch (parsingResult->getResultType()) {
            case SUCCESS:
                output(storage.execute(std::static_pointer_cast<SuccessParsingResult>(parsingResult)->getRequest()));
                break;
            case ERROR:
                output(std::static_pointer_cast<ErrorParsingResult>(parsingResult)->getDescription());
                break;
            case EXIT:
                output("Program stopped successfully");
                return;
        }
    }
}
