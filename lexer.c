#include "lexer.h"

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
