#include <array>
#include <iostream>

#include "lexer.hpp"
#include "tokenizer.hpp"


Tokenizer::Tokenizer(std::string&& _str) : str(std::move(_str)), position(0), column(0), line(1)
{
}

/**
 * method to call for use this tokenizer
 */
Tokens Tokenizer::tokenize()
{
    std::vector<std::unique_ptr<BaseToken>> tokens {};
    std::string last_token { "<START>" };

    while(position < str.size())
    {
        if (Lexer::isWhitespace(currentChar()))             // whitespaces
        {
            tokens.emplace_back(std::make_unique<Token<std::string_view>>(consumeWhitespace()));
        }
        else if (std::isdigit(currentChar()))           // numerics
        {
            tokens.emplace_back(std::make_unique<Token<std::string_view>>(consumeNumber()));
        }
        else if (currentChar() == '"')                         // strings
        {
            tokens.emplace_back(std::make_unique<Token<std::string_view>>(consumeString()));
        }
        else if (currentChar() == '\'')                        // valid quote string start
        {
            if (Lexer::isValidSingleQuoteStringStart(tokens))
            {
                tokens.emplace_back(std::make_unique<Token<std::string_view>>(consumeString()));
            }
            else
            {
                tokens.emplace_back(std::make_unique<Token<std::string_view>>(consumeOperator()));
            }
        }
        else if (Lexer::isStartOfOperator(currentChar()))   // operator
        {
            tokens.emplace_back(std::make_unique<Token<std::string_view>>(consumeOperator()));
        }
        else                                                   // 404 - char does not exists (lol)
        {
            if (position < str.size())
            {
                std::cout << "Error: 404, char does not exists (" << currentChar() << ")." << "\n";
            }
        }
    }

    return { std::move(tokens), str };
}

char Tokenizer::currentChar()
{
    return str[position];
}

char Tokenizer::nextChar()
{
    return str[position + 1];
}

char Tokenizer::nextCharAt(int delta_index)
{
    return str[position + delta_index];
}

/**
 * consume char:
 * increments position & column
 * @returns last_token
 */
char Tokenizer::consumeChar()
{
    char last_token { currentChar() };
    position++;
    column++;
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
Token<std::string_view> Tokenizer::consumeNumber()
{
    Token<std::string_view> token { TokenType::NUMBER, "", position, column, line, false };

    std::string value { consumeChar() };

    // I
    while (std::isdigit(consumeChar()))
    {
        value += consumeChar();
    }

    // II
    if (currentChar() == '.' && std::isdigit(nextChar()))
    {
        value += consumeChar();
    }

    while (std::isdigit(consumeChar()))
    {
        value += consumeChar();
    }

    // III
    if (currentChar() == 'e' || currentChar() == 'E')
    {
        // scientific notation, e.g. 1e6 or 1e-6
        if (std::isdigit(nextChar()))
        {
            // e.g. 1e6
            value += consumeChar();
        } else if (nextChar() == '-')
        {
            // e.g. 1e-6
            value += consumeChar();
            value += consumeChar();
        }
    }

    // IV
    while (std::isdigit(consumeChar()))
    {
        value += consumeChar();
    }

    std::string_view _value { value };

    token.setValue(_value);
    token.setEnd(position);
    return token;
}

/**
 * This method handle all types of operators, including operators with many characters.
 */
Token<std::string_view> Tokenizer::consumeOperator()
{
    Token<std::string_view> op { TokenType::OPERATOR, "", position, column, line, true };
    std::string value { consumeChar() }; // consume leading char

    auto arr_begin { std::begin(Lexer::OPERATIONS) };
    auto arr_end { std::end(Lexer::OPERATIONS) };
    auto it { std::find(arr_begin, arr_end, std::string_view {value + currentChar()}) };

    while (currentChar() && it != arr_end)
    {
        value += consumeChar();
        it = std::find(arr_begin, arr_end, std::string_view {value + currentChar()});
    }

    // FIXME: Replace that line with the TokenType enum class.
    // op.setType(std::string (*it));  // i'm not sure about that
    op.setValue(std::move(value));
    op.setEnd(position);
    return op;
}

/**
 * handles strings, even with special whitespaces (e.g: \t)
 */
Token<std::string_view> Tokenizer::consumeString()
{
    Token<std::string_view> string { TokenType::STRING, "", position, column, line, false };
    char startChar { consumeChar() };
    std::string value {};

    while (currentChar() && currentChar() != startChar)
    {
        if (currentChar() == '\\')
        {
            consumeChar(); // consume escape char and get the next one
            char nextChar = consumeChar();
            if (nextChar == 'b')
            {
                value += "\b";
            }
            else if (nextChar == 'f')
            {
                value += "\f";
            }
            else if (nextChar == 'n')
            {
                value += "\n";
            }
            else if (nextChar == 'r')
            {
                value += "\r";
            }
            else if (nextChar == 't')
            {
                value += "\t";
            }
            else if (nextChar == 'v')
            {
                value += "\v";
            }
            else
            {
                value += nextChar;
            }
        }
        else
        {
            value += consumeChar();
        }
    }
    if (currentChar() != startChar)
    {
        // ERROR (string not terminated, only one quote)
        std::cout << "Error : string not terminated (" << currentChar() << ")\n";
    }
    else
    {
        consumeChar(); // consume final quote
    }
    string.setValue(std::string_view (value));
    string.setEnd(position);
    return string;
}

/**
 * Handles whitespaces and carriage returns
 */
Token<std::string_view> Tokenizer::consumeWhitespace()
{
    Token<std::string_view> whitespace { TokenType::WHITESPACE, "", position, column, line, false };
    std::string value {};

    while (currentChar() && Lexer::isWhitespace(currentChar()))
    {
        if (Lexer::isNewline(currentChar()))
        {
            column = 0;
            line++;
        }
        value += consumeChar();
    }

    std::string_view newValue{ std::move(value) };

    whitespace.setValue(newValue);
    whitespace.setEnd(position);

    return whitespace;
    //return { "WHITESPACE", std::string_view (value), position, column, line, false };
}
