#ifndef _STORAGE_COMMON_BLOCK_ID
#define _STORAGE_COMMON_BLOCK_ID

#include <string>

namespace storage::common {

class BlockId {
public:
  static constexpr std::uint8_t kMaxFileNameLength = 128;

  BlockId(const char *file_name, int block_number)
      : block_number_(block_number) {
    std::strcpy(file_name_, file_name);
  }
  BlockId() : block_number_(0) {
    std::memcpy(file_name_, NULL, kMaxFileNameLength);
  }

  std::string GetFileName() const { return std::string(file_name_); }
  int GetBlockNumber() const { return block_number_; }

private:
  char file_name_[kMaxFileNameLength];
  int block_number_;
};
} // namespace storage::common
#endif