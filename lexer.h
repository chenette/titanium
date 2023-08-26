#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define MAX_TOKEN_LENGTH 100

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_NUMBER,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[100];
} Token;

Token* tokenize(FILE* inputFile);
void freeTokens(Token* tokens);

#endif
