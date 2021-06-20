# dancli - C++ library to quickly and easily create command line applications

This library is basically just a wrapper for `boost::program_options`

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

```c++
#include <dancli/cli.h>

int main(int argc, char *argv[])
{
    dancli::CLI cli("example1", "example description");
    return cli.run(argc, argv);
}
```

Check out the "examples/" directory for more in-depth examples.
