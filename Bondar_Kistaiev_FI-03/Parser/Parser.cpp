#include "Parser.hpp"
#include <sstream>
#include <vector>
#include <regex>

void Parser::make_lower(std::string& str)
{
    std::transform(str.begin(), str.end(), 
                str.begin(), [](char c) { return std::tolower(c); });
}

DBCommand::Node* Parser::parse_command(const std::string& cmd)
{
    auto [tokens, valid] = process_input(cmd); // MATLAB moment
    //TODO : Build a tree, grow a house, plant a son.  
    if(valid)
    {
        DBCommand::Node* tree;
        return tree;    
    }
    else
        return nullptr; // Error-node
} 

breakdown_result Parser::process_input(const std::string& cmd)
{
    std::istringstream to_parse(cmd);
    std::string word;
    std::vector<std::string> tokens;

    while(to_parse)
    {       
        char curr = to_parse.peek();
        if (curr == ' ')
            continue;
        else if(curr == '(' || curr == ')' || curr == ',' || curr == ';')
            tokens.push_back(std::to_string(to_parse.get()));
        else if(curr == '\"')
        {
            to_parse.get();
            std::getline(to_parse, word, '\"');

            if(word.back() == ';')  // reached eof
            {
                tokens.clear();
                tokens.push_back("Expected closing \" in \"" + word + "_ <-");
                return {tokens, false};
            }
            tokens.push_back("\"" + word + "\"");
        }
        else
        {
            to_parse >> word;

            tokens.push_back(word);

            make_lower(word);

            if (word == "where")
            {
                std::getline(to_parse, word, ';');
                tokens.push_back(word);
                tokens.push_back(";");
            }
            else if(word == "on")
            {
                tokens.push_back(word);
                to_parse >> word;
                
                const std::regex on_token_regex("[a-zA-Z][a-zA-Z0-9_]*=[a-zA-Z]*[a-zA-Z0-9_]*");
                std::smatch base_match;
                if(std::regex_match(word, base_match, on_token_regex))
                {
                    size_t i = word.find("=");
                    std::string temp = word.substr(0, i + 1);
                    tokens.push_back(temp);
                    tokens.push_back("=");

                    if(i != word.size() - 1)
                        tokens.push_back(word.substr(i + 1, word.size() - i - 1));
                }
            }
        }
    }
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
    DBCommand::NodeLITERAL* t = new DBCommand::NodeLITERAL;
    t->value = error;
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
    
    if(*(++current) != "(")
        return build_ERROR_tree("Opening '(' is expected after:  " + *(current - 2) + ' ' + *(current - 1) + " _ <-");

    std::vector<std::pair<std::string, bool>> columns;

    while (true)
    {
        ++current;
        std::string temp = *current;
        bool indexed_flag = false;
        
        if (!std::regex_match(temp, base_match, token_regex))
            return build_ERROR_tree("Not a valid column name:  «" + temp + "».");
        
        columns.push_back({temp, false});
        ++current;
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
    
    if(*(++current) != "(")
        return build_ERROR_tree("Opening '(' is expected after:  " + *(current - 2) + ' ' + *(current - 1) + " _ <-");

    std::vector<std::string> row;

    const std::regex str_regex("\"(?)*\"");
    while (true)
    {
        ++current;
        std::string temp = *current;
        if (!std::regex_match(temp, base_match, str_regex))
            return build_ERROR_tree("Not a valid value:  " + temp + " <-");
            
        row.push_back(temp.substr(1, temp.size() - 2));
        ++current;

        if(*current == ",")
            continue;
        
        if(*current == ")")
            break;

        if(*current == ";")
            return build_ERROR_tree("Closing ')' is expected after:  ... " + *(tokens.end() - 2) + ' ' + *(tokens.end() - 1) + "_ <-");

        return build_ERROR_tree("Unexpected token:  " + *current);
    }

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

    if(from != "from")
        return build_ERROR_tree("Expected FROM after " + tokens.front() + " _ <-");

    ++current;

    if(tokens.size() < 4)
        return build_ERROR_tree("Incomplete SELECT FROM-command structure.");

    std::string name = *current;
    if(!std::regex_match(name, base_match, token_regex))
        return build_ERROR_tree("Not a valid table name:  " + name);

    std::string join = *current;
    make_lower(join);
    
    DBCommand::Node* from_table;

   
    if(join == "join")
    {
        std::string join_table = *(++current);
        std::string on_tbl1 = "", on_tbl2 = "";

        if(!std::regex_match(join_table, base_match, token_regex))
            return build_ERROR_tree("Not a valid table name:  " + join_table);

        std::string on = *(++current);
        make_lower(on);
        
        if (on == "on")
        {
            on_tbl1 = *(++current);
            
            if(!std::regex_match(on_tbl1, base_match, token_regex))
                return build_ERROR_tree("Not a valid table name:  " + on_tbl1);

            if (*(++current) != "=")
                return build_ERROR_tree("Expected '=' after:  " + on_tbl1 + " _ <-");

            on_tbl2 = *(++current);

            if(!std::regex_match(on_tbl1, base_match, token_regex))
                return build_ERROR_tree("Not a valid table name:  " + on_tbl2);
        }

        DBCommand::NodeJOIN* temp  = new DBCommand::NodeJOIN;
        temp->table1 = new DBCommand::NodeLITERAL;
        dynamic_cast<DBCommand::NodeLITERAL*>(temp->table1)->value = name;
        temp->table2 = new DBCommand::NodeLITERAL;
        dynamic_cast<DBCommand::NodeLITERAL*>(temp->table2)->value = join_table;
        temp->on_column1 = on_tbl1;
        temp->on_column2 = on_tbl2;
        
        from_table = temp;
    }
    else
    {
        from_table = new DBCommand::NodeLITERAL;
        dynamic_cast<DBCommand::NodeLITERAL*>(from_table)->value = name;
    }

    std::string where = *current;
    std::string cond = "";
    make_lower(where);
    
    if(where == "where")
        cond = *((++current)++);


    if(*current != ";")
        return build_ERROR_tree("Unexpected token:  " + *current);

    DBCommand::NodeSELECT* node = new DBCommand::NodeSELECT; 
    node->from_table = from_table;
    node->condition = cond;

    return node;
}