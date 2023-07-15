#ifndef LEXER
#define LEXER

#include <array>  //temp
#include <string>  //temp

class Lexer
{
public:
    static std::array<std::string, 28> OPERATIONS
    {
        "+"s, "-"s, "*"s, "/"s, "%"s, "=="s, "!="s, ">"s, ">="s, "<"s, "<="s, "!"s, "||"s, "&&"s, "~"s, "|"s, "&"s,
        "^"s, "<<"s, ">>"s, "-b"s, "-c"s, "-d"s, "-e"s, "-r"s, "-w"s, "-x"s, "-s"s, "."s, ".."s, "\\"s, ":"s, "%"s,
        "|"s, "!"s, "?"s, "#"s, "&"s, "$"s, ";"s, ","s, "("s, ")"s, "{"s, "}"s, "["s, "]"s, "="s
    };
    static std::array<std::string, 10> FIGURES {"0"s, "1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s, "9"s};
    static std::array<std::string, 42> ALPHABET
    {
        "a"s, "b"s, "c"s, "d"s, "e"s, "f"s, "g"s, "h"s, "i"s, "j"s, "k"s, "l"s, "m"s, "n"s, "o"s, "p"s, "q"s, "r"s,
        "s"s, "t"s, "u"s, "v"s, "w"s, "x"s, "y"s, "z"s, "A"s, "B"s, "C"s, "D"s, "E"s, "F"s, "G"s, "H"s, "I"s, "J"s,
        "K"s, "L"s, "M"s, "N"s, "O"s, "P"s, "Q"s, "R"s, "S"s, "T"s, "U"s, "V"s, "W"s, "X"s, "Y"s, "Z"s
    };

    static bool isOperator(std::string c);
    static bool isWhitespace(std::string c);
    static bool isNewline(std::string c);
    static bool isNumeric(std::string c);
    static bool isAlpha(std::string c);
    static Tokens tokenize(std::string str);
private:
};

#endif //LEXER
