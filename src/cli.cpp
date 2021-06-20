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

    po::parsed_options parsed = po::command_line_parser(argc, argv).
            options(*this->global_options).
            positional(pos).
            allow_unregistered().
            run();

    po::store(parsed, this->global_vm);

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
        if (option_name != "command" && option_name != "args") {
            std::cout << "[" << option_format_name << "] ";
        }
    }
    std::cout <<  "<command> [<command-options>] [<args>]" << std::endl;
    std::cout << std::endl;
    std::cout << "commands:" << std::endl;
    //    std::cout << "help - show help menu" << std::endl;
    //    std::cout << "import <path...> - import csv of transactions" << std::endl;
    //    std::cout << "server - http server to serve REST API and UI" << std::endl;
    //    std::cout << "rebuild - rebuild database schema" << std::endl;
    //    std::cout << "verify - verify integrity of database" << std::endl;
    std::cout << std::endl;
    std::cout << "options:" << std::endl;
    for (auto& i : this->global_options->options()) {
        std::string option_name =  i->long_name();
        std::string option_format_name = i->format_name();
        if (option_name != "command" && option_name != "args") {
            std::cout << option_format_name << " - " << i->description() << std::endl;
        }
    }
}

int dancli::CLI::process() {
    bool help = this->global_vm.count("help") > 0;

    std::string command = "help";
    if (this->global_vm.count("command") > 0) {
        command = this->global_vm["command"].as<std::string>();
    }

//    std::unique_ptr<billz::command::Command> commandInstance;

//    if (command == "rebuild") {
//        commandInstance = std::make_unique<billz::command::Rebuild>();
//    } else if(command == "help") {
//        print_usage();
//        return 0;
//    } else {
//        std::cerr << "Error: Unknown command '" << command << "'" << std::endl;
//        return 1;
//    }

    if (help) {
        if (this->global_vm.count("command") > 0) {
//            commandInstance->help();
            return 0;
        } else {
            this->usage();
            return 0;
        }
    }

//    commandInstance->parse(parsed);
//    commandInstance->run();
    return 0;
}
