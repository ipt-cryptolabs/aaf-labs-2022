#include "DataBase.hpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <set>

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

    if(greater_cond.at(0) == '"' && less_cond.at(0) == '"')        // Comparing two literals
    {
        if(greater_cond.substr(1, greater_cond.size() - 2) > less_cond.substr(1, less_cond.size() - 2))
        {
            return {tbl_name, Result_Code::Table};
        }
        else
        {
            Table* temp = tables.at(buff_name);
            tables.at(buff_name) = new Table(table->column_info);
            if(temp)
                delete temp;
                
            return {buff_name, Result_Code::Table};
        }
    }
    else if(greater_cond.at(0) == '"' && less_cond.at(0) != '"')   // [col] < Literal
    {
        int l_index = table->col_index(less_cond);
        if(l_index == -1)
            return {"Column " + less_cond + " does not exist in table " + tbl_name + ".", Result_Code::Error};

        Table* temp = new Table(table->column_info);
        greater_cond = greater_cond.substr(1, greater_cond.size() - 2);

        if(table->column_info.at(l_index).second)   // Check whether col is indexed
        {
            const auto& treee = table->indexed_cols.at(less_cond);
            auto mobil = treee.begin();
            const auto range_end = treee.lower_bound(greater_cond);

            while(mobil != range_end)
            {
                temp->rows.push_back(table->rows.at((*mobil).second));
                ++mobil;
            }
        }
        else
        {
            for(const auto& r : table->rows)
            {
                if(greater_cond > r.at(l_index))
                    temp->rows.push_back(r);
            }
        }
            
        if(tables.at(buff_name))
            delete tables.at(buff_name);
        tables.at(buff_name) = temp;
    }
    else if(greater_cond.at(0) != '"' && less_cond.at(0) == '"')   // Literal < [col]
    {
        int g_index = table->col_index(greater_cond);
        if(g_index == -1)
            return {"Column " + greater_cond + " does not exist in table " + tbl_name + ".", Result_Code::Error};

        Table* temp = new Table(table->column_info);
        less_cond = less_cond.substr(1, less_cond.size() - 2);

        if(table->column_info.at(g_index).second)   // Check whether col is indexed
        {
            const auto& treee = table->indexed_cols.at(greater_cond);
            auto mobil = treee.upper_bound(less_cond);
            auto mobil_1 = treee.lower_bound(less_cond);
            const auto range_end = treee.end();

            while(mobil != range_end)
            {
                temp->rows.push_back(table->rows.at((*mobil).second));
                ++mobil;
            }
        }
        else
        {
            for(const auto& r : table->rows)
            {
                if(r.at(g_index) > less_cond)
                    temp->rows.push_back(r);
            }
        }

        if(tables.at(buff_name))
            delete tables.at(buff_name);
        tables.at(buff_name) = temp;
    }
    else                                                           // [col] < [col]
    {
        int g_index = table->col_index(greater_cond);
        int l_index = table->col_index(less_cond);
        if(g_index == -1)
            return {"Column " + greater_cond + " does not exist in table " + tbl_name + ".", Result_Code::Error};

        if(l_index == -1)
            return {"Column " + less_cond + " does not exist in table " + tbl_name + ".", Result_Code::Error};
        
        Table* temp = new Table(table->column_info);

        for(const auto& r : table->rows)
        {
            if(r.at(g_index) > r.at(l_index))
                temp->rows.push_back(r);
        }

        if(tables.at(buff_name))
            delete tables.at(buff_name);
        tables.at(buff_name) = temp;
    }

    return {buff_name, Result_Code::Table};
}

