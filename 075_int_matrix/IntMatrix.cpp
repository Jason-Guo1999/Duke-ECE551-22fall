#include "IntMatrix.h"

#include "IntArray.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns) {
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      rows[i][j] = rhs.rows[i][j];
    }
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
  numColumns = rhs.numColumns;
  numRows = rhs.numRows;

  rows = new IntArray *[rhs.numRows];
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(rhs[i]);
  }
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      rows[i][j] = rhs.rows[i][j];
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if (rows[i] != rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix ans(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      ans.rows[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if (rhs.getRows() == 0) {
    s << "[]";
  }
  else {
    s << "[";
    for (int i = 0; i < rhs.getRows() - 1; i++) {
      s << rhs[i] << "," << std::endl;
    }
  }
  s << rhs[rhs.getRows() - 1];
  s << "]";
  return s;
}
