#ifndef TOKEN
#define TOKEN

#include <string>
#include <vector>


/// DISCLAIMER : these classes aren't finished yet.

class Token
{
public:
    Token() = delete;
    Token(const std::string& _type,
          const std::string& _value,
          int _position,  // Token.start and Token.end are defined by _position
          int _column,
          int _line,
          bool _isOperator
          ) noexcept;

    void setType(std::string new_type);
    void setValue(std::string new_value);
    void setEnd(int new_end);

    std::string getType() const noexcept;
    std::string getValue() const noexcept;
    int getStart() const noexcept;
    int getEnd() const noexcept;
    int getColumn() const noexcept;
    int getLine() const noexcept;
    bool getIsOperator() const noexcept;
private:
    std::string type;
    std::string value;
    int start;
    int end;
    int column;
    int line;
    bool isOperator;
};

/**
 * set of tokens
 */
class Tokens
{
public:
    Tokens() = delete;
    Tokens(std::vector<Token> _tokens, std::vector<Token> _consumed, std::string& str) noexcept;
private:
    std::vector<Token> tokens;
    std::vector<Token> _consumed;
    std::string str;
};

#endif //TOKEN
