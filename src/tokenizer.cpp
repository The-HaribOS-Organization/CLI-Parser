#include <array>
#include <iostream>

#include "lexer.hpp"
#include "tokenizer.hpp"


Tokenizer::Tokenizer(std::string _str) : str(std::move(_str)), position(0), column(0), line(1)
{
}

/**
 * method to call for use this tokenizer
 */
Tokens Tokenizer::tokenize()
{
    std::vector<BaseToken*> tokens {};
    std::string last_token { "<START>" };

    while(position < str.size())
    {
        if (Lexer::isWhitespace(currentChar()))             // whitespaces
        {
            auto token { consumeWhitespace() };
            tokens.emplace_back(&token);
        }
        else if (Lexer::isNumeric(currentChar()))           // numerics
        {
            auto token { consumeNumber() };
            tokens.emplace_back(&token);
        }
        else if (currentChar() == '"')                         // strings
        {
            auto token { consumeString() };
            tokens.emplace_back(&token);
        }
        else if (currentChar() == '\'')                        // valid quote string start
        {
            if (Lexer::isValidSingleQuoteStringStart(tokens))
            {
                auto token { consumeString() };
                tokens.emplace_back(&token);
            }
            else
            {
                auto token { consumeOperator() };
                tokens.emplace_back(&token);
            }
        }
        else if (Lexer::isStartOfOperator(currentChar()))   // operator
        {
            auto token { consumeOperator() };
            tokens.emplace_back(&token);
        }
        else                                                   // 404 - char does not exists (lol)
        {
            if (position < str.size())
            {
                std::cout << "Error: 404, char does not exists (" << currentChar() << ")." << "\n";
            }
        }
    }

    Tokens tokens_set { tokens, std::vector<BaseToken*> {}, str };
    return tokens_set;
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
    Token<std::string_view> token { "NUMBER", "", position, column, line, false };

    std::string value { consumeChar() };

    // I
    while (Lexer::isNumeric(consumeChar()))
    {
        value += consumeChar();
    }

    // II
    if (currentChar() == '.' && Lexer::isNumeric(nextChar()))
    {
        value += consumeChar();
    }

    while (Lexer::isNumeric(consumeChar()))
    {
        value += consumeChar();
    }

    // III
    if (currentChar() == 'e' || currentChar() == 'E')
    {
        // scientific notation, e.g. 1e6 or 1e-6
        if (Lexer::isNumeric(nextChar()))
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
    while (Lexer::isNumeric(consumeChar()))
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
    Token<std::string_view> op { "", "", position, column, line, true };
    std::string value { consumeChar() }; // consume leading char

    auto arr_begin { std::begin(Lexer::OPERATIONS) };
    auto arr_end { std::end(Lexer::OPERATIONS) };
    auto it { std::find(arr_begin, arr_end, std::string_view {value + currentChar()}) };

    while (currentChar() && it != arr_end)
    {
        value += consumeChar();
        it = std::find(arr_begin, arr_end, std::string_view {value + currentChar()});
    }

    std::string_view _value { value };

    op.setType(std::string (*it));  // i'm not sure about that
    op.setValue(_value);
    op.setEnd(position);
    return op;
}

/**
 * handles strings, even with special whitespaces (e.g: \t)
 */
Token<std::string_view> Tokenizer::consumeString()
{
    Token<std::string_view> string { "STRING", "", position, column, line, false };
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
    Token<std::string_view> whitespace { "WHITESPACE", "", position, column, line, false };
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

    whitespace.setValue(std::string_view (value));
    whitespace.setEnd(position);
    return whitespace;
    //return { "WHITESPACE", std::string_view (value), position, column, line, false };
}
