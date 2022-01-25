#include "column_table.h"
#include <cstring>
#include <iostream>

namespace bytedance_db_project {
ColumnTable::ColumnTable() {}

ColumnTable::~ColumnTable() {
  if (columns_ != nullptr) {
    delete columns_;
    columns_ = nullptr;
  }
}

//
// columnTable, which stores data in column-major format.
// That is, data is laid out like
//   col 1 | col 2 | ... | col m.
//
void ColumnTable::Load(BaseDataLoader *loader) {
  num_cols_ = loader->GetNumCols();
  std::vector<char *> rows = loader->GetRows();
  num_rows_ = rows.size();
  columns_ = new char[FIXED_FIELD_LEN * num_rows_ * num_cols_];

  for (int32_t row_id = 0; row_id < num_rows_; row_id++) {
    auto cur_row = rows.at(row_id);
    for (int32_t col_id = 0; col_id < num_cols_; col_id++) {
      int32_t offset = FIXED_FIELD_LEN * ((col_id * num_rows_) + row_id);
      std::memcpy(columns_ + offset, cur_row + FIXED_FIELD_LEN * col_id,
                  FIXED_FIELD_LEN);
    }
  }
}

int32_t ColumnTable::GetIntField(int32_t row_id, int32_t col_id) {
    // TODO: Implement this!
       //首先计算偏移量
    auto offset = FIXED_FIELD_LEN * col_id * num_rows_ + FIXED_FIELD_LEN * row_id;

    //判断偏移量是否在合法范围内
    if (offset >= 0 && offset < FIXED_FIELD_LEN * num_rows_ * num_cols_) {

        //通过偏移量获取对应int32_t类型数据并返回
        return *(int32_t*)(columns_ + offset);
    }
    return 0;
}

void ColumnTable::PutIntField(int32_t row_id, int32_t col_id, int32_t field) {
  // TODO: Implement this!
    auto offset = FIXED_FIELD_LEN * col_id * num_rows_ + FIXED_FIELD_LEN * row_id;

    //判断偏移量是否在合法范围内
    if (offset >= 0 && offset < FIXED_FIELD_LEN * num_rows_ * num_cols_) {

        //通过偏移量获取对应int32_t类型数据并修改
        *(int32_t*)(columns_ + offset)=field;
    }
}

int64_t ColumnTable::ColumnSum() {
    // TODO: Implement this!
    int64_t sum = 0;

    for (auto row_id = 0; row_id < num_rows_; row_id++) {

        //col0所在地址的偏移量
        auto offset = FIXED_FIELD_LEN *row_id;
        sum += *(int32_t*)(columns_ + offset);
    }
    return sum;
}

int64_t ColumnTable::PredicatedColumnSum(int32_t threshold1,int32_t threshold2) {
  // TODO: Implement this!
  return 0;
}

int64_t ColumnTable::PredicatedAllColumnsSum(int32_t threshold) {
  // TODO: Implement this!
  return 0;
}

int64_t ColumnTable::PredicatedUpdate(int32_t threshold) {
  // TODO: Implement this!
  return 0;
}
} // namespace bytedance_db_project
