#ifndef CHURIKOV_FI_01_STORAGE_HPP
#define CHURIKOV_FI_01_STORAGE_HPP

#include "Request.hpp"
#include "Trie.hpp"
#include <memory>


class Storage {
private:
    std::map<std::string, Trie> tries;
public:
    Storage();

    std::string create(CreateRequest request);

    std::string insert(InsertRequest request);

    std::string print_tree(PrintTreeRequest request);

    std::string contains(ContainsRequest request);

    std::string search(SearchRequest request);

    std::string execute(const std::shared_ptr<Request> &request);
};


#endif
