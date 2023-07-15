#include "../include/lexer.hpp"
#include "../include/token.hpp"
#include "../include/tokenizer.hpp"

using namespace std::literals;

/**
 * check if the token is a valid operator
 */
bool Lexer::isOperator(std::string c)
{
    return Lexer::OPERATIONS.contains(c);
}

bool Lexer::isWhitespace(std::string c)
{
    return c == ' 's;
}

bool Lexer::isNewline(int c)
{
    return c == "\r"s || c == "\n"s;
}

bool Lexer::isNumeric(std::string c)
{
    return Lexer::FIGURES.contains(c);
}

bool Lexer::isAlpha(std::string c)
{
    return Lexer::ALPHABET.contains(c);
}

/**
 * @returns `true` if the last Token isn't a '>' nor a ')' (-> end Token == valid string ending)
 */
bool Lexer::isValidSingleQuoteStringStart(std::vector<Token> tokens)
{
    if (tokens.size() > 0) {
        var previousToken = tokens[tokens.size() - 1];
        if (previousToken.getIsOperator() &&
            (previousToken.getValue() == ">"s ||
            previousToken.getValue() == ")"s)) {

            return false;
        }
    }
    return true;
}

/**
 * main using of the tokenizer
 */
Tokens Lexer::tokenize(std::string str)
{
    Tokenizer tokenizer { str };
    return tokenizer.tokenize();
}