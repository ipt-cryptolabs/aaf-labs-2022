use crate::ParseError::{InvalidUsage, NoCommand, NotExist, UnacceptableData};
use std::collections::HashMap;
use std::io;

#[derive(Debug)]
enum ParseError {
    NoCommand,
    NotExist,
    InvalidUsage,
    UnacceptableData,
}

struct DamnDB {
    pub tables: HashMap<String, Table>,
}

impl DamnDB {
    pub fn new() -> DamnDB {
        DamnDB {
            tables: HashMap::new(),
        }
    }

    pub fn get_mut(&mut self) -> &mut DamnDB {
        self
    }

    pub fn is_table_exist(&self, table_name: &str) -> bool {
        self.tables.contains_key(table_name)
    }

    pub fn try_create_table(&mut self, table: Table) -> Result<(), &str> {
        if self.is_table_exist(table.name.as_str()) {
            return Err("table with provided name already exists");
        }
        self.tables.insert(table.name.clone(), table);
        Ok(())
    }

    pub fn insert_into_table(&mut self, table_name: &str, data: Vec<String>) -> Result<(), &str> {
        if let Some(table) = self.tables.get_mut(table_name) {
            if table.columns.len() != data.len() {
                return Err("insertion into table more or less than table have columns impossible");
            }
            let mut it = data.into_iter();
            for x in table.data.iter_mut() {
                x.push(it.next().unwrap());
            }
        } else {
            return Err("insertion into non-existing table impossible");
        }
        Ok(())
    }

    pub fn get_table_mut(&mut self, table_name: &str) -> Result<&mut Table, &str> {
        if let Some(table) = self.tables.get_mut(table_name) {
            Ok(table)
        } else {
            Err("insertion into non-existing table impossible")
        }
    }

    pub fn get_table(&mut self, table_name: &str) -> Result<&Table, &str> {
        if let Some(table) = self.tables.get(table_name) {
            Ok(table)
        } else {
            Err("insertion into non-existing table impossible")
        }
    }
}

#[derive(Clone)]
struct Table {
    name: String,
    columns: Vec<String>,
    data: Vec<Vec<String>>,
}

impl Table {
    pub fn new(name: String, columns: Vec<String>, data: Vec<Vec<String>>) -> Table {
        Table {
            name,
            columns,
            data,
        }
    }
}

fn main() {
    let mut db = DamnDB::new();
    loop {
        let mut cmd_str: String = String::new();
        println!("Enter command");
        //todo change to read until ;
        io::stdin().read_line(&mut cmd_str).unwrap_or_else(|error| {
            println!("oops... we have an error: {:?}", error);
            0
        });
        parse_and_execute_command(cmd_str.as_str(), db.get_mut())
            .unwrap_or_else(|parse_error| println!("oops... we have an error: {:?}", parse_error));
    }
}

fn check_table_name(possible_name: &str) -> bool {
    let mut it = possible_name.chars();
    match it.next() {
        None => false,
        Some(first) => match first.is_ascii_alphabetic() {
            true => it.all(|other| other.is_ascii_alphanumeric()),
            false => false,
        },
    }
}

