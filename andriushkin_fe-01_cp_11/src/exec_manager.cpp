#include "exec_manager.hpp"

ExecManager::ExecManager():
    os(std::cout), is(std::cin), running(true) {};
ExecManager::ExecManager(std::ostream& os_, std::istream& is_):
    os(os_), is(is_), running(true) {};
ExecManager::~ExecManager(){};

bool ExecManager::IsRunning()
{
    return running;
}
/*
void ExecManager::RunLoop()
{
    std::stringstream ss;
    std::vector<std::string> tokens;
    Command comm;
    while(running)
    {
        ss = FineReader();
        tokens = Tokenize(ss);
        comm = RecognizeComm(tokens);
    }
}
*/
std::stringstream ExecManager::FineReader()
{
    std::stringstream ret;
    size_t size = 0; 
    os << ">>> ";
    char p = is.peek();
    while(p != ';')
    {
        if( p == '\n')
        {   
            if( size != 0) 
                os << "... ";
            else
                os << ">>> ";
        }   
        else
            size +=1;
        ret << p;
        is.get();
    
        p = is.peek();
    }
    os << "\n";
    while( p != '\n')
    {
        p = is.get();
    }
    return ret;
}

std::vector<std::string> ExecManager::Tokenize(std::stringstream& is)
{
    std::string s;
    std::vector<std::string> out;
    char p = is.peek();
    while((p != ';') & (p != EOF))
    {
        if( !( isalnum(p) | isspace(p) | p == ';' | p == ')' | p == '(' | p == '_' | p == ',' ))
            throw std::invalid_argument("Unexpected symbol in input: "  
                                + std::string(&p));
        //std::cout << "check " << p << " : " << "ispunct: " << bool(ispunct(p)) << " p != '_': " << (p !='_') 
        //    << " and " << (bool(ispunct(p)) & (p !='_')) << std::endl;
        if( bool(ispunct(p)) & (p !='_'))
        {
            if( s.size() > 0)
            {
                out.push_back(s);
                s = "";
            }
            out.push_back(std::string(&p));
        }
        else if (! isspace(p))
            s.push_back(p);
        else 
        {
            if( s.size() > 0)
            {
                out.push_back(s);
                s = "";
            }
        }
        is.get();
        p = is.peek();
    }
    if( s.size() > 0)
        out.push_back(s);
    return out;
}


/*
Command ExecManager::RecognizeComm(const std::vector<std::string>& tokens)
{
    if( tokens[0] == "CREATE")
    {
        if( !(tokens.size() == 2))
            throw std::invalid_argument("too much arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        return Command::CREATE;
    }

    //INSERT set_name (x, y);
    else if( tokens[0] == "INSERT")
    {
        if( !(tokens.size() == 7))
            throw std::invalid_argument("too much arguments");
        if( !CheckVarName(tokens[1]))
            throw std::invalid_argument("invalid var name");
        // todo chech if set exist
        if ( tokens[2] == "(" & tokens[4] == "," & tokens[6] == ")")
            throw std::invalid_argument("invalid ");
    } 
    throw std::invalid_argument("unexpected command");
    return Command::CREATE;
}
*/
