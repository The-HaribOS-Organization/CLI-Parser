#include "../include/token.hpp"

/* ---------------------------------------------- *
 * TokenBase                                      *
 * ---------------------------------------------- */


constexpr BaseToken::BaseToken(TokenType _type, int _position, int _column, int _line, bool _isOperator) noexcept
        : type(_type), start(_position), end(_position + 1), column(_column), line(_line), isOperator(_isOperator)
{
}

constexpr void BaseToken::setType(TokenType new_type)
{
    type = new_type;
}

constexpr void BaseToken::setEnd(int new_end)
{
    end = new_end;
}

constexpr TokenType BaseToken::getType() const noexcept
{
    return type;
}


constexpr int BaseToken::getStart() const noexcept
{
    return start;
}

constexpr int BaseToken::getEnd() const noexcept
{
    return end;
}

constexpr int BaseToken::getColumn() const noexcept
{
    return column;
}

constexpr int BaseToken::getLine() const noexcept
{
    return line;
}

constexpr bool BaseToken::getIsOperator() const noexcept
{
    return isOperator;
}


/* ---------------------------------------------- *
 * Token                                          *
 * ---------------------------------------------- */

template<CorrectTokenType T>
constexpr Token<T>::Token(TokenType _type, T _value, int _position, int _column, int _line, bool _isOperator) noexcept
        : value(_value), BaseToken(_type, _position, _column, _line, _isOperator)
{
}

template<CorrectTokenType T>
void Token<T>::setValue(T new_value)
{
    value = new_value;
}

template<CorrectTokenType T>
const T& Token<T>::getValue() const noexcept
{
    return value;
}

/* ---------------------------------------------- *
 * Tokens                                         *
 * ---------------------------------------------- */

Tokens::Tokens(std::vector<std::unique_ptr<BaseToken>>&& _tokens, std::string_view _str) noexcept
        : tokens(std::move(_tokens)), str(_str)
{
}
