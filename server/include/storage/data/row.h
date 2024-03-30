#ifndef STORAGE_COMMON_ROW
#define STORAGE_COMMON_ROW

#include "storage/common/block_id.h"

namespace storage::common {
class RowId {
public:
  using RowNumber = std::uint16_t;
  RowId(BlockId block_id, RowNumber row_no)
      : block_id_(block_id), row_no_(row_no) {}
  BlockId GetBlockId() const { return block_id_; }
  RowNumber GetRowNumber() const { return row_no_; }

private:
  BlockId block_id_;
  RowNumber row_no_;
};

class RowPiece {
public:
  enum class Status { Header, Tail };

private:
  RowId row_id_;
};

} // namespace storage::common

#endif