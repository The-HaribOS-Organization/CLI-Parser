#ifndef TOKEN
#define TOKEN

#include <string>
#include <string_view>
#include <vector>


class BaseToken
{
public:
    BaseToken() = delete;
    BaseToken(std::string _type,
              int _position,  // Token.start and Token.end are defined by _position
              int _column,
              int _line,
              bool _isOperator
              ) noexcept;

    BaseToken(BaseToken&& other) noexcept;
    BaseToken& operator=(const BaseToken& other) = default;

    virtual ~BaseToken() noexcept = default;

    void setType(std::string new_type);
    void setEnd(int new_end);

    [[nodiscard]] std::string getType() const noexcept;
    [[nodiscard]] int getStart() const noexcept;
    [[nodiscard]] int getEnd() const noexcept;
    [[nodiscard]] int getColumn() const noexcept;
    [[nodiscard]] int getLine() const noexcept;
    [[nodiscard]] bool getIsOperator() const noexcept;
private:
    std::string type;
    int start;
    int end;
    int column;
    int line;
    bool isOperator;
};

template<class T>
class Token : public BaseToken
{
public:
    Token() = delete;
    Token(std::string _type,
          T _value,
          int _position,
          int _column,
          int _line,
          bool _isOperator) noexcept;

    Token(Token&& other) noexcept;
    Token& operator=(const Token& other) = default;

    ~Token() noexcept override;

    void setValue(T new_value);
    T getValue() const noexcept;
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
    Tokens() = delete;
    Tokens(std::vector<BaseToken*> _tokens,
           std::vector<BaseToken*> _consumed,
           std::string str) noexcept;
private:
    std::vector<BaseToken*> tokens;
    std::vector<BaseToken*> consumed;
    std::string str;
};

#endif //TOKEN
