#ifndef LEXER
#define LEXER

#include <array>  //temp
#include <string>  //temp

class Lexer
{
public:
    static std::array<std::string, 28> OPERATIONS
    {
        std::string {"+"}, std::string {"-"}, std::string {"*"}, std::string {"/"}, std::string {"%"},
        std::string {"=="}, std::string {"!="}, std::string {">"}, std::string {">="}, std::string {"<"},
        std::string {"<="}, std::string {"!"}, std::string {"||"}, std::string {"&&"}, std::string {"~"},
        std::string {"|"}, std::string {"&"}, std::string {"^"}, std::string {"<<"}, std::string {">>"},
        std::string {"-b"}, std::string {"-c"}, std::string {"-d"}, std::string {"-e"}, std::string {"-r"},
        std::string {"-w"}, std::string {"-x"}, std::string {"-s"}, std::string {"."}, std::string {".."},
        std::string {"\\"}, std::string {":"}, std::string {"%"}, std::string {"|"}, std::string {"!"},
        std::string {"?"}, std::string {"#"}, std::string {"&"}, std::string {"$"}, std::string {";"},
        std::string {","}, std::string {"("}, std::string {")"}, std::string {"{"}, std::string {"}"},
        std::string {"["}, std::string {"]"}, std::string {"="}
    };
    static std::array<std::string, 10> FIGURES
    {
        std::string {"0"}, std::string {"1"}, std::string {"2"}, std::string {"3"}, std::string {"4"},
        std::string {"5"}, std::string {"6"}, std::string {"7"}, std::string {"8"}, std::string {"9"}
    };
    static std::array<std::string, 42> ALPHABET
    {
        std::string {"a"}, std::string {"b"}, std::string {"c"}, std::string {"d"}, std::string {"e"},
        std::string {"f"}, std::string {"g"}, std::string {"h"}, std::string {"i"}, std::string {"j"},
        std::string {"k"}, std::string {"l"}, std::string {"m"}, std::string {"n"}, std::string {"o"},
        std::string {"p"}, std::string {"q"}, std::string {"r"}, std::string {"s"}, std::string {"t"},
        std::string {"u"}, std::string {"v"}, std::string {"w"}, std::string {"x"}, std::string {"y"},
        std::string {"z"}, std::string {"A"}, std::string {"B"}, std::string {"C"}, std::string {"D"},
        std::string {"E"}, std::string {"F"}, std::string {"G"}, std::string {"H"}, std::string {"I"},
        std::string {"J"}, std::string {"K"}, std::string {"L"}, std::string {"M"}, std::string {"N"},
        std::string {"O"}, std::string {"P"}, std::string {"Q"}, std::string {"R"}, std::string {"S"},
        std::string {"T"}, std::string {"U"}, std::string {"V"}, std::string {"W"}, std::string {"X"},
        std::string {"Y"}, std::string {"Z"}
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
