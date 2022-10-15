#pragma once
#include <map>
#include <string>

/**
 * Data Base structure that contains data tables.
 * Control is provided through public interface.
 */
class DataBase
{
public:
    class Table
    {
        
    };


    static Table* select_from(Table* tbl, std::string cond);

    static Table* create_join(Table* t1, Table* t2, std::string cond);

    static Table* insert(Table* t1, std::string table_row /*find a better name*/ );

    static Table* create(std::string columns /*find a better name*/ );
};