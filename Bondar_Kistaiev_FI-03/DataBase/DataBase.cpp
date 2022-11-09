#include "DataBase.hpp"
#include <sstream>
#include <iomanip>

const size_t MAX_CELL_WIDTH = 15;


DataBase::DataBase() : buff_name{"__buff"}
{
    tables[buff_name] = nullptr;
}

DataBase::~DataBase()
{
    for(auto [name, table] : tables)
        if(table)
            delete table;
}

query_result DataBase::select_from(const std::string& tbl_name, std::string greater_cond, std::string less_cond)
{
    // Vyba4te 3a KoD
    if(!tables.contains(tbl_name))
        return {"Table " + tbl_name + " does not exist.", Result_Code::Error};

    const Table* table = tables.at(tbl_name);

    if(greater_cond == ""  && less_cond == "")
        return {tbl_name, Result_Code::Table};

    if(greater_cond.at(0) == '"' && less_cond.at(0) == '"')
    {
        if(greater_cond.substr(1, greater_cond.size() - 2) > less_cond.substr(1, less_cond.size() - 2))
        {
            return {tbl_name, Result_Code::Table};
        }
        else
        {
            Table* temp = tables.at(buff_name);
            tables.at(buff_name) = new Table(table->get_col_info());
            if(temp)
                delete temp;
                
            return {buff_name, Result_Code::Table};
        }
    }
    else if(greater_cond.at(0) == '"' && less_cond.at(0) != '"')
    {
        int l_index = table->col_index(less_cond);
        if(l_index == -1)
            return {"Column " + less_cond + " does not exist in table " + tbl_name + ".", Result_Code::Error};

        Table* temp = new Table(table->get_col_info());
        for(const auto& r : table->get_all_rows())
        {
            if(greater_cond.substr(1, greater_cond.size() - 2) > r.get_full_row().at(l_index))
                temp->insert(r);
        }

        if(tables.at(buff_name))
            delete tables.at(buff_name);
            
        tables.at(buff_name) = temp;
    }
    else if(greater_cond.at(0) != '"' && less_cond.at(0) == '"')
    {
        int g_index = table->col_index(greater_cond);
        if(g_index == -1)
            return {"Column " + greater_cond + " does not exist in table " + tbl_name + ".", Result_Code::Error};

        Table* temp = new Table(table->get_col_info());
        for(const auto& r : table->get_all_rows())
        {
            if(r.get_full_row().at(g_index) > less_cond.substr(1, less_cond.size() - 2))
                temp->insert(r);
        }

        if(tables.at(buff_name))
            delete tables.at(buff_name);
            
        tables.at(buff_name) = temp;
    }
    else
    {
        int g_index = table->col_index(greater_cond);
        int l_index = table->col_index(less_cond);
        if(g_index == -1)
            return {"Column " + greater_cond + " does not exist in table " + tbl_name + ".", Result_Code::Error};

        if(l_index == -1)
            return {"Column " + less_cond + " does not exist in table " + tbl_name + ".", Result_Code::Error};
            

        Table* temp = new Table(table->get_col_info());
        for(const auto& r : table->get_all_rows())
        {
            if(r.get_full_row().at(g_index) > r.get_full_row().at(l_index))
                temp->insert(r);
        }

        if(tables.at(buff_name))
            delete tables.at(buff_name);
            
        tables.at(buff_name) = temp;
    }

    return {buff_name, Result_Code::Table};
}

query_result DataBase::create_join(const std::string& t1,  const std::string& t2, const std::string& on_col1, const std::string& on_col2)
{
    return {"JOIN RESULT: " + t1 + " x " + t2 + " ON " + on_col1 + " = " + on_col2, Result_Code::Table};
}

query_result DataBase::insert(const std::string& tbl_name, const std::vector<std::string>& row)
{
    if(!tables.contains(tbl_name))
        return {"Table " + tbl_name + " does not exists.", Result_Code::Error};

    bool success = tables.at(tbl_name)->insert(row);
    
    if(!success)
        return {"Inserted row's size does not match " + tbl_name + "'s row-size.", Result_Code::Error};
    
    return {tbl_name, Result_Code::Table};      // Switch to TextMessage
}

query_result DataBase::create(const std::string& tbl_name, const std::vector<std::pair<std::string, bool>>& columns)
{
    if(tables.contains(tbl_name))
        return {"Table " + tbl_name + " already exists.", Result_Code::Error};

    tables[tbl_name] = new Table(columns);

    return {tbl_name, Result_Code::Table};      // Switch to TextMessage
}
                
query_result DataBase::get_table_string(const std::string& tbl_name) const
{
    if(!tables.contains(tbl_name))
        return {"Table " + tbl_name + " does not exist.", Result_Code::Error};

    const Table* tb = tables.at(tbl_name);

    std::ostringstream to_print;
    
    to_print << std::left;
    to_print << '|';
    for(const auto& c : tb->get_col_info())
    {
        to_print << "   " << std::setw(MAX_CELL_WIDTH + 5) << c.first.substr(0, MAX_CELL_WIDTH) + (c.second ? " (I)" : "") << '|';
    }
    to_print << std::endl;

    for(size_t i = 0; i < tb->row_size(); ++i)
    {
        to_print << '|';
        for(const auto& v : tb->get_row(i).get_full_row())
        {
            to_print << "  \"" << std::setw(MAX_CELL_WIDTH + 5) 
                << (v.size() < MAX_CELL_WIDTH ? v : (v.substr(0, MAX_CELL_WIDTH - 3) + "...")) + "\"" << '|';
        }
        to_print << std::endl; 
    }

    return {to_print.str(), Result_Code::Table};
}

size_t DataBase::Table::row_size() const
{
    return this->rows.size();
}

size_t DataBase::Table::col_size() const
{
    return this->column_info.size();
}

const DataBase::Table::Row& DataBase::Table::get_row(size_t ind) const
{
    return this->rows[ind];
}

DataBase::Table::Table(const std::vector<std::pair<std::string, bool>>& columns)
{
    // TODO : ADD indexing

    column_info = columns;
    // Some indexing logic
}

const std::vector<std::pair<std::string, bool>>& DataBase::Table::get_col_info() const
{
    return this->column_info;
}

bool DataBase::Table::insert(const auto& r)
{
    if(r.size() != col_size())
        return false;               // Incomplete or bad row

    this->rows.emplace_back(r, this);
    return true;
}

int DataBase::Table::col_index(const std::string& index) const
{
    int r = 0;
    for (const auto& c : this->column_info)
    {
        if (index == c.first)
            return r;

        ++r;
    }
    
    return -1;
}

const std::vector<DataBase::Table::Row>& DataBase::Table::get_all_rows() const
{
    return this->rows;
}

DataBase::Table::Row::Row(const Row& cp, Table *new_owner) : r{cp.r}, owner{new_owner} {}

DataBase::Table::Row::Row(const std::vector<std::string>& row, Table *new_owner) : r{row}, owner{new_owner} {}

std::string DataBase::Table::Row::at(const std::string& index) const
{
    return r.at(this->owner->col_index(index));
}

size_t DataBase::Table::Row::size() const
{
    return r.size();
}

const std::vector<std::string>& DataBase::Table::Row::get_full_row() const
{
    return this->r;
}