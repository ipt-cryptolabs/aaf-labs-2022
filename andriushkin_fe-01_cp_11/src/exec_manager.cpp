#include "exec_manager.hpp"

ExecManager::ExecManager() : os(std::cout), is(std::cin), running(true){};
ExecManager::ExecManager(std::ostream &os_, std::istream &is_) : os(os_), is(is_), running(true){};
ExecManager::~ExecManager(){};

std::stringstream ExecManager::FineReader()
{
    std::stringstream ret;
    size_t size = 0;
    os << ">>> ";
    char p = is.peek();
    while (p != ';')
    {
        if (p == '\n')
        {
            if (size != 0)
                os << "... ";
            else
                os << ">>> ";
        }
        else
            size += 1;
        ret << p;
        is.get();

        p = is.peek();
    }
    os << "\n";
    while (p != '\n')
    {
        p = is.get();
    }
    return ret;
}

std::vector<std::string> ExecManager::Tokenize(std::stringstream &is)
{
    std::string s;
    std::vector<std::string> out;
    char p = is.peek();
    while ((p != ';') & (p != EOF))
    {
        if (!(isalnum(p) | isspace(p) |
              p == '-' | p == ';' | p == ')' | p == '(' | p == '_' | p == ','))
            throw std::invalid_argument("Unexpected symbol in input: " + std::string(&p));
        // std::cout << "check " << p << " : " << "ispunct: " << bool(ispunct(p)) << " p != '_': " << (p !='_')
        //     << " and " << (bool(ispunct(p)) & (p !='_')) << std::endl;
        if (bool(ispunct(p)) & (p != '_') & ( p != '-'))
        {
            if (s.size() > 0)
            {
                out.push_back(s);
                s = "";
            }
            out.push_back(std::string(1,p));
        }
        else if (!isspace(p))
            s.push_back(p);
        else
        {
            if (s.size() > 0)
            {
                out.push_back(s);
                s = "";
            }
        }
        is.get();
        p = is.peek();
    }
    if (s.size() > 0)
        out.push_back(s);
    return out;
}
