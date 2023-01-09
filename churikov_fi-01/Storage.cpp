#include "Storage.hpp"
#include <iomanip>


Storage::Storage() : tries(std::map<std::string, Trie>()) {}

std::string Storage::create(CreateRequest request) {
    std::stringstream ss;
    const std::string &trie_name = request.getTrieName();
    if (!tries.contains(trie_name)) {
        tries.insert({trie_name, Trie()});
        ss << "Trie " << trie_name << " has been created";
    } else {
        ss << "Trie " << trie_name << " already exist";
    }
    return ss.str();
}

std::string Storage::insert(InsertRequest request) {
    std::stringstream ss;
    const std::string &trie_name = request.getTrieName(), &value = request.getValue();
    if (tries.contains(trie_name)) {
        tries[trie_name].insert(value);
        ss << "String " << std::quoted(value) << " has been added to " << trie_name;
    } else {
        ss << "Trie " << trie_name << " does not exist";
    }
    return ss.str();
}

std::string Storage::print_tree(PrintTreeRequest request) {
    std::stringstream ss;
    const std::string &trie_name = request.getTrieName();
    if (tries.contains(trie_name)) {
        ss << tries[trie_name].print();
    } else {
        ss << "Trie " << trie_name << " does not exist";
    }
    return ss.str();
}

std::string Storage::contains(ContainsRequest request) {
    std::stringstream ss;
    const std::string &trie_name = request.getTrieName(), &value = request.getValue();
    if (tries.contains(trie_name)) {
        if (tries[trie_name].contains(value))
            ss << "TRUE";
        else
            ss << "FALSE";
    } else {
        ss << "Trie " << trie_name << " does not exist";
    }
    return ss.str();
}

std::string Storage::search(SearchRequest request) {
    std::stringstream ss;
    const std::string &trie_name = request.getTrieName();
    if (tries.contains(trie_name)) {
        std::vector<std::string> values = tries[trie_name].search();
        if (!values.empty()) {
            ss << std::quoted(values[0]);
            for (int i = 1; i < values.size(); ++i) {
                ss << ", " << std::quoted(values[i]);
            }
        } else {
            ss << "Strings not found";
        }
    } else {
        ss << "Trie " << trie_name << " does not exist";
    }
    return ss.str();
}

std::string Storage::execute(const std::shared_ptr<Request> &request) {
    switch (request->getCommandName()) {
        case CREATE: {
            return create(*std::static_pointer_cast<CreateRequest>(request));
        }
        case INSERT: {
            return insert(*std::static_pointer_cast<InsertRequest>(request));
        }
        case PRINT_TREE: {
            return print_tree(*std::static_pointer_cast<PrintTreeRequest>(request));
        }
        case CONTAINS: {
            return contains(*std::static_pointer_cast<ContainsRequest>(request));
        }
        case SEARCH: {
            return search(*std::static_pointer_cast<SearchRequest>(request));
        }
        default:
            return ":D";
    }
}
