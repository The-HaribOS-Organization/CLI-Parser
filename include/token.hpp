#ifndef TOKEN
#define TOKEN

#include <string>
#include <string_view>
#include <vector>
#include <memory>


enum class TokenType
{
    CHAR,
    NUMBER,
    OPERATOR,
    STRING,
    WHITESPACE
};

class Token
{
public:
    Token() = delete;
    Token(TokenType _type, std::string_view _value, int _position, int _column, int _line, bool _isOperator) noexcept;

    Token(const Token& other) = default;
    Token& operator=(const Token& other) = default;
    Token(Token&& other) noexcept = default;
    Token& operator=(Token&& other) noexcept = default;

    void setType(TokenType new_type);
    void setEnd(int new_end);

    [[nodiscard]] TokenType getType() const noexcept;
    [[nodiscard]] int getStart() const noexcept;
    [[nodiscard]] int getEnd() const noexcept;
    [[nodiscard]] int getColumn() const noexcept;
    [[nodiscard]] int getLine() const noexcept;
    [[nodiscard]] bool getIsOperator() const noexcept;

    void setValue(std::string_view new_value);
    [[nodiscard]] const std::string_view& getValue() const noexcept;
private:
    TokenType type;
    int start;
    int end;
    int column;
    int line;
    bool isOperator;
    std::string_view value;
};


/// DISCLAIMER : this class isn't finished yet.

/**
 * set of tokens
 */
class Tokens
{
public:
    Tokens(std::vector<Token>&& _tokens, std::string_view _str) noexcept;
private:
    std::vector<Token> tokens;
    std::string_view str;
};

#endif //TOKEN
