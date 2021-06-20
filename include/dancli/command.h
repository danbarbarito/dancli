#pragma once

#include <boost/program_options.hpp>

namespace dancli {

class Command
{
public:
    virtual void help() {};
    virtual void parse(boost::program_options::parsed_options parsed) {};
    virtual void run() {};
};

}
