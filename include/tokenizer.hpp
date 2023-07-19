#ifndef TOKENIZER
#define TOKENIZER

#include <string>
#include <vector>

#include "token.hpp"

class Tokenizer
{
public:
    Tokenizer() = delete;
    Tokenizer(std::string _str);

    Tokens tokenize();

    // Tokenizer utils

    char currentChar();
    char nextChar();
    char nextCharAt(int delta_index);
    char consumeChar();
    /**
     * Handles integers, floats and scientific numbers.
     */
    Token<std::string_view> consumeNumber();
    /**
     * This method handle all type of operators, including operators with many characters.
     */
    Token<std::string_view> consumeOperator();
    Token<std::string_view> consumeString();
    /**
     * Handles whitespaces and carriage returns
     */
    Token<std::string_view> consumeWhitespace();
private:
    std::string str;
    int position;
    int column;
    int line;
};

#endif //TOKENIZER
