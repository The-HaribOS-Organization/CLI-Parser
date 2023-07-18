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
    static constexpr const std::array<char, 10> FIGURES {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    static constexpr const std::array<char, 52> ALPHABET
    {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    static bool isOperator(std::string_view c);
    static bool isStartOfOperator(char c);
    static bool isWhitespace(char c);
    static bool isNewline(char c);
    static bool isNumeric(char c);
    static bool isAlpha(char c);
    static bool isValidSingleQuoteStringStart(std::vector<BaseToken*> tokens);
    static Tokens tokenize(std::string str);
private:
};

#endif //LEXER
