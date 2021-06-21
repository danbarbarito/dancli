#include <iostream>
#include <string>

#include <dancli/cli.h>
#include <dancli/command.h>

namespace po = boost::program_options;

class SpeakCommand : public dancli::Command {
public:
    SpeakCommand() {
        this->command_options = std::make_shared<po::options_description>("speak options");
        this->command_options->add_options()
                ("person", po::value<std::string>()->default_value("Dan"), "Person who is speaking");
    }
    void run() {
        std::string person = this->command_vm["person"].as<std::string>();
        std::cout << person << ": Hi!" << std::endl;
    };
};

int main(int argc, char *argv[])
{
    dancli::CLI cli("example1", "example description");
    cli.add_command<SpeakCommand>("speak", "have a person say something to the user");
    return cli.run(argc, argv);
}
