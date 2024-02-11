#include <algorithm>
#include <iostream>



template<typename FlagStructure>
CommandPattern<FlagStructure>::CommandPattern(std::string name, int position, FlagStructure flags) noexcept
        : m_name(std::move(name)), m_position(position), m_flags(std::move(flags)) {}

template<typename FlagStructure>
bool CommandPattern<FlagStructure>::Matches(const CommandPattern &pattern) const noexcept
{
    return m_name == pattern.m_name
           && m_position == pattern.m_position
           && std::all_of(std::begin(pattern.m_flags), std::end(pattern.m_flags), [this](const std::string& flag)
    {
        return std::find(std::begin(m_flags), std::end(m_flags), flag) != std::end(m_flags);
    });
}

template<typename FlagStructure>
const std::string &CommandPattern<FlagStructure>::GetName() const noexcept
{
    return m_name;
}

template<typename FlagStructure>
const std::string &CommandPattern<FlagStructure>::GetUsage() const noexcept
{
    return "Future auto-building usage...";
}


template<std::size_t SubCommandsCount, std::size_t FlagsCount>
Command<SubCommandsCount, FlagsCount>::Command(FixedCommandPattern commandPattern, Command::SubCommands subCommands) noexcept
        : m_pattern(std::move(commandPattern)), m_subCommands(std::move(subCommands)) {}

template<std::size_t SubCommandsCount, std::size_t FlagsCount>
const Command<SubCommandsCount, FlagsCount>::FixedCommandPattern &Command<SubCommandsCount, FlagsCount>::GetPattern() const noexcept
{
    return m_pattern;
}

template<std::size_t SubCommandsCount, std::size_t FlagsCount>
constexpr std::size_t Command<SubCommandsCount, FlagsCount>::GetSubCommandsCount() const noexcept
{
    return SubCommandsCount;
}

template<std::size_t SubCommandsCount, std::size_t FlagsCount>
constexpr std::size_t Command<SubCommandsCount, FlagsCount>::GetFlagsCount() const noexcept
{
    return FlagsCount;
}

template<std::size_t SubCommandsCount, std::size_t FlagsCount>
void Command<SubCommandsCount, FlagsCount>::Execute(const CommandContext &context) const noexcept
{
    switch (Run(context))
    {
        case WRONG_USAGE:
            std::cout << "Wrong usage for command \"" << m_pattern.GetName() << "\"."
                                                                                "\nCorrect usage: " << m_pattern.GetUsage() << std::endl;
            break;
        case INTERNAL_FAILURE:
            std::cout << "An internal failure has occurred while performing \"" << m_pattern.GetName() << "\" command."
                      << std::endl;
            break;
    }
}