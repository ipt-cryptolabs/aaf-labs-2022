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
    class Table
    {
    public:
        class Row;

        Table(const std::vector<std::pair<std::string, bool>>& columns);
        bool insert(const auto& r);

        // Getters
        const std::vector<Row>& get_all_rows() const;
        const std::vector<std::pair<std::string, bool>>& get_col_info() const;
        const Row& get_row(size_t ind) const;
        size_t row_size() const;
        size_t col_size() const;

        int col_index(const std::string& index) const;

        class Row
        {
        private:
            Table* owner = nullptr;
            std::vector<std::string> r;

        public:
            Row(const Row& cp, Table *new_owner = nullptr);
            Row(const std::vector<std::string>& row, Table *new_owner = nullptr);

            size_t size() const;
            std::string at(const std::string& index) const;
            const std::vector<std::string>& get_full_row() const;
        };

    private:
        std::vector<std::pair<std::string, bool>> column_info;
        std::vector<Row> rows;
    };

    std::string buff_name;
    std::map<std::string, Table*> tables;
    //std::pair<std::string, Table*> buffer_table;

public:
    query_result select_from(const std::string& tbl_name, std::string greater_cond, std::string less_cond);

    query_result create_join(const std::string& t1,  const std::string& t2, const std::string& on_col1, const std::string& on_col2);

    query_result insert(const std::string& tbl_name, const std::vector<std::string>& row);

    query_result create(const std::string& tbl_name, const std::vector<std::pair<std::string, bool>>& columns);
                
    query_result get_table_string(const std::string& tbl_name) const; 

    DataBase();
    ~DataBase();
};
