The zlite library is inspired by Mark Adler's venerable zlib library and as
the implies, serves as a lightweight drop-in replacement, both in terms of
binary and source code size. It intends to conform to RFCs 1950-1952.

# Build Instructions
## Unix-like OS
Build prerequisites:
* Compiler and library conformant to C99 standard
* make

Steps:
1. Execute `configure.sh`.
2. Type `make` to build zlite. See all options available by typing `make help`.

## Windows
If you are building it on Cygwin or MSYS, see
[link](# "instructions for Unix-like OSes").
This assumes that you use the Visual Studio IDE or the Build Tools for Visual
Studio.

Build prerequisites:
*
* nmake

Steps:
1. Execute `configure.sh`.
2. Type `make` to build zlite. See all options available by typing `make help`.

## OpenVMS
Coming soon...

## Cross-compiling

# Copyright
(C) 2019 under the MPL 2.0.

# Authors
Charlie Lin
