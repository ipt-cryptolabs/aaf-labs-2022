#include "Parser.hpp"
#include "..\\Node\\Node.hpp"

#include <sstream>
#include <vector>
#include <regex>

char Parser::delims[] = {'\"', ',', '(', ')', '=', ';'};

void Parser::make_lower(std::string& str)
{
    std::transform(str.begin(), str.end(), 
                str.begin(), [](char c) { return std::tolower(c); });
}

bool Parser::is_delim(char c)
{
    bool is_delim = false;
    for (char d : delims)
        is_delim = is_delim || (c == d);
        
    return is_delim;
}

bool Parser::get_token(std::istream& s, std::string& str)
{
    str.clear();
    char curr = s.get();

    while (std::isspace(curr) && s)
        curr = s.get();

    if(curr == delims[0])
    {
        std::getline(s, str, delims[0]);

        if(str.back() == ';')  // reached eof
        {
            str = "Expected closing \" in \"" + str + "_ <-";
            return false;
        }
        str = "\"" + str + "\"";
        return true;
    }

    if(is_delim(curr))
    {
        str = std::string(1, curr);
        return true;
    }

    while(true)
    {
        str.push_back(curr);
        curr = s.peek();
        if(std::isspace(curr) || is_delim(curr))
            break;

        s.get();
    }
    
    return true;
}

DBCommand::Node* Parser::parse_command(const std::string& cmd)
{
    auto [tokens, valid] = process_input(cmd); // MATLAB moment
    
    if(valid)
        return build_tree(tokens);
    else
        return build_ERROR_tree("Error:  " + tokens.front());; // Error-node
} 

breakdown_result Parser::process_input(const std::string& cmd)
{
    std::istringstream to_parse(cmd);
    std::string word;
    std::vector<std::string> tokens;

    do
    {       
        bool is_valid = get_token(to_parse, word);
        
        if(!is_valid)
        {
            tokens.clear();
            tokens.push_back(word);
            return {tokens, false};
        }

        tokens.push_back(word);

        make_lower(word);
        if (word == "where")
        {
            std::getline(to_parse, word, ';');
            tokens.push_back(word);
            tokens.push_back(";");
            break;
        }
    } while(word != ";");
    
    return {tokens, true};
}

DBCommand::Node* Parser::build_tree(const std::vector<std::string> & tokens)
{
    std::string first = tokens.front();
    make_lower(first);
                
    if (first == "create")
    {
        return build_CREATE_tree(tokens);
    }
    else if (first == "insert")
    {
        return build_INSERT_tree(tokens);
    }
    else if (first == "select")
    {
        return build_SELECT_tree(tokens);
    }
    else
    {
        return build_ERROR_tree("Unknown command:  " + tokens.front());
    }
}

DBCommand::Node* Parser::build_ERROR_tree(const std::string & error)
{
    DBCommand::NodeVALUE* t = new DBCommand::NodeVALUE;
    t->value = error;
    t->type = Result_Code(0);
    return t;
}

DBCommand::Node* Parser::build_CREATE_tree(const std::vector<std::string> & tokens)
{
    const std::regex token_regex("[a-zA-Z][a-zA-Z0-9_]*");
    std::smatch base_match;

    auto current = tokens.begin() + 1;

    if(tokens.size() < 6)
        return build_ERROR_tree("Incomplete CREATE-command structure.");

    std::string name = *current;
    if(!std::regex_match(name, base_match, token_regex))
        return build_ERROR_tree("Not a valid table name:  " + name);
    ++current;
    
    if(*current != "(")
        return build_ERROR_tree("Opening '(' is expected after:  " + *(current - 2) + ' ' + *(current - 1) + " _ <-");

    std::vector<std::pair<std::string, bool>> columns;

    while (true)
    {
        ++current;
        std::string temp = *current;
        if (!std::regex_match(temp, base_match, token_regex))
            return build_ERROR_tree("Not a valid column name:  «" + temp + "».");
        ++current;

        columns.push_back({temp, false});
        
        temp = *current;
        make_lower(temp);

        if(temp == "indexed")
        {
            columns.back().second = true;
            ++current;
        }

        if(*current == ",")
            continue;
        
        if(*current == ")")
            break;

        if(*current == ";")
            return build_ERROR_tree("Closing ')' is expected after:  ... " + *(tokens.end() - 2) + ' ' + *(tokens.end() - 1) + "_ <-");

        return build_ERROR_tree("Unexpected token:  " + *current);
    }
    ++current;

    if(*current != ";")
        return build_ERROR_tree("Unexpected token:  " + *current);
    ++current;

    if(current != tokens.end())
        return build_ERROR_tree("Found unexpected token  " + *current + "  after expression end (parse error).");

    DBCommand::NodeCREATE* node = new DBCommand::NodeCREATE; 
    node->table_name = name;
    node->columns = columns;

    return node;
}

