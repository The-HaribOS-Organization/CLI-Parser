#include <algorithm>

#include "lexer.hpp"
#include "tokenizer.hpp"

using namespace std::literals;

/**
 * check if the char is a valid operator
 */
bool Lexer::isOperator(std::string_view c)
{
    return std::find(std::begin(Lexer::OPERATIONS), std::end(Lexer::OPERATIONS), c) != std::end(Lexer::OPERATIONS);
}

bool Lexer::isStartOfOperator(char c)
{
    constexpr std::array<char, 48> OPERATIONS_BEGINNING
    {
            '+', '-', '*', '/', '%', '=', '!', '>', '<', '!', '|', '&', '~', '|', '&', '^', '-', '.', '\\', ':', '%',
            '?', '#', '&', '$', ';', ',', '(', ')', '{', '}', '[', ']', '='
    };
    return std::find(std::begin(OPERATIONS_BEGINNING), std::end(OPERATIONS_BEGINNING), c) != std::end(OPERATIONS_BEGINNING);
}

bool Lexer::isWhitespace(char c)
{
    return c == ' ';
}

bool Lexer::isNewline(char c)
{
    return c == '\r' || c == '\n';
}

/**
 * @returns `true` if the last Token isn't a '>' nor a ')' (-> end Token == valid string ending)
 */
bool Lexer::isValidSingleQuoteStringStart(const std::vector<Token>& tokens)
{
    if (!tokens.empty())
    {
        const Token& previous_token = tokens.back();

        constexpr std::string_view CLOSING_CHEVRON = ">";
        constexpr std::string_view CLOSING_PARENTHESIS = ")";

        if (previous_token.getIsOperator() &&
            (previous_token.getValue() == CLOSING_CHEVRON || previous_token.getValue() == CLOSING_PARENTHESIS))
        {
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
    Tokenizer tokenizer { std::move(str) };
    return tokenizer.tokenize();
}
