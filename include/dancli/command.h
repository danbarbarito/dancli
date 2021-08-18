#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <string>

#include <boost/program_options.hpp>

namespace dancli {

class Command
{
public:
    std::string program_name;
    std::string command_name;
    std::string command_description;
    std::string additional_usage;
    std::shared_ptr<boost::program_options::options_description> command_options;
    boost::program_options::variables_map command_vm;
    boost::program_options::variables_map global_vm;
    std::vector<std::string> command_args;
    void parse(boost::program_options::parsed_options parsed, boost::program_options::variables_map global_vm) {
        std::vector<std::string> opts = boost::program_options::collect_unrecognized(parsed.options, boost::program_options::include_positional);
        opts.erase(opts.begin());
        boost::program_options::store(boost::program_options::command_line_parser(opts).options(*this->command_options).run(), this->command_vm);
        this->global_vm = global_vm;
    };
    void usage() {
        std::cout << this->program_name << " " << this->command_name << " - " << this->command_description << std::endl;
        std::cout << std::endl;
        std::cout << "usage:" << std::endl;
        std::cout << this->program_name << " " << this->command_name << " ";
        for (auto& i : this->command_options->options()) {
            std::cout << "[" << i->format_name() << " " << i->format_parameter() << "] ";
        }
        std::cout << this->additional_usage << std::endl << std::endl;
        std::cout << "options:" << std::endl;
        for (auto& i : this->command_options->options()) {
            std::string option_name =  i->long_name();
            std::string option_format_name = i->format_name();
            std::string option_format_parameter = i->format_parameter();
            std::cout << option_format_name;
            if (!option_format_parameter.empty()) {
                std::cout << " " << option_format_parameter;
            }
            std::cout << " - " << i->description() << std::endl;
        }
    };
    virtual void run() {};
};

}
