#ifndef _STORAGE_TX_BLOCK_H
#define _STORAGE_TX_BLOCK_H
#include <array>

#include "storage/cache/block.h"

namespace storage::tx {

struct TxId {};

struct TxSlot {
  enum class Status { None, Active, Committed };
  TxSlot() : tx_id {}
  TxSlot(const TxSlot &tx_slot)
      : tx_id(tx_slot.tx_id), undo_block_id(tx_slot.undo_block_id),
        status(tx_slot.status) {}

  TxId tx_id;
  common::BlockId undo_block_id;
  Status status;
};

class Block : cache::Block {
public:
  Block() : cache::Block() {}

  common::TimeStamp GetCleanoutTime() const { return cleanout_time_; }
  void SetCleanoutTime(const common::TimeStamp &cleanout_time) {
    cleanout_time_ = cleanout_time;
  }
  std::uint8_t GetTxCount() const { return tx_count_; }
  void SetTxCount(std::uint8_t tx_count) { tx_count_ = tx_count; }

  TxSlot GetTxSlot(std::uint8_t index) { return tx_slots_[index]; }
  bool AddTx(const TxSlot &new_tx_slot) {
    bool tx_added = false;
    for (int i = 0; i < tx_count_; i++) {
      TxSlot &tx_slot = tx_slots_[i];
      if (tx_slot.status != TxSlot::Status::None)
        continue;
      tx_slot = new_tx_slot;
      tx_added = true;
    }
    return tx_added;
  }

private:
  common::TimeStamp cleanout_time_;
  std::uint8_t tx_count_;
  TxSlot tx_slots_[1];
};

} // namespace storage::tx

#endif