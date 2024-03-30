#ifndef _STORAGE_COMMON_TIMESTAMP
#define _STORAGE_COMMON_TIMESTAMP

#include <cstdint>
#include <numeric>

namespace storage::common {

class TimeStamp {
public:
  TimeStamp() : time_high_(0), time_low_(0) {}
  TimeStamp(const TimeStamp &time_stamp)
      : time_high_(time_stamp.time_high_), time_low_(time_stamp.time_low_) {}

  void IncrementTime() {
    if (time_low_ == std::numeric_limits<std::uint32_t>::max()) {
      time_high_++;
      time_low_ = 0;
    } else {
      time_low_++;
    }
  }

private:
  std::uint16_t time_high_;
  std::uint32_t time_low_;
};

} // namespace storage::common

#endif