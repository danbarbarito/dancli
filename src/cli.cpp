#include <dancli/cli.h>


#include <iostream>
#include <string>
#include <memory>

namespace po = boost::program_options;

dancli::CLI::CLI(std::string program_name, std::string program_description)
{
    this->program_name = program_name;
    this->program_description = program_description;
    this->global_options = std::make_unique<po::options_description>("Global options");
    this->global_options->add_options()
            ("debug", "Turn on debug output")
            ("help,h", "show help menu")
            ("command", po::value<std::string>(), "command to execute")
            ("args", po::value<std::vector<std::string> >(), "Arguments for command");
}

int dancli::CLI::run(int argc, char *argv[]) {
    po::positional_options_description pos;
    pos.add("command", 1).
            add("args", -1);

    this->global_parsed = std::make_unique<boost::program_options::parsed_options>(po::command_line_parser(argc, argv).
                                                                                   options(*this->global_options).
                                                                                   positional(pos).
                                                                                   allow_unregistered().
                                                                                   run());

    po::store(*this->global_parsed, this->global_vm);

    return this->process();
}

void dancli::CLI::usage() {
    std::cout << this->program_name << " - " << this->program_description << std::endl;
    std::cout << std::endl;
    std::cout << "usage:" << std::endl;
    std::cout << this->program_name << " ";
    for (auto& i : this->global_options->options()) {
        std::string option_name =  i->long_name();
        std::string option_format_name = i->format_name();
        std::string option_format_parameter = i->format_parameter();
        if (option_name != "command" && option_name != "args") {
            std::cout << "[" << option_format_name;
            if (!option_format_parameter.empty()) {
                std::cout << " " << option_format_parameter;
            }
            std::cout << "] ";
        }
    }
    std::cout <<  "<command> [<command-options>] [<args>]" << std::endl;
    std::cout << std::endl;
    std::cout << "commands:" << std::endl;
    std::cout << "help - show help menu" << std::endl;
    for (auto& i : this->commands) {
        std::cout << i->command_name << " - " << i->command_description << std::endl;
    }
    std::cout << std::endl;
    std::cout << "options:" << std::endl;
    for (auto& i : this->global_options->options()) {
        std::string option_name =  i->long_name();
        std::string option_format_name = i->format_name();
        std::string option_format_parameter = i->format_parameter();
        if (option_name != "command" && option_name != "args") {
            std::cout << option_format_name;
            if (!option_format_parameter.empty()) {
                std::cout << " " << option_format_parameter;
            }
            std::cout << " - " << i->description() << std::endl;
        }
    }
}

int dancli::CLI::process() {
    bool help = this->global_vm.count("help") > 0;

    std::string command;
    if (this->global_vm.count("command") > 0) {
        command = this->global_vm["command"].as<std::string>();
    }

    if (!command.empty()) {
        if (command == "help") {
            this->usage();
            return 0;
        }
        for (auto& i : this->commands) {
            if (i->command_name == command) {
                if (help) {
                    i->usage();
                    return 0;
                } else {
                    i->parse(*this->global_parsed);
                    i->run();
                    return 0;
                }
            }
        }

        // If we get to this point, no valid command was found
        this->usage();
        std::cerr << std::endl << "Error: Unknown command '" << command << "'" << std::endl;
        return 1;
    }



    if (help) {
        this->usage();
    } else {
        // If we get to this point, no command was entered
        // TODO Allow user to set the default action that occurs when no command was entered
        this->usage();
    }
    return 0;
}
