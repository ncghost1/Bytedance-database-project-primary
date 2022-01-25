#include "indexed_row_table.h"

namespace bytedance_db_project {
IndexedRowTable::IndexedRowTable(int32_t index_column) {
  index_column_ = index_column;
}

void IndexedRowTable::Load(BaseDataLoader *loader) {
  // TODO: Implement this!
}

int32_t IndexedRowTable::GetIntField(int32_t row_id, int32_t col_id) {
  // TODO: Implement this!
  return 0;
}

void IndexedRowTable::PutIntField(int32_t row_id, int32_t col_id,
                                  int32_t field) {
  // TODO: Implement this!
}

int64_t IndexedRowTable::ColumnSum() {
  // TODO: Implement this!
  return 0;
}

int64_t IndexedRowTable::PredicatedColumnSum(int32_t threshold1,
                                             int32_t threshold2) {
  // TODO: Implement this!
  return 0;
}

int64_t IndexedRowTable::PredicatedAllColumnsSum(int32_t threshold) {
  // TODO: Implement this!
  return 0;
}

int64_t IndexedRowTable::PredicatedUpdate(int32_t threshold) {
  // TODO: Implement this!
  return 0;
}
} // namespace bytedance_db_project