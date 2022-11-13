#ifndef CHURIKOV_FI_01_PROGRAM_HPP
#define CHURIKOV_FI_01_PROGRAM_HPP

#include "Storage.hpp"


class Program {
private:
    Storage storage;
public:
    static std::string input();

    static void output(const std::string &str);

    void run();
};


#endif
