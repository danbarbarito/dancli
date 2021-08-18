# dancli - C++ library to quickly and easily create command line applications

```c++
#include <iostream>
#include <string>
#include <vector>

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
        std::vector<std::string> args = this->global_vm["args"].as<std::vector<std::string>>();
        std::string statement = args.size() > 0 ? args[0] : "Hi!";
        std::cout << person << ": " << statement << std::endl;
    };
};

int main(int argc, char *argv[])
{
    dancli::CLI cli("example1", "example description");
    cli.add_command<SpeakCommand>("speak", "have a person say something to the user", "<statement>");
    return cli.run(argc, argv);
}


```

```
> myapp --help

myapp - description for myapp

usage:
myapp [--debug] [-h [ --help ]] <command> [<command-options>] [<args>]

commands:
help - show help menu
speak - have a person say something to the user

options:
--debug - Turn on debug output
-h [ --help ] - show help menu
```

```
> myapp speak --help

myapp speak - have a person say something to the user

usage:
myapp speak [--person arg (=Dan)]

options:
--person arg (=Dan) - Person who is speaking
```

```
> myapp speak --person=Steve

Steve: Hi!
```

## Dependencies

1. Boost

## Building

1. `git clone --recursive https://github.com/danbarbarito/dancli.git`
2. `cd dancli`
3. `mkdir build && cd build/`
4. `cmake ..`
5. `make`
6. `make install`

## Usage

Check out the "examples/" directory for more in-depth examples.
