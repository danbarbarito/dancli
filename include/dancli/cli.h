#pragma once

#include <memory>
#include <map>
#include <boost/program_options.hpp>

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
    boost::program_options::variables_map global_vm;
    int run(int argc, char *argv[]);
    void usage();
};

}