query_result DataBase::create_join(const std::string& t1,  const std::string& t2, const std::string& on_col1, const std::string& on_col2)
{
    if(!tables.contains(t1))
        return {"Table " + t1 + " does not exist.", Result_Code::Error};
    if(!tables.contains(t2))
        return {"Table " + t2 + " does not exist.", Result_Code::Error};
        
    Table* table1 = tables.at(t1);
    Table* table2 = tables.at(t2);

    // Create table header
    std::vector<std::pair<std::string, bool>> new_col_info = table1->column_info;
    std::transform(table2->column_info.begin(), table2->column_info.end(), std::back_inserter(new_col_info), [&](const auto& c_i)
    {
        auto same_pos = std::find_if(new_col_info.begin(), new_col_info.end(), [&c_i](const auto& c_j)
        {
            return c_i.first == c_j.first;
        });

        std::pair<std::string, bool> to_cerf = {c_i.first, false};
        if(same_pos != new_col_info.end())
        {
            (*same_pos).first = (*same_pos).first + "_" + t1;
            to_cerf.first = to_cerf.first + "_" + t2;
        }

        return to_cerf;
    });

    Table* result = new Table(new_col_info);

    if(on_col1 == ""  && on_col2 == "")
    {
        std::vector<std::string> to_add;    
        for(const auto& row_l : table1->rows)
        {
            for(const auto& row_r : table2->rows)
            {
                to_add = row_l;
                to_add.insert(to_add.end(), row_r.begin(), row_r.end());
                result->rows.push_back(to_add);
            }
        }

        if(tables.at(buff_name))
            delete tables.at(buff_name);
        tables.at(buff_name) = result;

        return {buff_name, Result_Code::Table};
    }
    else
    {
        int col1_idx = table1->col_index(on_col1);
        int col2_idx = table2->col_index(on_col2);

        if(col1_idx == -1)
            return {"Column " + on_col1 + " does not exist in table " + t1 + ".", Result_Code::Error};
        if(col2_idx == -1)
            return {"Column " + on_col2 + " does not exist in table " + t2 + ".", Result_Code::Error};

        // TODO : Indexing condition flowchange

        std::vector<std::string> to_add;
        for(const auto& row_l : table1->rows)
        {
            for(const auto& row_r : table2->rows)
            {
                if(row_l.at(col1_idx) == row_r.at(col2_idx))
                {
                    to_add = row_l;
                    to_add.insert(to_add.end(), row_r.begin(), row_r.end());
                    result->rows.push_back(to_add);
                }
            }
        }
    }

    if(tables.at(buff_name))
        delete tables.at(buff_name);
    tables.at(buff_name) = result;

    return {buff_name, Result_Code::Table};
}

query_result DataBase::insert(const std::string& tbl_name, const std::vector<std::string>& row)
{
    // Errors
    if(!tables.contains(tbl_name))
        return {"Table " + tbl_name + " does not exists.", Result_Code::Error};
    
    if(tables.at(tbl_name)->column_info.size() != row.size())
        return {"Inserted row's size does not match " + tbl_name + "'s row-size.", Result_Code::Error};
    //

    // Logic (musician)
    auto* t = tables.at(tbl_name);

    t->rows.push_back(row);
    for (size_t i = 0; i < row.size(); ++i)
    {
        const auto& [col, indexed] =  t->column_info.at(i);
        
        if(indexed)
            t->indexed_cols.at(col).insert({row.at(i), t->rows.size() - 1});
    }
    
    return {"1 row inserted into table: " + tbl_name, Result_Code::TextMessage};      // Switch to TextMessage
}

query_result DataBase::create(const std::string& tbl_name, const std::vector<std::pair<std::string, bool>>& columns)
{
    if(tables.contains(tbl_name))
        return {"Table " + tbl_name + " already exists.", Result_Code::Error};

    std::set<std::string> a;
    for(const auto& c : columns)
        a.insert(c.first);

    if(a.size() != columns.size())
        return {"Table cannot have multiple columns with same name.", Result_Code::Error};
        
    tables[tbl_name] = new Table(columns);

    return {"Created table:  " + tbl_name, Result_Code::TextMessage};
}
                
void DataBase::draw_krywka(std::ostream& ass, int block_count)
{
    ass << '+' << std::setfill('-');
    for(int i = 0; i < block_count; ++i)
    {
        ass << std::setw(MAX_CELL_WIDTH + 8) << "" << '+';
    }
    ass << std::endl << std::setfill(' ');
}

query_result DataBase::get_table_string(const std::string& tbl_name) const
{
    if(!tables.contains(tbl_name))
        return {"Table " + tbl_name + " does not exist.", Result_Code::Error};

    const Table* tb = tables.at(tbl_name);

    std::ostringstream to_print;
    
    to_print << std::left;
    draw_krywka(to_print, tb->column_info.size());
    to_print << '|';
    for(const auto& c : tb->column_info)
    {
        to_print << "   " << std::setw(MAX_CELL_WIDTH + 5) << c.first.substr(0, MAX_CELL_WIDTH) + (c.second ? " (I)" : "") << '|';
    }
    to_print << std::endl;

    draw_krywka(to_print, tb->column_info.size());

    for(size_t i = 0; i < tb->rows.size(); ++i)
    {
        to_print << '|';
        for(const auto& v : tb->rows.at(i))
        {
            to_print << "  \"" << std::setw(MAX_CELL_WIDTH + 5) 
                << (v.size() < MAX_CELL_WIDTH ? v : (v.substr(0, MAX_CELL_WIDTH - 3) + "...")) + "\"" << '|';
        }
        to_print << std::endl; 
    }
    
    draw_krywka(to_print, tb->column_info.size());

    return {to_print.str(), Result_Code::Table};
}

DataBase::Table::Table(const std::vector<std::pair<std::string, bool>>& columns)
{
    column_info = columns;
    
    for (const auto& c : columns)
    {
        if(c.second)
            indexed_cols[c.first]; // c++ moment
    }
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
