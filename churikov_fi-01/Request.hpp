#ifndef CHURIKOV_FI_01_REQUEST_HPP
#define CHURIKOV_FI_01_REQUEST_HPP

#include <string>


enum CommandName {
    CREATE, INSERT, PRINT_TREE, CONTAINS, SEARCH
};

class Request {
public:
    virtual CommandName getCommandName() = 0;
};

class CreateRequest : public Request {
private:
    std::string trie_name;
public:
    explicit CreateRequest(std::string trie_name) : Request(), trie_name(std::move(trie_name)) {}

    CommandName getCommandName() override { return CREATE; }

    std::string getTrieName() { return trie_name; }
};

class InsertRequest : public Request {
private:
    std::string trie_name, value;
public:
    explicit InsertRequest(std::string trie_name, std::string value)
            : Request(), trie_name(std::move(trie_name)), value(std::move(value)) {}

    CommandName getCommandName() override { return INSERT; }

    std::string getTrieName() { return trie_name; }

    std::string getValue() { return value; }
};

class PrintTreeRequest : public Request {
private:
    std::string trie_name;
public:
    explicit PrintTreeRequest(std::string trie_name) : Request(), trie_name(std::move(trie_name)) {}

    CommandName getCommandName() override { return PRINT_TREE; }

    std::string getTrieName() { return trie_name; }
};

class ContainsRequest : public Request {
private:
    std::string trie_name, value;
public:
    explicit ContainsRequest(std::string trie_name, std::string value)
            : Request(), trie_name(std::move(trie_name)), value(std::move(value)) {}

    CommandName getCommandName() override { return CONTAINS; }

    std::string getTrieName() { return trie_name; }

    std::string getValue() { return value; }
};

class SearchRequest : public Request {
private:
    std::string trie_name;
public:
    explicit SearchRequest(std::string trie_name) : Request(), trie_name(std::move(trie_name)) {}

    CommandName getCommandName() override { return SEARCH; }

    std::string getTrieName() { return trie_name; }
};

#endif
