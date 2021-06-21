#pragma once

#include <memory>
#include <vector>

#include <boost/program_options.hpp>

#include <dancli/command.h>

namespace dancli {

class CLI
{
private:
    int process();
public:
    CLI(std::string program_name, std::string program_description);
    std::string program_name;
    std::string program_description;
    std::unique_ptr<boost::program_options::options_description> global_options;
    std::unique_ptr<boost::program_options::parsed_options> global_parsed;
    boost::program_options::variables_map global_vm;
    std::vector<std::shared_ptr<dancli::Command>> commands;

    int run(int argc, char *argv[]);

    template<class CommandClass>
    void add_command(std::string command_name, std::string command_description) {
        std::shared_ptr<CommandClass> command = std::make_shared<CommandClass>();
        command->program_name = this->program_name;
        command->command_name = command_name;
        command->command_description = command_description;
        this->commands.push_back(command);
    };

    void usage();
};

}
