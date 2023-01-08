use crate::ParseError::{InvalidUsage, NoCommand, NotExist};
use std::collections::HashMap;
use std::io;

#[derive(Debug)]
enum ParseError {
    NoCommand,
    NotExist,
    InvalidUsage,
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
        io::stdin().read_line(&mut cmd_str).unwrap_or_else(|error| {
            println!("oops... we have an error: {:?}", error);
            0
        });

        parse_and_execute_command(cmd_str.as_str(), db.get_mut())
            .unwrap_or_else(|parse_error| println!("oops... we have an error: {:?}", parse_error));
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
        let table_name = s
            .chars()
            .into_iter()
            .take_while(|char| char != &'(')
            .collect::<String>();
        let table_right_str = table_name.trim();
        let columns_data = &s[(table_right_str.len() + 2)..];
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
            if let Some(_start) = column_possibly_name.to_lowercase().strip_suffix(");") {
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
                println!("{}", error_message)
            }
        }
        // insert table_name ("for first row", "for second row", "for third row");
    } else if let Some(insert_data) = s.to_lowercase().strip_prefix("insert ") {
        //uncheked
        let mut data = &s[7..];
        if let Some(_into) = insert_data.strip_prefix("into ") {
            data = &s[12..];
        }
        let table_name = data
            .chars()
            .into_iter()
            .take_while(|char| char != &'(')
            .collect::<String>();
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
                println!("{}", error_message)
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
        if !select_data.contains(' ') && select_data.len() > 1 {
            // todo check if table name like this correct
            match db.get_table(&s[12..]) {
                Ok(table) => {
                    // todo printing this table
                }
                Err(error_message) => {
                    println!("{}", error_message);
                }
            }
        }
        let table_name = s[12..]
            .chars()
            .into_iter()
            .take_while(|char| char != &' ')
            .collect::<String>();
        let table_right_str = table_name.trim();
        let mut remainder = &s[12 + table_name.len() + 1..];
        if let Some(_join_and_other) = remainder.to_lowercase().strip_prefix("full_join ") {
            let table_join = remainder[10..]
                .chars()
                .into_iter()
                .take_while(|char| char != &' ')
                .collect::<String>();
            remainder = &remainder[table_join.len() + 10 + 1..];
            let on;
            if let Some(_on_and_other) = remainder.to_lowercase().strip_prefix("on ") {
                on = remainder[3..]
                    .chars()
                    .into_iter()
                    .take_while(|char| char != &' ')
                    .collect::<String>();
                remainder = &remainder[on.len() + 3 + 1..];
            } else {
                println!("1");
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
                println!("2");
                return Err(InvalidUsage);
            }
            //todo  we have all for full join(?)
        }
        //SELECT FROM owners
        //           FULL_JOIN cats ON owner_id = cat_owner_id *WHERE name = “Murzik”;
        // *where some *= ("1" | id);

        if remainder.to_lowercase().starts_with("where ") {
            let what_where = remainder[6..]
                .chars()
                .into_iter()
                .take_while(|char| char != &' ')
                .collect::<String>();
            remainder = &remainder[what_where.len() + 6 + 1..];
        }
    } else {
        return Err(NotExist);
    }

    Ok(())
}
