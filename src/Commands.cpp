#include "../include/Commands.hpp"

#include <iostream>



TestCommand::TestCommand() noexcept : Command(Command::FixedCommandPattern("test")) {}

Command<>::Output TestCommand::Run(const CommandContext &context) const noexcept
{
    std::cout << "Changed this message so that I can create a new pull request." << std::endl;
    return SUCCESS;
}
