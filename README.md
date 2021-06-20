# dancli - C++ library to quickly and easily create command line applications

```c++
#include <dancli/cli.h>

int main(int argc, char *argv[])
{
    dancli::CLI cli("example1", "example description");
    return cli.run(argc, argv);
}
```

```
> ./example1 --help

example1 - example description

usage:
example1 [--debug] [-h [ --help ]] <command> [<command-options>] [<args>]

commands:
help - show help menu

options:
--debug - Turn on debug output
-h [ --help ] - show help menu
```

## Dependencies

1. Boost

## Building

1. `git clone --recursive https://github.com/danbarbarito/dancli.git`
2. `cd dancli`
3. `mkdir build && cd build/`
4. `cmake .`
5. `make`
6. `make install`

## Usage

Check out the "examples/" directory for more in-depth examples.
