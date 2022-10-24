#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  vector<vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}

  Matrix(int row, int col) : numRows(row), numColumns(col) {
    for (int i = 0; i < row; i++) {
      rows.push_back(vector<T>(col));
    }
  }

  Matrix(const Matrix & rhs) {
    numColumns = rhs.numColumns;
    numRows = rhs.numRows;
    rows = rhs.rows;
  }

  ~Matrix() { rows.clear(); }

  Matrix & operator=(const Matrix & rhs) {
    rows.clear();
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    //vector<vector<T> > ans;
    for (int i = 0; i < numRows; i++) {
      rows.push_back(rhs[i]);
    }
    return *this;
  }

  int getRows() const { return numRows; }

  int getColumns() const { return numColumns; }

  vector<T> & operator[](int index) {
    assert(index >= 0 && index < numRows);
    return this->rows[index];
  }

  const vector<T> & operator[](int index) const {
    assert(index >= 0 && index < numRows);
    return this->rows[index];
  }

  bool operator==(const Matrix & rhs) {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }
    else {
      for (int i = 0; i < numRows; i++) {
        if ((*this)[i] != rhs[i]) {
          return false;
        }
      }
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) {
    assert(numColumns == rhs.numColumns && numRows == rhs.numRows);
    Matrix ans(rhs.numRows, rhs.numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        ans.rows[i][j] = this->rows[i][j] + rhs.rows[i][j];
      }
    }
    return ans;
  }
};

template<typename T>
ostream & operator<<(ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[ ]";
    return s;
  }
  else {
    s << "[";
    for (int i = 0; i < rhs.getRows() - 1; i++) {
      s << rhs[i] << ",";
    }
    s << rhs[rhs.getRows() - 1] << "]";
  }
  return s;
}

template<typename T>
ostream & operator<<(ostream & s, const vector<T> & rhs) {
  if (rhs.size() == 0) {
    s << "{ }";
    return s;
  }
  else {
    s << "{";
    for (size_t i = 0; i < rhs.size() - 1; i++) {
      s << rhs[i] << ",";
    }
    s << rhs[rhs.size() - 1] << "}";
  }
  return s;
}
#endif
