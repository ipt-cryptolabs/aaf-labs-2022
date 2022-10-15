#pragma once
#include <tuple>
#include <string>

typedef std::pair<std::string, bool> query_result;

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

public:
    query_result select_from(std::string tbl, std::string cond);

    query_result create_join(std::string t1,  std::string* t2, std::string cond);

    query_result insert(std::string t1, std::string table_row /*find a better name*/);

    query_result create(std::string columns /*find a better name*/);
};