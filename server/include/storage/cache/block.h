#ifndef _STORAGE_CACHE_BLOCK_H
#define _STORAGE_CACHE_BLOCK_H

#include "storage/common/block_id.h"
#include "storage/common/timestamp.h"

namespace storage::cache {

enum class BlockType { kNone, kControl, kData };

class Block {
public:
  Block(common::BlockId block_id, BlockType block_type)
      : block_id_(block_id), block_type_(block_type) {}
  Block() {}

  common::BlockId GetBlockId() const { return block_id_; }
  BlockType GetBlockType() const { return block_type_; }

private:
  common::BlockId block_id_;
  BlockType block_type_;
  common::TimeStamp first_modified_time_;
  common::TimeStamp last_modified_time_;
};

} // namespace storage::cache

#endif