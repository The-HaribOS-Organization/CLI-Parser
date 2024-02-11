#include "../include/token.hpp"

/* ---------------------------------------------- *
 * TokenBase                                      *
 * ---------------------------------------------- */
Token::Token(TokenType _type, std::string_view _value, int _position, int _column, int _line, bool _isOperator) noexcept
        : value(_value), type(_type), start(_position), end(_position + 1), column(_column), line(_line), isOperator(_isOperator) {}

void Token::setType(TokenType new_type)
{
    type = new_type;
}

void Token::setEnd(int new_end)
{
    end = new_end;
}

TokenType Token::getType() const noexcept
{
    return type;
}

int Token::getStart() const noexcept
{
    return start;
}

int Token::getEnd() const noexcept
{
    return end;
}

int Token::getColumn() const noexcept
{
    return column;
}

int Token::getLine() const noexcept
{
    return line;
}

bool Token::getIsOperator() const noexcept
{
    return isOperator;
}


/* ---------------------------------------------- *
 * Token                                          *
 * ---------------------------------------------- */

void Token::setValue(std::string_view new_value)
{
    value = new_value;
}

const std::string_view& Token::getValue() const noexcept
{
    return value;
}

/* ---------------------------------------------- *
 * Tokens                                         *
 * ---------------------------------------------- */

Tokens::Tokens(std::vector<Token>&& _tokens, std::string_view _str) noexcept
        : tokens(std::move(_tokens)), str(_str)
{
}
