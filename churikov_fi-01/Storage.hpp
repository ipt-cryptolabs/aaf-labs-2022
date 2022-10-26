#ifndef CHURIKOV_FI_01_STORAGE_HPP
#define CHURIKOV_FI_01_STORAGE_HPP

#include "Request.hpp"
#include <memory>


class Storage {
public:
    std::string execute(const std::shared_ptr<Request> &request);
};


#endif
