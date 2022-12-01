#include "Parser.h"
#include "Tree.h"

int main()
{
    Parser p;
    for (std::string line; std::getline(std::cin, line, ';');)
    {
        if(!p.insert(line))
            return 0;
    }
    return 0;
}
