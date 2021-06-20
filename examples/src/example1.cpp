#include <iostream>
#include <string>

#include <dancli/cli.h>

int main(int argc, char *argv[])
{
    dancli::CLI cli("example1", "example description");
    return cli.run(argc, argv);
}