// просторова та часова складність
fn parse_and_execute_command(cmd_str: &str, db: &mut DamnDB) -> Result<(), ParseError> {
    let s = cmd_str.trim();
    if s.is_empty() {
        return Err(NoCommand);
    }
    // create table_name (first_row, another_row);
    if let Some(create_data) = s.to_lowercase().strip_prefix("create ") {
        let table_name = s[7..]
            .chars()
            .into_iter()
            .take_while(|char| char != &'(')
            .collect::<String>();
        let table_right_str = table_name.trim();
        if !check_table_name(&s[12..]) {
            println!("provided table name is unacceptable");
            return Err(UnacceptableData);
        }
        let columns_data = &s[(table_right_str.len() + 7 + 2)..];
        let columns = columns_data.split(", ").collect::<Vec<&str>>();
        let mut finished = false;
        let mut table_columns = Vec::new();
        for column_possibly_name in columns {
            if finished {
                return Err(InvalidUsage);
            }
            if column_possibly_name.contains("INDEXED") {
                todo!()
            }
            if column_possibly_name.to_lowercase().ends_with(");") {
                finished = true;
                table_columns.push(String::from(
                    &column_possibly_name[..column_possibly_name.len() - 2],
                ));
            } else {
                table_columns.push(String::from(column_possibly_name));
            };
        }
        match db.try_create_table(Table::new(
            String::from(table_right_str),
            table_columns,
            Vec::new(),
        )) {
            Ok(_) => {
                println!("table with name {table_right_str} has been created")
            }
            Err(error_message) => {
                println!("{}", error_message);
                return Err(InvalidUsage);
            }
        }
        // insert table_name ("for first row", "for second row", "for third row");
    } else if let Some(insert_data) = s.to_lowercase().strip_prefix("insert ") {
        let mut data = &s[7..];
        if let Some(_into) = insert_data.strip_prefix("into ") {
            data = &s[12..];
        }
        let table_name = data
            .chars()
            .into_iter()
            .take_while(|char| char != &'(')
            .collect::<String>();
        if !check_table_name(&s[12..]) {
            println!("provided table name is unacceptable");
            return Err(UnacceptableData);
        }
        let table_right_str = table_name.trim();
        let columns_data = &data[(table_right_str.len() + 2)..];
        let columns = columns_data.split(", ").collect::<Vec<&str>>();
        let mut finished = false;
        let mut table_columns_data = Vec::new();
        for column_possibly_data in columns {
            println!("{column_possibly_data}");
            if finished
                || !column_possibly_data.starts_with('"')
                || (!column_possibly_data.ends_with('"') && !column_possibly_data.ends_with(';'))
            {
                return Err(InvalidUsage);
            }
            let mut sstr;
            if let Some(_start) = column_possibly_data.strip_suffix(");") {
                finished = true;
                sstr = &column_possibly_data[..column_possibly_data.len() - 2];
            } else {
                sstr = column_possibly_data;
            }
            sstr = &sstr[1..sstr.len() - 1];
            table_columns_data.push(sstr.to_string());
        }
        match db.insert_into_table(table_right_str, table_columns_data) {
            Ok(_) => {
                println!("data into {table_right_str} inserted");
            }
            Err(error_message) => {
                println!("{}", error_message);
                return Err(InvalidUsage);
            }
        }
        /*SELECT FROM cats;
        SELECT FROM cats
          WHERE name = “Murzik”;
        SELECT FROM owners
          FULL_JOIN cats ON owner_id = cat_owner_id;
        SELECT FROM owners
          FULL_JOIN cats ON owner_id = cat_owner_id WHERE name = “Murzik”;
          */
    } else if let Some(select_data) = s.to_lowercase().strip_prefix("select from ") {
        let mut data;
        if !select_data.contains(' ') && select_data.len() > 1 {
            match db.get_table(&s[12..]) {
                Ok(table) => {
                    data = table;
                }
                Err(error_message) => {
                    println!("{}", error_message);
                    return Err(InvalidUsage);
                }
            }
        }
        let table_name = s[12..]
            .chars()
            .into_iter()
            .take_while(|char| char != &' ')
            .collect::<String>();
        let table_right_str = table_name.trim();
        match db.get_table(table_right_str) {
            Ok(table) => {
                data = table;
            }
            Err(error_message) => {
                println!("{}", error_message);
                return Err(InvalidUsage);
            }
        }
        let mut remainder = &s[12 + table_name.len() + 1..];
        let mut table2 = None;
        if remainder.to_lowercase().starts_with("full_join ") {
            let table_join = remainder[10..]
                .chars()
                .into_iter()
                .take_while(|char| char != &' ')
                .collect::<String>();
            let join_table;
            match db.get_table(table_join.as_str()) {
                Ok(table) => {
                    join_table = table;
                }
                Err(error_message) => {
                    println!("{}", error_message);
                    return Err(InvalidUsage);
                }
            }
            remainder = &remainder[table_join.len() + 10 + 1..];
            let on;
            if remainder.to_lowercase().starts_with("on ") {
                on = remainder[3..]
                    .chars()
                    .into_iter()
                    .take_while(|char| char != &' ')
                    .collect::<String>();
                remainder = &remainder[on.len() + 3 + 1..];
            } else {
                return Err(InvalidUsage);
            }
            let another_on;
            if let Some(_another_on_and_other) = remainder.to_lowercase().strip_prefix("= ") {
                another_on = remainder[2..]
                    .chars()
                    .into_iter()
                    .take_while(|char| char != &' ' && char != &';')
                    .collect::<String>();

                remainder = &remainder[another_on.len() + 2..];
            } else {
                return Err(InvalidUsage);
            }
            table2 = Some((join_table, on, another_on));
            //todo  we have all for full join!
        }
        //SELECT FROM owners
        //           FULL_JOIN cats ON owner_id = cat_owner_id WHERE name *= “Murzik”;
        // *where some *= ("1" | id);
         let mut wherre = None;
        if remainder.to_lowercase().starts_with("where ") {
            let what_where = remainder[6..]
                .chars()
                .into_iter()
                .take_while(|char| char != &' ')
                .collect::<String>();
            remainder = &remainder[what_where.len() + 6 + 1..];
            // if what_where.ends_with('"') && what_where.starts_with('"')
            if !remainder.starts_with("= ") {
                return Err(InvalidUsage);
            }
            remainder = &remainder[2..remainder.len()-1];
            let mut what_eq;
            if remainder.starts_with('(') && remainder.ends_with(')') {
                what_eq = remainder[1..remainder.len()-1].split('|').collect::<Vec<&str>>();
                what_eq.iter_mut().for_each(|each| *each = each.trim())
            } else {
                what_eq = vec![remainder];
            }
            wherre = Some((what_where, what_eq));
        }
            //todo maybe we dont need it, and we can only in full_join change data (that table) to another and filter with where then
        match table2 {
            None => { // just if where

                }
            Some((join_t, on, another_on)) => {
                //get data, make new "virtual" table, check if where
            }
        }

        //print all
    } else {
        return Err(NotExist);
    }

    Ok(())
}
