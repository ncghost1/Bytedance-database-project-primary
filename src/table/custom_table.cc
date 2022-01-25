#include "custom_table.h"
#include <cstring>

namespace bytedance_db_project {
CustomTable::CustomTable() {}

CustomTable::~CustomTable() {}

void CustomTable::Load(BaseDataLoader *loader) {
  // TODO: Implement this!
}

int32_t CustomTable::GetIntField(int32_t row_id, int32_t col_id) {
  // TODO: Implement this!
  return 0;
}

void CustomTable::PutIntField(int32_t row_id, int32_t col_id, int32_t field) {
  // TODO: Implement this!
}

int64_t CustomTable::ColumnSum() {
  // TODO: Implement this!
  return 0;
}

int64_t CustomTable::PredicatedColumnSum(int32_t threshold1,
                                         int32_t threshold2) {
  // TODO: Implement this!
  return 0;
}

int64_t CustomTable::PredicatedAllColumnsSum(int32_t threshold) {
  // TODO: Implement this!
  return 0;
}

int64_t CustomTable::PredicatedUpdate(int32_t threshold) {
  // TODO: Implement this!
  return 0;
}
} // namespace bytedance_db_project