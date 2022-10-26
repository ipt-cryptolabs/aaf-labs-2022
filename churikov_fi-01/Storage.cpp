#include "Storage.hpp"
#include <sstream>


std::string Storage::execute(const std::shared_ptr<Request> &request) {
    std::stringstream ss;
    switch (request->getCommandName()) {
        case CREATE: {
            ss << "CREATE: "
               << std::static_pointer_cast<CreateRequest>(request)->getTrieName()
               << " trie created";
            break;
        }
        case INSERT: {
            InsertRequest ir = *std::static_pointer_cast<InsertRequest>(request);
            ss << "INSERT: "
               << ir.getValue()
               << " inserted to " << ir.getTrieName() << " trie";
            break;
        }
        case PRINT_TREE: {
            ss << "PRINT_TREE: "
               << std::static_pointer_cast<PrintTreeRequest>(request)->getTrieName()
               << " trie printed";
            break;
        }
        case CONTAINS: {
            ContainsRequest cr = *std::static_pointer_cast<ContainsRequest>(request);
            ss << "CONTAINS: "
               << cr.getValue()
               << " may be contained in " << cr.getTrieName() << " trie";
            break;
        }
        case SEARCH: {
            ss << "SEARCH: "
               << std::static_pointer_cast<SearchRequest>(request)->getTrieName()
               << " trie searched";
            break;
        }
        default:
            ss << ":D";
    }
    return ss.str();
}
