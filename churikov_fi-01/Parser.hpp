#ifndef CHURIKOV_FI_01_PARSER_HPP
#define CHURIKOV_FI_01_PARSER_HPP

#include "Request.hpp"
#include <memory>


enum ParsingResultType {
    SUCCESS, ERROR, EXIT
};

class ParsingResult {
public:
    virtual ParsingResultType getResultType() { return EXIT; };
};

class SuccessParsingResult : public ParsingResult {
private:
    std::shared_ptr<Request> request;
public:
    explicit SuccessParsingResult(std::shared_ptr<Request> request) : request(std::move(request)) {}

    ParsingResultType getResultType() override { return SUCCESS; }

    std::shared_ptr<Request> getRequest() { return request; }
};

class ErrorParsingResult : public ParsingResult {
private:
    std::string description;
public:
    explicit ErrorParsingResult(std::string description) : description(std::move(description)) {}

    ParsingResultType getResultType() override { return ERROR; }

    std::string getDescription() { return description; }
};

class Parser {
public:
    static std::shared_ptr<ParsingResult> parse(const std::string &str);
};


#endif
