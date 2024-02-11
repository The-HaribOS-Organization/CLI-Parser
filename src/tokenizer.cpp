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
    std::vector<Token> tokens {};
    std::string last_token { "<START>" };

    while(position < str.size())
    {
        if (Lexer::isWhitespace(currentChar()))             // whitespaces
        {
            tokens.emplace_back(consumeWhitespace());
        }
        else if (std::isdigit(currentChar()))           // numerics
        {
            tokens.emplace_back(consumeNumber());
        }
        else if (currentChar() == '"')                         // strings
        {
            tokens.emplace_back(consumeString());
        }
        else if (currentChar() == '\'')                        // valid quote string start
        {
            if (Lexer::isValidSingleQuoteStringStart(tokens))
            {
                tokens.emplace_back(consumeString());
            }
            else
            {
                tokens.emplace_back(consumeOperator());
            }
        }
        else if (Lexer::isStartOfOperator(currentChar()))   // operator
        {
            tokens.emplace_back(consumeOperator());
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
Token Tokenizer::consumeNumber()
{
    Token token { TokenType::NUMBER, "", position, column, line, false };

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

    token.setValue(std::move(value));
    token.setEnd(position);
    return token;
}

/**
 * This method handle all types of operators, including operators with many characters.
 */
Token Tokenizer::consumeOperator()
{
    Token op { TokenType::OPERATOR, "", position, column, line, true };
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
Token Tokenizer::consumeString()
{
    Token string { TokenType::STRING, "", position, column, line, false };
    char startChar { consumeChar() };
    std::string value {};

    while (currentChar() && currentChar() != startChar)
    {
        if (currentChar() == '\\')
        {
            consumeChar(); // consume escape char and get the next one
            char nextChar = consumeChar();

            switch (nextChar)
            {
                case 'b':
                    value += "\b";
                    break;
                case 'f':
                    value += "\f";
                    break;
                case 'n':
                    value += "\n";
                    break;
                case 'r':
                    value += "\r";
                    break;
                case 't':
                    value += "\t";
                    break;
                case 'v':
                    value += "\v";
                    break;
                default:
                    value += nextChar;
                    break;
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
Token Tokenizer::consumeWhitespace()
{
    Token whitespace { TokenType::WHITESPACE, "", position, column, line, false };
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

    whitespace.setValue(std::move(value));
    whitespace.setEnd(position);

    return whitespace;
    //return { "WHITESPACE", std::string_view (value), position, column, line, false };
}
