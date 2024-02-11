#ifndef CLI_PARSER_COMMANDS_HPP
#define CLI_PARSER_COMMANDS_HPP

#include "CommandComponents.hpp"

#include <array>



struct TestCommand : public Command<>
{
    TestCommand() noexcept;

    Output Run(const CommandContext& context) const noexcept final;
};



#endif //CLI_PARSER_COMMANDS_HPP
