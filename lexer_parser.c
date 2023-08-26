#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100

typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_NUMBER,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
} Token;

Token* tokenize(FILE* inputFile) {
    Token* tokens = NULL;
    int tokenCount = 0;
    int tokenCapacity = 0;
    
    char buffer[MAX_TOKEN_LENGTH];
    int bufferIndex = 0;
    char c;

    while ((c = fgetc(inputFile)) != EOF) {
        if (isspace(c)) {
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                Token token;

                if (isdigit(buffer[0])) {
                    token.type = TOKEN_NUMBER;
                } else if (isalpha(buffer[0])) {
                    token.type = TOKEN_IDENTIFIER;
                } else {
                    token.type = TOKEN_OPERATOR;
                }

                strcpy(token.value, buffer);

                if (tokenCount >= tokenCapacity) {
                    tokenCapacity += 10;
                    tokens = (Token*)realloc(tokens, tokenCapacity * sizeof(Token));
                }

                tokens[tokenCount] = token;
                tokenCount++;

                bufferIndex = 0;
            }
        } else {
            if (bufferIndex < MAX_TOKEN_LENGTH - 1) {
                buffer[bufferIndex] = c;
                bufferIndex++;
            } else {
                // Token too long, ignore excess characters
                while ((c = fgetc(inputFile)) != EOF && !isspace(c)) {
                }
                bufferIndex = 0;
            }
        }
    }

    if (bufferIndex > 0) {
        buffer[bufferIndex] = '\0';
        Token token;

        if (isdigit(buffer[0])) {
            token.type = TOKEN_NUMBER;
        } else if (isalpha(buffer[0])) {
            token.type = TOKEN_IDENTIFIER;
        } else {
            token.type = TOKEN_OPERATOR;
        }

        strcpy(token.value, buffer);

        if (tokenCount >= tokenCapacity) {
            tokenCapacity += 1;
            tokens = (Token*)realloc(tokens, tokenCapacity * sizeof(Token));
        }

        tokens[tokenCount] = token;
        tokenCount++;
    }

    Token eofToken;
    eofToken.type = TOKEN_EOF;
    strcpy(eofToken.value, "");
    if (tokenCount >= tokenCapacity) {
        tokenCapacity += 1;
        tokens = (Token*)realloc(tokens, tokenCapacity * sizeof(Token));
    }
    tokens[tokenCount] = eofToken;

    return tokens;
}

void freeTokens(Token* tokens) {
    free(tokens);
}

int parseExpression(Token* tokens, int* currentIndex);

int parseNumber(Token* tokens, int* currentIndex) {
    int value = atoi(tokens[*currentIndex].value);
    (*currentIndex)++;
    return value;
}

int parseTerm(Token* tokens, int* currentIndex) {
    int left = parseNumber(tokens, currentIndex);

    while (tokens[*currentIndex].type == TOKEN_OPERATOR &&
           (tokens[*currentIndex].value[0] == '+' || tokens[*currentIndex].value[0] == '-')) {
        char operator = tokens[*currentIndex].value[0];
        (*currentIndex)++;

        int right = parseNumber(tokens, currentIndex);

        if (operator == '+') {
            left += right;
        } else if (operator == '-') {
            left -= right;
        }
    }

    return left;
}

int parseExpression(Token* tokens, int* currentIndex) {
    return parseTerm(tokens, currentIndex);
}

int main() {
    FILE* inputFile = fopen("input.txt", "r");
    if (!inputFile) {
        printf("Error opening input file\n");
        return 1;
    }

    Token* tokens = tokenize(inputFile);

    int currentIndex = 0;
    int result = parseExpression(tokens, &currentIndex);

    printf("Result: %d\n", result);

    freeTokens(tokens);
    fclose(inputFile);

    return 0;
}
