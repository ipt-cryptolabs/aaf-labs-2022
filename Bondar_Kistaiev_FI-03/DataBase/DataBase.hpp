#pragma once

// Headers to use
#include <map>
#include <string>
#include <vector>

// Utility types and predeclarations
enum class Result_Code : uint8_t { Error = 0, Table = 1, TextMessage = 2 };
typedef std::pair<std::string, Result_Code> query_result;

/**
 * Data Base structure that contains data tables.
 * Control is provided through public interface.
 */
class DataBase
{   
    struct Table
    {
        Table(const std::vector<std::pair<std::string, bool>>& columns);

        int col_index(const std::string& index) const;

        std::vector<std::pair<std::string, bool>> column_info;
        std::vector<std::vector<std::string>> rows;

        std::map<std::string,                                           // Multimap has log complexity for search (+ lower_bound) and insertion operations
                 std::multimap<std::string, size_t>> indexed_cols;      // Implemeted with Dviikove Derevo (Paleno (log))   <- 190 IQ
    };

    
    std::string buff_name;
    std::map<std::string, Table*> tables;


    static void draw_krywka(std::ostream& ass, int block_count); // yes
public:
    query_result select_from(const std::string& tbl_name, std::string greater_cond, std::string less_cond);

    query_result create_join(const std::string& t1,  const std::string& t2, const std::string& on_col1, const std::string& on_col2);

    query_result insert(const std::string& tbl_name, const std::vector<std::string>& row);

    query_result create(const std::string& tbl_name, const std::vector<std::pair<std::string, bool>>& columns);
                
    query_result get_table_string(const std::string& tbl_name) const; 

    DataBase();
    ~DataBase();
};
