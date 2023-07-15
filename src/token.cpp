#include "../include/token.hpp"

/* ---------------------------------------------- *
 * Token                                          *
 * ---------------------------------------------- */

Token::Token(const std::string& _type,
             const std::string& _value,
             int _position,
             int _column,
             int _line,
             bool _isOperator)
noexcept : type(_type), value(_value), start(_position), end(_position + 1), column(_column), line(_line),
isOperator(_isOperator)
{
}

void Token::setType(std::string new_type)
{
    this->type = new_type;
}

void Token::setValue(std::string new_value)
{
    this->value = new_value;
}

void Token::setEnd(int new_end)
{
    this->end = new_end;
}

std::string Token::getType() const noexcept
{
    return this->type;
}

std::string Token::getValue() const noexcept
{
    return this->value;
}

int Token::getStart() const noexcept
{
    return this->start;
}

int Token::getEnd() const noexcept
{
    return this->end;
}

int Token::getColumn() const noexcept
{
    return this->column;
}

int Token::getLine() const noexcept
{
    return this->line;
}

bool Token::getIsOperator() const noexcept
{
    return this->isOperator;
}


/* ---------------------------------------------- *
 * Tokens                                         *
 * ---------------------------------------------- */

Tokens::Tokens(std::vector<Token> _tokens,
               std::vector<Token> _consumed,
               std::string& _str) noexcept : tokens(_tokens), consumed(_consumed), str(_str)
{
}
