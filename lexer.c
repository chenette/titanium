#include <stdio.h>
#include <ctype.h>

// Token types
enum TokenType {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_EOF
};

// Token structure
struct Token {
    enum TokenType type;
    double value; // For TOKEN_NUMBER
};

// Global variables
char currentChar;
struct Token currentToken;

// Advance to the next character in input
void advance() {
    currentChar = getchar();
}

// Skip whitespace characters
void skipWhitespace() {
    while (isspace(currentChar))
        advance();
}

// Lexical analysis: convert characters to tokens
struct Token getNextToken() {
    skipWhitespace();

    if (isdigit(currentChar)) {
        // Parse numbers
        double value = 0;
        while (isdigit(currentChar)) {
            value = value * 10 + (currentChar - '0');
            advance();
        }
        struct Token token = {TOKEN_NUMBER, value};
        return token;
    }
    
    if (currentChar == '+') {
        advance();
        struct Token token = {TOKEN_PLUS, 0};
        return token;
    }
    
    if (currentChar == '-') {
        advance();
        struct Token token = {TOKEN_MINUS, 0};
        return token;
    }

    // End of input
    struct Token token = {TOKEN_EOF, 0};
    return token;
}

int main() {
    // Initialize
    advance();
    
    while (currentChar != EOF) {
        currentToken = getNextToken();
        
        // Display token information
        switch (currentToken.type) {
            case TOKEN_NUMBER:
                printf("Number: %lf\n", currentToken.value);
                break;
            case TOKEN_PLUS:
                printf("Plus\n");
                break;
            case TOKEN_MINUS:
                printf("Minus\n");
                break;
            case TOKEN_EOF:
                printf("End of File\n");
                break;
        }
    }
    
    return 0;
}
