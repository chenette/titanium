mod lexer;
mod parser;

use std::fs::File;
use std::io::{self, Read};
use lexer::Lexer;
use parser::Parser;

fn read_input_from_file(filename: &str) -> Result<String, io::Error> {
    let mut file = File::open(filename)?;
    let mut input = String::new();
    file.read_to_string(&mut input)?;
    Ok(input)
}

fn main() {
    if let Ok(input) = read_input_from_file("input2.ti") {
        let mut lexer = Lexer::new(&input);
        let tokens = lexer.tokenize();
        println!("Tokens: {:?}", tokens);

        let mut parser = Parser::new(tokens);
        let ast = parser.parse();
        println!("AST: {:?}", ast);
    } else {
        eprintln!("Error reading input from file.");
    }
}
