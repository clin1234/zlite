#ifndef __deflate
#define __deflate

#include <cstddef>
#ifdef __STDC_HOSTED__
#include <vector>

using std::vector;
#else
#endif

using std::byte;

namespace zlite {
enum class compression_mode : unsigned char {
  None,
  With_fixed_Huffman,
  With_dynamic_Huffman,
  Reserved
};

struct deflate_block {
    bool is_final_block;
    compression_mode mode : 2;
    vector<byte> data;
  };
// TODO: encapsulate
struct deflate {
  vector<deflate_block> blocks;
  size_t number_of_blocks;

  vector<byte> decompress();
  const char* info();
  deflate(vector<byte>, compression_mode mode = compression_mode::None);
  deflate_block &operator[](const size_t index);
  const deflate_block &operator[] (const size_t index) const;
  void swap(deflate &);
  void clear();
  void recompress(deflate_block &, compression_mode);
  void push(vector<byte>, compression_mode);
};
} // namespace zlite

#endif
