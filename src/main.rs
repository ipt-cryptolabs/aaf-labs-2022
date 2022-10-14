use std::io;
use crate::ParseError::{InvalidUsage, NoCommand, NotExist};

#[derive(Debug)]
enum ParseError{
    NoCommand,
    NotExist,
    InvalidUsage
}

fn main(){
    let mut cmd_str: String = String::new();
    loop {
        println!("Enter command");
        io::stdin().read_line(&mut cmd_str);
        parse_command(&cmd_str).expect("oh no... error...");
    }
}

fn parse_command(cmd_str: &String) -> Result<(), ParseError>{
    let s = cmd_str.trim().split_whitespace().collect::<Vec<&str>>();
    if s.is_empty() {
        return Err(NoCommand);
    }
    match s[0].to_lowercase() {
        &"create" => {
            if s.len() < 2 {
                Err(InvalidUsage)
            }
            todo!();
        },
         &"insert" => {
             if s.len() < 2 {
                 Err(InvalidUsage)
             }
             todo!();

         },
         &"select" => {
             todo!();
         }
        _ => { Err(NotExist)}
    }
    Ok(())
}