#ifndef LEXER
#define LEXER

#include <array>  //temp
#include <memory>
#include <string>  //temp
#include <string_view>  //temp
#include <vector>  //temp

#include "token.hpp"

class Lexer
{
public:
    static constexpr std::array<std::string_view, 48> OPERATIONS
    {
        "+", "-", "*", "/", "%", "==", "!=", ">", ">=", "<", "<=", "!", "||",
        "&&", "~", "|", "&", "^", "<<", ">>",
        "-b", "-c", "-d", "-e", "-r", "-w", "-x", "-s", ".", "..", "\\", ":", "%", "|", "!", "?", "#", "&", "$", ";",
        ",", "(", ")", "{", "}", "[", "]", "="
    };

    static constexpr bool isOperator(std::string_view c);
    static constexpr bool isStartOfOperator(char c);
    static constexpr bool isWhitespace(char c);
    static constexpr bool isNewline(char c);
    static bool isValidSingleQuoteStringStart(const std::vector<std::unique_ptr<BaseToken>>& tokens);
    static Tokens tokenize(std::string&& str);
private:
};

#endif //LEXER
