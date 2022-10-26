#include "Parser.hpp"
#include <regex>


std::shared_ptr<ParsingResult> Parser::parse(const std::string &str) {
    std::smatch match;
    if (std::regex_search(str, match, std::regex(R"(^\s*EXIT\s*;$)", std::regex_constants::icase))) {
        return std::make_shared<ParsingResult>();
    }
    if (std::regex_search(str, match,
                          std::regex(R"(^\s*CREATE\s+([a-zA-Z][a-zA-Z0-9_]*)\s*;$)", std::regex_constants::icase))) {
        return std::make_shared<SuccessParsingResult>(std::make_shared<CreateRequest>(match.str(1)));
    }
    if (std::regex_search(str, match, std::regex(R"f(^\s*INSERT\s+([a-zA-Z][a-zA-Z0-9_]*)\s+"(.*)"\s*;$)f",
                                                 std::regex_constants::icase))) {
        return std::make_shared<SuccessParsingResult>(std::make_shared<InsertRequest>(match.str(1), match.str(2)));
    }
    if (std::regex_search(str, match, std::regex(R"(^\s*PRINT_TREE\s+([a-zA-Z][a-zA-Z0-9_]*)\s*;$)",
                                                 std::regex_constants::icase))) {
        return std::make_shared<SuccessParsingResult>(std::make_shared<PrintTreeRequest>(match.str(1)));
    }
    if (std::regex_search(str, match, std::regex(R"f(^\s*CONTAINS\s+([a-zA-Z][a-zA-Z0-9_]*)\s+"(.*)"\s*;$)f",
                                                 std::regex_constants::icase))) {
        return std::make_shared<SuccessParsingResult>(std::make_shared<ContainsRequest>(match.str(1), match.str(2)));
    }
    if (std::regex_search(str, match,
                          std::regex(R"(^\s*SEARCH\s+([a-zA-Z][a-zA-Z0-9_]*)\s*;$)", std::regex_constants::icase))) {
        return std::make_shared<SuccessParsingResult>(std::make_shared<SearchRequest>(match.str(1)));
    }
    return std::make_shared<ErrorParsingResult>("Syntax error");
}
