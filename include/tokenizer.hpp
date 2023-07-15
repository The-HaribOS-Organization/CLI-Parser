#ifndef TOKENIZER
#define TOKENIZER

#include <string>
#include <vector>

#include "token.hpp"

class Tokenizer
{
public:
    Tokenizer() = delete;
    Tokenizer(std::string& _str);

    Tokens tokenize();

    // Tokenizer utils

    Token makeToken(std::string type, std::string value, bool isOperator);
    std::string currentChar();
    std::string nextChar();
    std::string nextCharAt(int delta_index);
    std::string consumeChar();
    /**
     * Handles integers, floats and scientific numbers.
     */
    Token consumeNumber();
    /**
     * This method handle all type of operators, including operators with many characters.
     */
    Token consumeOperator();
    Token consumeString();
    /**
     * Handles whitespaces and carriage returns
     */
    Token consumeWhitespace();
private:
    std::string str;
    int position;
    int column;
    int line;
};

#endif //TOKENIZER
