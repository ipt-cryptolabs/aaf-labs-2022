#ifndef CHURIKOV_FI_01_STORAGE_HPP
#define CHURIKOV_FI_01_STORAGE_HPP

#include "Request.hpp"
#include "Trie.hpp"
#include <memory>
#include <map>


class Storage {
private:
    std::map<std::string, Trie> tries;

    void create(CreateRequest request, std::stringstream &ss);

    void insert(InsertRequest request, std::stringstream &ss);

    void print_tree(PrintTreeRequest request, std::stringstream &ss);

    void contains(ContainsRequest request, std::stringstream &ss);

    void search(SearchRequest request, std::stringstream &ss);

public:
    Storage();

    std::string execute(const std::shared_ptr<Request> &request);
};


#endif
