#include <iostream>
#include <sstream>
#include <string>
#include <limits>

int main()
{
    std::string input;
    std::getline(std::cin, input, ';');
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    // std::cout << std::endl << input;

    std::istringstream parse(input);
    while(parse >> input)
    {
        std::cout << input << ' ';
    }

    std::cin >> input;
}