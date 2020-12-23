#include <cstddef>
#include <cstdlib>
#ifdef __STDC_HOSTED__
#include <iterator>
#include <stdexcept>
#include <vector>

using std::runtime_error;
using std::vector;
#else
#endif

using std::byte, std::to_integer;

#include "deflate.hpp"

namespace zlite {
static void Huffman_decode() {}

static unsigned short code_lengths[288];
struct range {
  unsigned short end, bit_length;
};
static range range[4]{{143, 8}, {255, 9}, {279, 7}, {287, 8}};
std::vector<byte> deflate::decompress() {
  using zlite::compression_mode;
  std::vector<byte> lol;

  for (const auto &block : blocks) {
    // while (!is_final_block) {
    switch (block.mode) {
    case compression_mode::None:
      unsigned short len = to_integer(block.data.at(0)) +
                           to_integer(block.data.at(1)),
                     nlen = to_integer(block.data.at(2)) +
                            to_integer(block.data.at(3));
      if (~len != nlen)
        throw new runtime_error("Wrong length in an uncompressed block." +
                                "\nExpected len:" + len + ", nlen:" + ~len +
                                "\nGot len:" + len + ", nlen:" + len + '\n');
      if (block.data.size() - 4 != len)
        throw runtime_error(
            "Length of uncompressed block does not equal actual size.");

      for (unsigned short i = 4; i < len; i++) {
        lol.emplace_back(block.data.at(i));
      }
      break;
    case compression_mode::With_dynamic_Huffman:
      break;
    case compression_mode::With_fixed_Huffman:
      break;
    default:
      throw new std::runtime_error("Invalid Deflate compression mode");
    }
    //}
  }

  return lol;
}
deflate::deflate(vector<byte>, compression_mode mode = compression_mode::None) {
  switch (mode) {
  case compression_mode::None:
      
    break;
  case compression_mode::With_dynamic_Huffman:
      break;
  case compression_mode::With_fixed_Huffman:
      break;
  default:
    throw std::invalid_argument("Invalid compression mode");
  }
}
deflate::deflate_block &deflate::operator[](const size_t index) {
  try {
    return blocks.at(index);
  } catch (std::out_of_range &e) {
    throw;
  }
}

const char *deflate::info() {}
} // namespace zlite
