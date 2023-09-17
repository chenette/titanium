use crate::lexer::Token;

#[derive(Debug, PartialEq, Clone)]
pub enum Expr {
    Number(i32),
    Add(Box<Expr>, Box<Expr>),
    Subtract(Box<Expr>, Box<Expr>),
    DoubleEquals(Box<Expr>, Box<Expr>),
}

#[derive(Debug, PartialEq, Clone)]
pub enum Stmt {
    Expr(Expr),
    If(Box<Expr>, Box<Stmt>),
    Ret(Box<Expr>),
}

pub struct Parser {
    tokens: Vec<Token>,
    position: usize,
}

impl Parser {
    pub fn new(tokens: Vec<Token>) -> Self {
        Self {
            tokens,
            position: 0,
        }
    }

    pub fn parse(&mut self) -> Stmt {
        self.parse_statement()
    }

    fn parse_statement(&mut self) -> Stmt {
        if self.matches(&[Token::If]) {
            self.consume(Token::If);

            self.consume(Token::OpenParen);
            let condition = self.parse_expression();
            self.consume(Token::ClosedParen);

            self.consume(Token::OpenCurly);
            let body = self.parse_statement();
            self.consume(Token::ClosedCurly);

            Stmt::If(Box::new(condition), Box::new(body))
        } else if self.matches(&[Token::Return]) { 
            self.consume(Token::Return);
            let return_value = self.parse_expression();
            Stmt::Ret(Box::new(return_value))
        } else {
            let expr = self.parse_expression();
            Stmt::Expr(expr)
        }
    }

    fn parse_expression(&mut self) -> Expr {
        let mut left = self.parse_term();

        while let Some(token) = self.tokens.get(self.position) {
            match token {
                Token::Plus => {
                    self.position += 1;
                    let right = self.parse_term();
                    left = Expr::Add(Box::new(left), Box::new(right));
                }
                Token::Minus => {
                    self.position += 1;
                    let right = self.parse_term();
                    left = Expr::Subtract(Box::new(left), Box::new(right));
                }
                Token::DoubleEquals => {
                    self.position += 1;
                    let right = self.parse_term();
                    left = Expr::DoubleEquals(Box::new(left), Box::new(right));
                }
                _ => break,
            }
        }

        left
    }

    fn parse_term(&mut self) -> Expr {
        match self.tokens[self.position] {
            Token::Number(num) => {
                self.position += 1;
                Expr::Number(num)
            }
            _ => panic!("Expected a number"),
        }
    }

    fn consume(&mut self, expected: Token) {
        if let Some(token) = self.tokens.get(self.position) {
            if *token == expected {
                self.position += 1;
            } else {
                panic!("Expected {:?}, found {:?}", expected, token);
            }
        } else {
            panic!("Expected {:?}, but reached the end of input", expected);
        }
    }

    fn matches(&self, expected_tokens: &[Token]) -> bool {
        expected_tokens.iter().any(|&token| {
            if let Some(current_token) = self.tokens.get(self.position) {
                *current_token == token
            } else {
                false
            }
        })
    }
}
