#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <memory>
#include <string>
#include <vector>



template<typename FlagStructure = std::vector<std::string>>
struct CommandPattern
{
    explicit CommandPattern(std::string name, int position = 0, FlagStructure flags = {}) noexcept;

    bool Matches(const CommandPattern& pattern) const noexcept;

    const std::string& GetName() const noexcept;
    const std::string& GetUsage() const noexcept;
private:
    std::string m_name;
    int m_position;
    FlagStructure m_flags;
};


struct CommandContext
{
    std::vector<std::string> flags;
    std::vector<std::string> args;
};


template<std::size_t SubCommandsCount = 0, std::size_t FlagsCount = 0>
struct Command
{
public:
    using FixedCommandPattern = CommandPattern< std::array<std::string, FlagsCount>>;
    using SubCommands = std::array<std::unique_ptr<Command>, SubCommandsCount>;

    enum Output
    {
        WRONG_USAGE,
        INTERNAL_FAILURE,
        SUCCESS
    };

    explicit Command(FixedCommandPattern commandPattern, SubCommands subCommands = {}) noexcept;

    const FixedCommandPattern& GetPattern() const noexcept;
    constexpr std::size_t GetSubCommandsCount() const noexcept;
    constexpr std::size_t GetFlagsCount() const noexcept;

    void Execute(const CommandContext& context) const noexcept;
    virtual Output Run(const CommandContext& context) const noexcept = 0;
private:
    FixedCommandPattern m_pattern;
    SubCommands m_subCommands;
};


#include "../src/CommandComponents.inl"



#endif //COMMANDS_HPP