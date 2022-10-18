#pragma once
#include <tuple>
#include <map>
#include <string>
#include <vector>

// Predeclarations
enum class Result_Code : uint8_t { Error = 0, Table = 1, TextMessage = 2, Value = 3 };

typedef std::pair<std::string, Result_Code> query_result;

/**
 * Data Base structure that contains data tables.
 * Control is provided through public interface.
 */
class DataBase
{
    class Table
    {
        // TODO
    };

    std::string buffer_name = "buff";
    std::map<std::string, Table*> tables;
    std::pair<std::string, Table*> buffer_table;

public:
    query_result select_from(const std::string& tbl, const std::string& cond);

    query_result create_join(const std::string& t1,  const std::string& t2, const std::string& cond);

    query_result insert(const std::string& t1, const std::vector<std::string>& row /*TODO : consider this solution once again :) */);

    query_result create(const std::vector<std::pair<std::string, bool>>& columns /*TODO : consider this solution once again :) */);
                
    query_result get_table_string(const std::string& name) const; 
};