#[derive(Debug, PartialEq, Clone, Copy)]
pub enum Token {
    If,
    DoubleEquals,
    OpenCurly,
    ClosedCurly,
    OpenParen,
    ClosedParen,
    Number(i32),
    Plus,
    Minus,
    Return,
    EOF,
}

pub struct Lexer {
    input: Vec<char>,
    position: usize,
}

impl Lexer {
    pub fn new(input: &str) -> Self {
        Self {
            input: input.chars().collect(),
            position: 0,
        }
    }

    pub fn advance(&mut self) {
        self.position += 1;
    }

    pub fn advance_by(&mut self, count: usize) {
        self.position += count;
    }

    pub fn peek(&self) -> Option<char> {
        self.input.get(self.position).cloned()
    }

    pub fn tokenize(&mut self) -> Vec<Token> {
        let mut tokens = vec![];
        while self.position < self.input.len() {
            match self.peek() {
                Some(c) if c.is_digit(10) => {
                    let mut num_str = String::new();
                    while let Some(c) = self.peek() {
                        if c.is_digit(10) {
                            num_str.push(c);
                            self.advance();
                        } else {
                            break;
                        }
                    }
                    let num = num_str.parse::<i32>().unwrap();
                    tokens.push(Token::Number(num));
                }
                Some('r') if self.input[self.position] == 'r' => {
                    if self.position + 1 < self.input.len() && self.input[self.position + 1] == 'e' { // add rest of characters
                        tokens.push(Token::Return);
                        self.advance_by(6); // Skip 'return'
                    }
                }
                Some('i') if self.input[self.position] == 'i' => {
                    if self.position + 1 < self.input.len() && self.input[self.position + 1] == 'f' {
                        tokens.push(Token::If);
                        self.advance_by(2); // Skip 'if'
                    }
                }
                Some('=') if self.input[self.position] == '=' => {
                    if self.position + 1 < self.input.len() && self.input[self.position + 1] == '=' {
                        tokens.push(Token::DoubleEquals);
                        self.advance_by(2); // Skip '=='
                    }
                }
                Some('(') => {
                    tokens.push(Token::OpenParen);
                    self.advance();
                }
                Some(')') => {
                    tokens.push(Token::ClosedParen);
                    self.advance();
                }
                Some('{') => {
                    tokens.push(Token::OpenCurly);
                    self.advance();
                }
                Some('}') => {
                    tokens.push(Token::ClosedCurly);
                    self.advance();
                }
                Some('+') => {
                    tokens.push(Token::Plus);
                    self.advance();
                }
                Some('-') => {
                    tokens.push(Token::Minus);
                    self.advance();
                }
                Some(_) => {
                    // Ignore any other characters
                    self.advance();
                }
                None => break,
            }
        }
        tokens.push(Token::EOF);
        tokens
    }
}
