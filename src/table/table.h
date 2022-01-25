#pragma once
#include "data/csv_data_loader.h"

namespace bytedance_db_project {
class Table {
public:
  // Loads data into the table through passed-in data loader. Is not timed.
  virtual void Load(BaseDataLoader *loader) = 0;

  // Returns the int32_t field at row `row_id` and column `col_id`.
  virtual int32_t GetIntField(int32_t row_id, int32_t col_id) = 0;

  // Inserts the passed-in int32_t field at row `row_id` and column `col_id`.
  virtual void PutIntField(int32_t row_id, int32_t col_id, int32_t field) = 0;

  // Implements the query
  // SELECT SUM(col0) FROM table;
  // Returns the sum of all elements in the first column of the table.
  virtual int64_t ColumnSum() = 0;

  // Implements the query
  // SELECT SUM(col0) FROM table WHERE col1 > threshold1 AND col2 < threshold2;
  // Returns the sum of all elements in the first column of the table,
  // subject to the passed-in predicates.
  virtual int64_t PredicatedColumnSum(int32_t threshold1,
                                      int32_t threshold2) = 0;

  // Implements the query
  // SELECT SUM(col0) + SUM(col1) + ... + SUM(coln) FROM table WHERE col0 >
  // threshold; Returns the sum of all elements in the rows which pass the
  // predicate.
  virtual int64_t PredicatedAllColumnsSum(int32_t threshold) = 0;

  // Implements the query
  // UPDATE(col3 = col3 + col2) WHERE col0 < threshold;
  // Returns the number of rows updated.
  virtual int64_t PredicatedUpdate(int32_t threshold) = 0;
};
} // namespace bytedance_db_project
