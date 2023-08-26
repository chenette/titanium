#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

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
