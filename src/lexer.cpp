#include <algorithm>

#include "lexer.hpp"
#include "tokenizer.hpp"

using namespace std::literals;

/**
 * check if the char is a valid operator
 */
bool Lexer::isOperator(std::string_view c)
{
    auto it
    {
        std::find(std::begin(Lexer::OPERATIONS),
                  std::end(Lexer::OPERATIONS),
                  c)
    };
    return it != std::end(Lexer::OPERATIONS);
}

bool Lexer::isStartOfOperator(char c)
{
    constexpr std::array<char, 48> OPERATIONS_BEGINNING
    {
            '+', '-', '*', '/', '%', '=', '!', '>', '<', '!', '|', '&', '~', '|', '&', '^', '-', '.', '\\', ':', '%',
            '?', '#', '&', '$', ';', ',', '(', ')', '{', '}', '[', ']', '='
    };
    auto it
    {
        std::find(std::begin(OPERATIONS_BEGINNING),
                  std::end(OPERATIONS_BEGINNING),
                  c)
    };
    return it != std::end(OPERATIONS_BEGINNING);
}

bool Lexer::isWhitespace(char c)
{
    return c == ' ';
}

bool Lexer::isNewline(char c)
{
    return c == '\r' || c == '\n';
}

bool Lexer::isNumeric(char c)
{
    auto it
            {
                std::find(std::begin(Lexer::FIGURES),
                          std::end(Lexer::FIGURES),
                          c)
            };
    return it != std::end(Lexer::FIGURES);
}

bool Lexer::isAlpha(char c)
{
    auto it
            {
                std::find(std::begin(Lexer::ALPHABET),
                          std::end(Lexer::ALPHABET),
                          c)
            };
    return it != std::end(Lexer::ALPHABET);
}

/**
 * @returns `true` if the last Token isn't a '>' nor a ')' (-> end Token == valid string ending)
 */
bool Lexer::isValidSingleQuoteStringStart(std::vector<BaseToken*> tokens)
{
    if (tokens.size() > 0)
    {
        BaseToken* previous_token = tokens.back();

        if(Token<char>* token = dynamic_cast<Token<char>*>(previous_token))
        {
            if (token->getIsOperator() &&
                (token->getValue() == '>' ||
                 token->getValue() == ')')) {

                return false;
            }
        }
        else if(Token<std::string_view>* token = dynamic_cast<Token<std::string_view>*>(previous_token))
        {
            const std::string_view CLOSING_CHEVRON = ">";
            const std::string_view CLOSING_PARENTHESIS = ")";
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
Tokens Lexer::tokenize(std::string str)
{
    Tokenizer tokenizer { str };
    return tokenizer.tokenize();
}
