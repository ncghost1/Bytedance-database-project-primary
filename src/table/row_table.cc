#include "row_table.h"
#include <cstring>

//【后端&大数据-初级】内存数据布局
namespace bytedance_db_project {
RowTable::RowTable() {}

RowTable::~RowTable() {
  if (rows_ != nullptr) {
    delete rows_;
    rows_ = nullptr;
  }
}

void RowTable::Load(BaseDataLoader *loader) {
  num_cols_ = loader->GetNumCols();
  auto rows = loader->GetRows();
  num_rows_ = rows.size();
  rows_ = new char[FIXED_FIELD_LEN * num_rows_ * num_cols_];
  for (auto row_id = 0; row_id < num_rows_; row_id++) {
    auto cur_row = rows.at(row_id);
    std::memcpy(rows_ + row_id * (FIXED_FIELD_LEN * num_cols_), cur_row,
                FIXED_FIELD_LEN * num_cols_);
  }
}
 
int32_t RowTable::GetIntField(int32_t row_id, int32_t col_id) {
    // TODO: Implement this!
    //首先计算偏移量
    auto offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_id;

    //判断偏移量是否在合法范围内
    if (offset >= 0 && offset < FIXED_FIELD_LEN * num_rows_ * num_cols_) {

        //通过偏移量获取对应int32_t类型数据并返回
        return *(int32_t*)(rows_ + offset);
    }

    return 0;
}

void RowTable::PutIntField(int32_t row_id, int32_t col_id, int32_t field) {
    // TODO: Implement this!
    //首先计算偏移量
    auto offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_id;

    //判断偏移量是否在合法范围内
    if (offset >= 0 && offset < FIXED_FIELD_LEN * num_rows_ * num_cols_) {

        //通过偏移量获取对应int32_t类型的数据并赋值为field
        *(int32_t*)(rows_ + offset) = field;
    }

}

int64_t RowTable::ColumnSum() {
    // TODO: Implement this!

    int64_t sum = 0;

    for (auto row_id = 0; row_id < num_rows_; row_id++) {

        //col0所在地址的偏移量
        auto offset = FIXED_FIELD_LEN * row_id * num_cols_;
        sum += *(int32_t*)(rows_ + offset);
    }
    
    return sum;
}

int64_t RowTable::PredicatedColumnSum(int32_t threshold1, int32_t threshold2) {
    // TODO: Implement this!
    int64_t sum = 0;

    //col_0表示col0的位置，初始化为-1
    int32_t col_0 = -1;

    //col_0的位置最小为0
    if (threshold1 < 0) {
        col_0 = 0;
    }
    else {
        col_0 = threshold1;
    }
    if (col_0 < num_cols_ && col_0 < threshold2) {
        for (auto row_id = 0; row_id < num_rows_; row_id++) {
            auto offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_0;
            sum += *(int32_t*)(rows_ + offset);
        }
    }
    return sum;
}

int64_t RowTable::PredicatedAllColumnsSum(int32_t threshold) {
  // TODO: Implement this!
    int64_t sum = 0;
    int32_t col_0 = threshold + 1;

    //col_0的位置最小为0
    if (threshold < 0) {
        col_0 = 0;
    }
    if (col_0 >= 0 && col_0 < num_cols_ && col_0 < threshold) {
        for (auto row_id = 0; row_id < num_rows_; row_id++) {
            for (auto col_id = col_0; col_id < num_cols_; col_id++) {
                auto offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * col_id;
                sum += *(int32_t*)(rows_ + offset);
            }
        }
    }
    return sum;
}

int64_t RowTable::PredicatedUpdate(int32_t threshold) {
    // TODO: Implement this!
    int64_t update_rows = 0;

    if (threshold > 0) {
        for (auto row_id = 0; row_id < num_rows_; row_id++) {
            for (auto col_id = 0; col_id < threshold && col_id+3<num_cols_; col_id++) {

                //求col2和col3的地址偏移量
                auto col2_offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * (col_id + 2);
                auto col3_offset = FIXED_FIELD_LEN * row_id * num_cols_ + FIXED_FIELD_LEN * (col_id + 3);

                //取出col2和col3的数据
                int32_t col2_elem = *(int32_t*)(rows_ + col2_offset);
                int32_t col3_elem = *(int32_t*)(rows_ + col3_offset);

                //修改col3的数据(col3 = col2+ col3)
                *(int32_t*)(rows_ + col3_offset) = col2_elem + col3_elem;

                //更新过的行数+1
                update_rows++;
            }
        }
    }
    return update_rows;
}
} // namespace bytedance_db_project
