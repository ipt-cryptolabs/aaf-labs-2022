#include "commands.hpp"

bool CheckVarName(std::string name)
{
    return isalpha(name[0]);
}

bool CheckNum(std::string num)
{
    bool ret;
    for(auto i: num)
        ret = ret & isalnum(i);
    return ret;
}

Command::Command(){};
Command::~Command(){};
void Command::Execute(ExecManager &em){std::cout << "Placeholder for command" << std::endl;};

Exit::Exit(){};
Exit::~Exit(){};
void Exit::Execute(ExecManager &em){std::cout << "Placeholder for command exit" << std::endl;};

Create::Create(std::string name_): name(name_) {};
Create::~Create(){};
void Create::Execute(ExecManager &em)
{
    if( em.vars.emplace(name, KDtree()).second )
        std::cout << "Set " << name << " has been created" << std::endl;
    else
        std::cout << "Set " << name << " already exists" << std::endl;       
};

Insert::Insert(std::string name_, std::int64_t x_, std::int64_t y_): name(name_), x(x_), y(y_) {};
Insert::~Insert(){};
void Insert::Execute(ExecManager &em)
{
    std::map<std::string, KDtree>::iterator tree_it;
    tree_it = em.vars.find(name);
    if( tree_it != em.vars.end())
    {    
        if(tree_it->second.Insert(x,y))
            std::cout << "Inserted point (" << x << ", " << y << ") into set " << name << std::endl;
        else
            std::cout << "Point (" << x << ", " << y << ") already exists in set " << name << std::endl;

    }
    else
        std::cout << "Set " << name << " does not exists" << std::endl;
}

PrintTree::PrintTree(std::string name_): name(name_) {};
PrintTree::~PrintTree(){};
void PrintTree::Execute(ExecManager &em)
{
    std::map<std::string, KDtree>::iterator tree_it;
    tree_it = em.vars.find(name);
    if( tree_it != em.vars.end())
       tree_it->second.PrintTree();
    else
        std::cout << "Set " << name << " does not exists" << std::endl;
}

Contains::Contains(std::string name_, std::int64_t x_, std::int64_t y_): name(name_), x(x_), y(y_) {};
Contains::~Contains(){};
void Contains::Execute(ExecManager &em)
{
    std::map<std::string, KDtree>::iterator tree_it;
    tree_it = em.vars.find(name);
    if( tree_it != em.vars.end())
    {
        std::cout << "Set " << name << 
            (tree_it->second.Contains(x,y) ? "" : " not") << " contain point (" << x << ',' << y << ")" << std::endl;
    }
    else
        std::cout << "Set " << name << " does not exists" << std::endl;
}

Search::Search(std::string name_) : name(name_) {};
Search::~Search(){};
void Search::Execute(ExecManager &em)
{
    std::map<std::string, KDtree>::iterator tree_it;
    tree_it = em.vars.find(name);
    if( tree_it != em.vars.end())
    {
        std::vector<KDtree::Node*> nodes = tree_it->second.GetAll();
        if(nodes.size())
        {
            std::cout << "Set " << name << " contain points: " << std::endl;
            for(KDtree::Node* node : nodes)
                std::cout << *node << " ";
            std::cout << std::endl;
        }
        else
            std::cout << "Set " << name << " is empty" << std::endl;
    }
    else
        std::cout << "Set " << name << " does not exists" << std::endl;
}

RangeSearch::RangeSearch(std::string name_,int64_t x1_, int64_t y1_, int64_t x2_, int64_t y2_) 
    : name(name_), x1(x1_), y1(y1_), x2(x2_), y2(y2_) {};
void RangeSearch::Execute(ExecManager &em)
{
    std::map<std::string, KDtree>::iterator tree_it;
    tree_it = em.vars.find(name);
    if( tree_it != em.vars.end())
    {
        std::vector<KDtree::Node*> nodes = tree_it->second.RangeSearch(x1,y1,x2,y2);
        if(nodes.size())
        {
            std::cout << "Set " << name << " contain points in rectangle " 
                << '(' << x1 << ',' << y1 << ") (" << x2 << ',' << y2 << ')'
                << ": " << std::endl;
            for(KDtree::Node* node : nodes)
                std::cout << *node << " ";
            std::cout << std::endl;
        }
        else
            std::cout << "Set " << name << " have no points in rectangle"
            << '(' << x1 << ',' << y1 << ") (" << x2 << ',' << y2 << ')'
            << std::endl;
    }
    else
        std::cout << "Set " << name << " does not exists" << std::endl;
}

NNSearch::NNSearch(std::string name_,int64_t x_, int64_t y_) 
    : name(name_), x(x_), y(y_){};
