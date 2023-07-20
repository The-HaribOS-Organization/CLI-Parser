#include <algorithm>

#include "lexer.hpp"
#include "tokenizer.hpp"

using namespace std::literals;

/**
 * check if the char is a valid operator
 */
constexpr bool Lexer::isOperator(std::string_view c)
{
    return std::find(std::begin(Lexer::OPERATIONS), std::end(Lexer::OPERATIONS), c) != std::end(Lexer::OPERATIONS);
}

constexpr bool Lexer::isStartOfOperator(char c)
{
    constexpr std::array<char, 48> OPERATIONS_BEGINNING
    {
            '+', '-', '*', '/', '%', '=', '!', '>', '<', '!', '|', '&', '~', '|', '&', '^', '-', '.', '\\', ':', '%',
            '?', '#', '&', '$', ';', ',', '(', ')', '{', '}', '[', ']', '='
    };
    return std::find(std::begin(OPERATIONS_BEGINNING), std::end(OPERATIONS_BEGINNING), c) != std::end(OPERATIONS_BEGINNING);
}

constexpr bool Lexer::isWhitespace(char c)
{
    return c == ' ';
}

constexpr bool Lexer::isNewline(char c)
{
    return c == '\r' || c == '\n';
}

/**
 * @returns `true` if the last Token isn't a '>' nor a ')' (-> end Token == valid string ending)
 */
bool Lexer::isValidSingleQuoteStringStart(const std::vector<std::unique_ptr<BaseToken>>& tokens)
{
    if (!tokens.empty())
    {
        BaseToken* previous_token = tokens.back().get();

        if(auto token = dynamic_cast<Token<char>*>(previous_token))
        {
            if (token->getIsOperator() &&
                (token->getValue() == '>' ||
                 token->getValue() == ')')) {

                return false;
            }
        }
        else if(auto token = dynamic_cast<Token<std::string_view>*>(previous_token))
        {
            constexpr std::string_view CLOSING_CHEVRON = ">";
            constexpr std::string_view CLOSING_PARENTHESIS = ")";

            if (token->getIsOperator() &&
                (token->getValue() == CLOSING_CHEVRON ||
                 token->getValue() == CLOSING_PARENTHESIS)) {

                return false;
            }
        }
    }
    return true;
}

/**
 * main using of the tokenizer
 */
Tokens Lexer::tokenize(std::string&& str)
{
    Tokenizer tokenizer { std::move(str) };
    return tokenizer.tokenize();
}
