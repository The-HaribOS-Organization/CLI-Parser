#include "../include/token.hpp"

/* ---------------------------------------------- *
 * TokenBase                                      *
 * ---------------------------------------------- */


BaseToken::BaseToken(std::string _type,
                     int _position,
                     int _column,
                     int _line,
                     bool _isOperator)
            noexcept : type(_type), start(_position), end(_position + 1), column(_column), line(_line),
            isOperator(_isOperator)
{
}

BaseToken::BaseToken(BaseToken &&other) noexcept :
            type(std::move(other.type)),
            start(other.start),
            end(other.end),
            column(other.column),
            line(other.line),
            isOperator(other.isOperator)
{
}

void BaseToken::setType(std::string new_type)
{
    type = new_type;
}

void BaseToken::setEnd(int new_end)
{
    end = new_end;
}

std::string BaseToken::getType() const noexcept
{
    return type;
}


int BaseToken::getStart() const noexcept
{
    return start;
}

int BaseToken::getEnd() const noexcept
{
    return end;
}

int BaseToken::getColumn() const noexcept
{
    return this->column;
}

int BaseToken::getLine() const noexcept
{
    return this->line;
}

bool BaseToken::getIsOperator() const noexcept
{
    return this->isOperator;
}


/* ---------------------------------------------- *
 * Token                                          *
 * ---------------------------------------------- */

template<typename T>
Token<T>::Token(std::string _type,
                T _value,
                int _position,
                int _column,
                int _line,
                bool _isOperator) noexcept : value(_value), BaseToken(_type, _position, _column, _line, _isOperator)
{
}

template<typename T>
Token<T>::Token(Token &&other) noexcept :
        value(std::move(other.value)),
        BaseToken(other)
{
}

template<typename T>
void Token<T>::setValue(T new_value)
{
    value = new_value;
}

template<typename T>
T Token<T>::getValue() const noexcept
{
    return value;
}

/* ---------------------------------------------- *
 * Tokens                                         *
 * ---------------------------------------------- */

Tokens::Tokens(std::vector<BaseToken*> _tokens,
               std::vector<BaseToken*> _consumed,
               std::string _str) noexcept : tokens(std::move(_tokens)),
                                            consumed(std::move(_consumed)),
                                            str(std::move(_str))
{
}