void NNSearch::Execute(ExecManager &em)
{
    std::map<std::string, KDtree>::iterator tree_it;
    tree_it = em.vars.find(name);
    if( tree_it != em.vars.end())
    {
        std::vector<KDtree::Node*> nodes = tree_it->second.NNSearch(x, y);
        if(nodes.size())
        {
            std::cout << "Nearest neighbor to " 
            << '(' << x << ',' << y << ')'
            << " in set " << name << ": " << std::endl;
            for(KDtree::Node* node : nodes)
                std::cout << *node << " ";
            std::cout << std::endl;
        }
        else
            std::cout << "Set " << name << " is empty" << std::endl;
    }
    else
        std::cout << "Set " << name << " does not exists" << std::endl;
}

AboveSearch::AboveSearch(std::string name_, int64_t y_) : name(name_), y(y_){};
void AboveSearch::Execute(ExecManager &em)
{
    std::map<std::string, KDtree>::iterator tree_it;
    tree_it = em.vars.find(name);
    if( tree_it != em.vars.end())
    {
        std::vector<KDtree::Node*> nodes = tree_it->second.AboveSearch(y);
        if(nodes.size())
        {
            std::cout << "Points above " << y << " in set " << name << ":" << std::endl;
            for(KDtree::Node* node : nodes)
                std::cout << *node << " ";
            std::cout << std::endl;
        }
        else
            std::cout << "Set " << name << " is empty" << std::endl;
    }
    else
        std::cout << "Set " << name << " does not exists" << std::endl;
}


std::shared_ptr<Command> RecognizeComm(std::vector<std::string> tokens)
{

    if( tokens.size() == 0)
        throw std::invalid_argument("no command");
    if( tokens[0] == "CREATE")
    {
        if( !(tokens.size() == 2))
            throw std::invalid_argument("invalid count of arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        return std::make_shared<Create>(tokens[1]);
    }

    //INSERT set_name (x, y);
    else if( tokens[0] == "INSERT")
    {
        if( !(tokens.size() == 7))
            throw std::invalid_argument("invalid count of arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        if ( !(tokens[2] == "(" & tokens[4] == "," & tokens[6] == ")"))
            throw std::invalid_argument("invalid syntax");
        try
        {
            return std::make_shared<Insert>(tokens[1] ,stoi(tokens[3]), stoi(tokens[5]));
        }
        catch (std::exception& exc)
        {
            throw std::invalid_argument("invalid numbers");
        }
    }
    else if (tokens[0] == "PRINT_TREE")
    {
        if( !(tokens.size() == 2))
            throw std::invalid_argument("invalid count of arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        return std::make_shared<PrintTree>(tokens[1]);
    }
    else if( tokens[0] == "CONTAINS")
    {
        if( !(tokens.size() == 7))
            throw std::invalid_argument("invalid count of arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        if ( !(tokens[2] == "(" & tokens[4] == "," & tokens[6] == ")"))
            throw std::invalid_argument("invalid syntax");
        try
        {
            return std::make_shared<Contains>(tokens[1] ,stoi(tokens[3]), stoi(tokens[5]));
        }
        catch (std::exception& exc)
        {
            throw std::invalid_argument("invalid numbers");
        }
    }
    else if( tokens[0] == "SEARCH")
    {
        if( !CheckVarName(tokens[1]))
                throw std::invalid_argument("invalid var name");
        if(tokens.size() == 2)
        {
            return std::make_shared<Search>(tokens[1]);
        }
        else if(tokens[2] != "WHERE")
        {
            throw std::invalid_argument("invalid syntax");
        }
        else if(tokens.size() == 15 && tokens[3] == "INSIDE")
        {
            if ( !(tokens[4] == "(" && tokens[6] == "," && tokens[8] == ")"
                && tokens[9] == "," && tokens[10] == "(" && tokens[12] == "," && tokens[14] == ")"))
                throw std::invalid_argument("invalid syntax");
            try
            {
                return std::make_shared<RangeSearch>(tokens[1] ,stoi(tokens[5]), stoi(tokens[7]), stoi(tokens[11]), stoi(tokens[13]));
            }
            catch (std::exception& exc)
            {
                throw std::invalid_argument("invalid numbers");
            }
        }
        else if(tokens.size() == 9 && tokens[3] == "NN")
        {
            if ( !(tokens[4] == "(" && tokens[6] == "," && tokens[8] == ")"))
                throw std::invalid_argument("invalid syntax");
            try
            {
                return std::make_shared<NNSearch>(tokens[1] ,stoi(tokens[5]), stoi(tokens[7]));
            }
            catch (std::exception& exc)
            {
                throw std::invalid_argument("invalid numbers");
            }
        }
        else if(tokens.size() == 5 && tokens[3] == "ABOVE_TO")
        {
            try
            {
                return std::make_shared<AboveSearch>(tokens[1] ,stoi(tokens[4]));
            }
            catch (std::exception& exc)
            {
                throw std::invalid_argument("invalid numbers");
            }
        }
        else
            throw std::invalid_argument("invalid count of arguments");
        
    }
    throw std::invalid_argument("unexpected command");
}