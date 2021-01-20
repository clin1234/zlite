The zlite library is inspired by Mark Adler's venerable zlib library and as
the implies, serves as a lightweight drop-in replacement, both in terms of
binary and source code size. It intends to conform to RFCs 1950-1952.

# Build Instructions
For the moment, only CMake is supported. At the moment, a C++17 compiler
is required.

## Instructions
The following configs are supported:
* Debug
* MinSizeRel
* RelWithDebInfo

1. Run `cmake -DCMAKE_BUILD_TYPE=<config>` to generate native build files,
or `cmake -G<generator> -DCMAKE_BUILD_TYPE=<config>` for a specific build system.
2. Build using the generated build files, or run
`cmake --build . -DCMAKE_BUILD_TYPE=<config>`.

## Copyright
(C) 2019 under the MPL 2.0.

## Authors
Charlie Lin

## TODO:
### Primary:
- [ ] Convert build system to CMake?
- [ ] Gzip compression/decompression
- [ ] Implement zlib-compatible shim

### Secondary:
- [ ] Test against other projects
- [ ] Support older compilers?
