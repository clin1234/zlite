#include <iostream>
#include <array>
#include <span>
#include <initializer_list>
#include <utility>
#include <cstring>
#include <cassert>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "../adler32.hpp"

int main()
{
    using std::ifstream, std::ios;
    namespace fs = std::filesystem; using fs::path, fs::file_size;
    
    ifstream f("ls-lrRt.txt.gz", ios::binary);
    const auto & size {file_size(path("ls-lrRt.txt.gz"))};
    std::vector<unsigned char> ff(size);
    std::copy(std::istream_iterator<unsigned char>(f), 
              std::istream_iterator<unsigned char>(), std::back_inserter(ff));
    std::cout << "File from Adler-32: " << zlite::adler32(ff) << '\n';
    
    constexpr unsigned char test_string[] {"This is a very long string to test as well."};
    std::array a  {std::to_array(test_string)};
    std::span s {a};
    std::cout << "Plain uchar array: " << zlite::adler32(test_string) << '\n'
               << "Array: " << zlite::adler32(a) << '\n'
               << "Init list" << adler32(0,test_string, sizeof test_string) << '\n'
               << "Span: " << zlite::adler32(s) << '\n';
               
}
