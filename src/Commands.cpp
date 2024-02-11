#include "../include/Commands.hpp"

#include <iostream>



TestCommand::TestCommand() noexcept : Command(Command::FixedCommandPattern("test")) {}

Command<>::Output TestCommand::Run(const CommandContext &context) const noexcept
{
    std::cout << "Nice one." << std::endl;
    return SUCCESS;
}