DBCommand::Node* Parser::build_INSERT_tree(const std::vector<std::string> & tokens)
{
    const std::regex token_regex("[a-zA-Z][a-zA-Z0-9_]*");
    std::smatch base_match;

    auto current = tokens.begin() + 1;

    std::string into = *current;
    make_lower(into);

    if(into == "into")
        ++current;

    if(tokens.size() < 6)
        return build_ERROR_tree("Incomplete INSERT-command structure.");

    std::string name = *current;
    if(!std::regex_match(name, base_match, token_regex))
        return build_ERROR_tree("Not a valid table name:  " + name);
    ++current;

    if(*current != "(")
        return build_ERROR_tree("Opening '(' is expected after:  " + *(current - 2) + ' ' + *(current - 1) + " _ <-");

    std::vector<std::string> row;

    const std::regex str_regex("\"(.*?)\"");
    while (true)
    {
        ++current;

        std::string temp = *current;
        if (!std::regex_match(temp, base_match, str_regex))
            return build_ERROR_tree("Not a valid value:  " + temp + " <-");
        ++current;

        row.push_back(temp.substr(1, temp.size() - 2));

        if(*current == ",")
            continue;
        
        if(*current == ")")
            break;

        if(*current == ";")
            return build_ERROR_tree("Closing ')' is expected after:  ... " + *(tokens.end() - 2) + ' ' + *(tokens.end() - 1) + "_ <-");

        return build_ERROR_tree("Unexpected token:  " + *current);
    }
    ++current;

    if(*current != ";")
        return build_ERROR_tree("Unexpected token:  " + *current);
    ++current;

    if(current != tokens.end())
        return build_ERROR_tree("Found unexpected token  " + *current + "  after expression end (parse error).");

    DBCommand::NodeINSERT* node = new DBCommand::NodeINSERT; 
    node->table = name;
    node->row = row;

    return node;
}

DBCommand::Node* Parser::build_SELECT_tree(const std::vector<std::string> & tokens)
{
    const std::regex token_regex("[a-zA-Z][a-zA-Z0-9_]*");
    std::smatch base_match;

    auto current = tokens.begin() + 1;

    std::string from = *current;
    make_lower(from);
    ++current;

    if(from != "from")
        return build_ERROR_tree("Expected FROM after " + tokens.front() + " _ <-");

    if(tokens.size() < 4)
        return build_ERROR_tree("Incomplete SELECT FROM-command structure.");

    std::string name = *current;
    if(!std::regex_match(name, base_match, token_regex))
        return build_ERROR_tree("Not a valid table name:  " + name);
    ++current;

    std::string join = *current;
    make_lower(join);
    
    DBCommand::Node* from_table;

    if(join == "join")
    {
        ++current;

        std::string join_table = *current;
        if(!std::regex_match(join_table, base_match, token_regex))
            return build_ERROR_tree("Not a valid table name:  " + join_table);
        ++current;

        std::string on = *current;
        make_lower(on);
        
        std::string on_tbl1 = "", on_tbl2 = "";
        if (on == "on")
        {
            ++current;

            on_tbl1 = *current;
            if(!std::regex_match(on_tbl1, base_match, token_regex))
                return build_ERROR_tree("Not a valid table name:  " + on_tbl1);
            ++current;

            if(*current != "=")
                return build_ERROR_tree("Expected '=' after:  " + on_tbl1 + " _ <-");
            ++current;

            on_tbl2 = *current;
            if(!std::regex_match(on_tbl1, base_match, token_regex))
                return build_ERROR_tree("Not a valid table name:  " + on_tbl2);
            ++current;
        }

        DBCommand::NodeJOIN* temp  = new DBCommand::NodeJOIN;
        temp->table1 = new DBCommand::NodeVALUE;
        dynamic_cast<DBCommand::NodeVALUE*>(temp->table1)->value = name;
        dynamic_cast<DBCommand::NodeVALUE*>(temp->table1)->type = Result_Code(1);
        temp->table2 = new DBCommand::NodeVALUE;
        dynamic_cast<DBCommand::NodeVALUE*>(temp->table2)->value = join_table;
        dynamic_cast<DBCommand::NodeVALUE*>(temp->table2)->type = Result_Code(1);
        temp->on_column1 = on_tbl1;
        temp->on_column2 = on_tbl2;
        
        from_table = temp;
    }
    else
    {
        from_table = new DBCommand::NodeVALUE;
        dynamic_cast<DBCommand::NodeVALUE*>(from_table)->value = name;
        dynamic_cast<DBCommand::NodeVALUE*>(from_table)->type = Result_Code(1);
    }

    std::string where = *current;
    make_lower(where);
    
    std::string cond = "";
    if(where == "where")
    {
        ++current;
        cond = *current;
        ++current;
    }

    if(*current != ";")
        return build_ERROR_tree("Unexpected token:  " + *current);
    ++current;

    if(current != tokens.end())
        return build_ERROR_tree("Found unexpected token  " + *current + "  after expression end (parse error).");

    DBCommand::NodeSELECT* node = new DBCommand::NodeSELECT; 
    node->from_table = from_table;
    node->condition = cond;

    return node;
}
