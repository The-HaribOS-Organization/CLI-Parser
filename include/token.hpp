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


class BaseToken
{
public:
    constexpr BaseToken(TokenType _type, int _position, int _column, int _line, bool _isOperator) noexcept;

    constexpr BaseToken& operator=(const BaseToken& other) = default;
    constexpr BaseToken(const BaseToken& other) = default;
    constexpr BaseToken(BaseToken&& other) noexcept = default;
    constexpr BaseToken& operator=(BaseToken&& other) noexcept = default;

    virtual ~BaseToken() noexcept = default;

    void setType(TokenType new_type);
    void setEnd(int new_end);

    [[nodiscard]] constexpr TokenType getType() const noexcept;
    [[nodiscard]] constexpr int getStart() const noexcept;
    [[nodiscard]] constexpr int getEnd() const noexcept;
    [[nodiscard]] constexpr int getColumn() const noexcept;
    [[nodiscard]] constexpr int getLine() const noexcept;
    [[nodiscard]] constexpr bool getIsOperator() const noexcept;
private:
    TokenType type;
    int start;
    int end;
    int column;
    int line;
    bool isOperator;
};

template<class T>
concept CorrectTokenType = std::is_same_v<T, char> || std::is_same_v<T, std::string_view>;

template<CorrectTokenType T>
class Token : public BaseToken
{
public:
    Token() = delete;
    constexpr Token(TokenType _type, T _value, int _position, int _column, int _line, bool _isOperator) noexcept;

    constexpr Token(const Token& other) = default;
    constexpr Token& operator=(const Token& other) = default;
    constexpr Token(Token&& other) noexcept = default;
    constexpr Token& operator=(Token&& other) noexcept = default;

    constexpr ~Token() noexcept override = default;

    void setValue(T new_value);
    const T& getValue() const noexcept;
private:
    T value;
};


/// DISCLAIMER : this class isn't finished yet.

/**
 * set of tokens
 */
class Tokens
{
public:
    Tokens(std::vector<std::unique_ptr<BaseToken>>&& _tokens, std::string_view _str) noexcept;
private:
    std::vector<std::unique_ptr<BaseToken>> tokens;
    std::string_view str;
};

#endif //TOKEN
