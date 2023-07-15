#include <array>
#include <iostream>

#include "../include/lexer.hpp"
#include "../include/tokenizer.hpp"

Token::Token(std::string& _str) : str(_str), position(0), column(0), line(1)
{
}

/**
 * method to call for use this tokenizer
 */
Tokens Tokenizer::tokenize()
{
    std::vector<Token> tokens {};
    std::string last_token { "<START>" };

    while(this->position < this->str.len.size())
    {
        if (Lexer::isWhitespace(Tokenizer.currentChar())) {      // whitespaces

            tokens.push_back(Tokenizer.consumeWhitespace());

        } else if (Lexer::isNumeric(Tokenizer.currentChar())) {  // numerics

            tokens.push(Tokenizer.consumeNumber());

        } else if (Tokenizer.currentChar() == '"') {            // strings

            tokens.push(Tokenizer.consumeString());

        } else if (Tokenizer.currentChar() == "'") {            // valid quote string start
            if (Lexer::isValidSingleQuoteStringStart(tokens)) {

                tokens.push(Tokenizer.consumeString());

            } else {

                tokens.push(Tokenizer.consumeOperator());

            }
        } else if (Lexer::OPERATIONS[Tokenizer.currentChar()]) {  // operators

            tokens.push(Tokenizer.consumeOperator());

        } else {                                                  // 404 - char does not exists (lol)

            if (position < this->str.size()) {
                std::cout << "Error: 404, char does not exists (" << Tokenizer.currentChar() << ")." << "\n";
            }

        }
    }

    Tokens token_set { tokens, std::vector<Token> {}, str };

    return token_set;
}

Token Tokenizer::makeToken(std::string type, std::string value, bool isOperator)
{
    Token token
    {
        type,
        value,
        this->position,
        this->column,
        this->line,
        isOperator
    };
    return token;
}

std::string Tokenizer::currentChar()
{
    return this->str[this->position];
}

std::string Tokenizer::nextChar()
{
    return this->str[this->position + 1];
}

std::string Tokenizer::nextCharAt(int delta_index)
{
    return this->str[this->position + delta_index];
}

/**
 * consume char:
 * increments position & column
 * @returns last_token
 */
std::string Tokenizer::consumeChar()
{
    std::string last_token { this->currentChar() };
    this->position++;
    this->column++;
    return last_token;
}

/**
 * Let's imagine an entrance like this one : 123.456e-789 (generalized in this form : XXX.YYY(e|E)[-]ZZZ).
 * We need to reach and parse this number.
 * This is the summary of steps that are taking place in this process.
 *
 * I : consumes XXX
 * II : consumes .YYY
 * III : consumes e|E[-]
 * IV : consumes ZZZ
 *
 * Welpike
 */
Token Tokenizer::consumeNumber()
{
    Token token { this->makeToken("NUMBER", std::string {""}, false) };

    std::string value { this->consumeChar() };

    // I
    while (Lexer::isNumeric(this->consumeChar())) {
        value += this->consumeChar();
    }

    // II
    if (this->currentChar() == "." && Lexer.isNumeric(this->nextChar())) {
        value += this->consumeChar();
    }
    while (Lexer::isNumeric(this->consumeChar())) {
        value += this->consumeChar();
    }

    // III
    if (this->currentChar() == "e" || this->currentChar() == "E") {
        // scientific notation, e.g. 1e6 or 1e-6
        if (Lexer.isNumeric(this->nextChar())) {
            // e.g. 1e6
            value += this->consumeChar();
        } else if (this->nextChar() == "-") {
            // e.g. 1e-6
            value += this->consumeChar();
            value += this->consumeChar();
        }
    }

    // IV
    while (Lexer::isNumeric(this->consumeChar())) {
        value += this->consumeChar();
    }

    token.setValue(value);
    token.setEnd()
}

/**
 * This method handle all types of operators, including operators with many characters.
 */
Token Tokenizer::consumeOperator()
{
    Token op { this->makeToken(std::string {""}, std::string {""}, true) };
    std::string value { this->consumeChar() }; // consume leading char

    while (this->currentChar() && Lexer::OPERATIONS[value + this->currentChar()]) {
        value += this->consumeChar();
    }

    op.setType(Lexer::OPERATIONS[value]);
    op.setValue(value);
    op.setEnd(position);
    return op;
}

/**
 * handles strings, even with special whitespaces (e.g: \t)
 */
Token Tokenizer::consumeString()
{
    Token str { this->makeToken("STRING", std::string {""}, false) };
    std::string startChar { this->consumeChar() };
    std::string value { "" };

    while (this->currentChar() && this->currentChar() != startChar) {
        if (this->currentChar() == "\\") {
            this->consumeChar(); // consume escape char and get the next one
            let nextChar = this->consumeChar();
            if (nextChar == "b") {
                value += "\b";
            } else if (nextChar == "f") {
                value += "\f";
            } else if (nextChar == "n") {
                value += "\n";
            } else if (nextChar == "r") {
                value += "\r";
            } else if (nextChar == "t") {
                value += "\t";
            } else if (nextChar == "v") {
                value += "\v";
            } else {
                value += nextChar;
            }
        } else {
            value += this->consumeChar();
        }
    }
    if (this->currentChar() != startChar) {
        // ERROR (string not terminated, only one quote)
        std::cout << "Error : string not terminated (" << this->currentChar() << "\n";
    } else {
        this->consumeChar(); // consume final quote
    }
    str.setValue(value);
    str.setEnd(position);
    return str;
}

/**
 * Handles whitespaces and carriage returns
 */
Token Tokenizer::consumeWhitespace()
{
    Token whitespace { makeToken("WHITESPACE", std::string { "" }, false) };
    std::string value{ "" };
    while (this->currentChar() && Lexer::isWhitespace(this->currentChar())) {
        if (Lexer::isNewline(this->currentChar())) {
            this->column = 0;
            this->line++;
        }
        value += this->consumeChar();
    }
    whitespace.setValue(value);
    whitespace.setEnd(this->position);
    return whitespace;
}
