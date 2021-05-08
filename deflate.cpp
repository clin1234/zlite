#include <cstddef>
#include <cstdlib>
#ifdef __STDC_HOSTED__
#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

using std::for_each_n, std::advance;
using std::runtime_error;
using std::uint16_t;
using std::vector;
#else
#endif

using std::byte, std::to_integer;

#include "deflate.hpp"
namespace zlite {
struct div_t {
  unsigned quot, rem;
};
static div_t div(unsigned x, unsigned y) {
  div_t lol;
  lol.quot = x / y;
  lol.rem = x % y;
  return lol;
}
static std::string operator+(std::string &s, unsigned i) {
  return s + std::to_string(i);
}

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
    case compression_mode::None: {
      auto len = to_integer<unsigned short>((block.data.at(0) << 8) |
                                            block.data.at(1)),
           nlen = to_integer<unsigned short>((block.data.at(2) << 8) |
                                             block.data.at(3));
      if (~len != nlen) {
        std::string message("Wrong length in an uncompressed block."
                            "\nExpected len:" +
                            std::to_string(len) +
                            ", nlen:" + std::to_string(~len) +
                            "\nGot len:" + std::to_string(len) +
                            ", nlen:" + std::to_string(len) + '\n');
        throw runtime_error(message);
      }
      if (block.data.size() - 4 != len)
        throw runtime_error(
            "Length of uncompressed block does not equal actual size.");

      for (unsigned short i = 4; i < len; i++) {
        lol.emplace_back(block.data.at(i));
      }
    } break;
    case compression_mode::With_dynamic_Huffman: {
      while (true) {
        unsigned short sym;
        if (sym == 256)
          break;

        if (sym < 256) {
          lol.emplace_back(byte(sym));
        } else {
        }
      }
    } break;
    case compression_mode::With_fixed_Huffman:
    unsigned short len_codes {257};
      break;
    default:
      throw std::runtime_error("Invalid Deflate compression mode");
    }
    //}
  }

  return lol;
}
// NOTE: constructor only allows one set of input data to be compressed only one
// way
deflate::deflate(vector<byte> uncompressed_data, compression_mode mode) {
  switch (mode) {
  case compression_mode::None: {
    div_t lol{div(uncompressed_data.size(), 0xffff)};
    for (unsigned i = 0; i < lol.quot; i++) {
      deflate_block block;
      block.is_final_block = false;
      block.mode = mode;
      block.data = {byte(0xff), byte(0xff), byte(0), byte(0)};
      for (auto j = 0; j < 0xffff; j++) {
        block.data.emplace_back(uncompressed_data.at(0xffff * i + j));
      }
      blocks.emplace_back(block);
    }
    deflate_block block;
    block.is_final_block = true;
    block.mode = mode;
    uint16_t len = lol.rem, nlen = ~len;
    block.data = {byte(lol.rem >> 8), byte(lol.rem | 0xff), byte(nlen >> 8),
                  byte(nlen | 0xff)};

    for (auto it = uncompressed_data.rbegin(); it != (it + lol.rem); ++it) {
      block.data.emplace_back(uncompressed_data.at(*it));
    }
    blocks.emplace_back(block);
  } break;
  case compression_mode::With_dynamic_Huffman: {
    deflate_block lol;
  } break;
  case compression_mode::With_fixed_Huffman: {
    deflate_block lol;
  } break;
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

const deflate::deflate_block &deflate::operator[](const size_t index) const {
  try {
    return blocks.at(index);
  } catch (std::out_of_range &e) {
    throw;
  }
}
void deflate::push(vector<byte> uncompressed_data, compression_mode mode) {
  blocks.end()->is_final_block = false;
  deflate_block block;
  block.mode = mode;
  switch (mode) {
  case compression_mode::None: {
    div_t lol{div(uncompressed_data.size(), 0xffff)};
    for (unsigned i = 0; i < lol.quot; i++) {
      deflate_block block;
      block.is_final_block = false;
      block.mode = mode;
      block.data = {byte(0xff), byte(0xff), byte(0), byte(0)};
      for (auto j = 0; j < 0xffff; j++) {
        block.data.emplace_back(uncompressed_data.at(0xffff * i + j));
      }
      blocks.emplace_back(block);
    }

    uint16_t len = lol.rem, nlen = ~len;
    block.data = {byte(lol.rem >> 8), byte(lol.rem | 0xff), byte(nlen >> 8),
                  byte(nlen | 0xff)};

    for (auto it = uncompressed_data.rbegin(); it != (it + lol.rem); ++it) {
      block.data.emplace_back(uncompressed_data.at(*it));
    }

  } break;
  case compression_mode::With_dynamic_Huffman:
    break;
  case compression_mode::With_fixed_Huffman:
    break;
  default:
    break;
  }
  blocks.emplace_back(block);
  block.is_final_block = true;
}

const char *deflate::info() {}
} // namespace zlite

extern "C" {}
