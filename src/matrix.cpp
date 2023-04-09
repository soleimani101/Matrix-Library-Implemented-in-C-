#include "../include/matrix.h"

Matrix2::Matrix2() {}

// Constructor that creates a square matrix of the given size.
Matrix2::Matrix2(int size)
{
  // Set the row and column sizes to the given size.
  rowSize = size;
  colSize = size;

  // Set the initial row and column capacities to size+2.
  // The extra capacity will allow for future growth without needing to reallocate.
  colCapacity = size + 2;
  rowCapacity = size + 2;

  // Allocate memory for the matrix data using the row capacity.
  data = new int *[rowCapacity];

  // Initialize the matrix data to all zeros.
  for (int i = 0; i < rowSize; i++)
  {
    // Allocate memory for each row using the column capacity.
    data[i] = new int[colCapacity];

    // Initialize each element to zero.
    for (int j = 0; j < colSize; j++)
    {
      data[i][j] = 0;
    }
  }
}

// Constructor that creates a matrix of the given row and column sizes.
Matrix2::Matrix2(int row, int column)
{
  // Initialize the member variables
  rowSize = row;
  colSize = column;
  colCapacity = row + 2;
  rowCapacity = column + 2;

  // Allocate memory for the data array using the row capacity.
  data = new int *[rowCapacity];

  // Allocate memory for each row using the column capacity.
  for (int i = 0; i < rowSize; i++)
  {
    data[i] = new int[colCapacity];
  }

  // Initialize the matrix elements to zero
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      data[i][j] = 0;
    }
  }
}

// Constructor that creates a matrix from an initializer list of rows and columns.
Matrix2::Matrix2(std::initializer_list<std::initializer_list<int>> a)
{
  // Determine the row and column sizes of the matrix based on the size of the initializer list.
  rowSize = a.size();
  colSize = a.begin()->size(); // assume all rows have the same number of columns

  // Determine the row and column capacities based on the sizes of the matrix.
  colCapacity = rowSize + 2;
  rowCapacity = colSize + 2;

  // Allocate memory for the matrix data using the row capacity.
  data = new int *[rowCapacity];

  // Allocate memory for each row using the column capacity and initialize the elements with values from the initializer list.
  for (int i = 0; i < rowSize; i++)
  {
    data[i] = new int[colCapacity];
    for (int j = 0; j < colSize; j++)
    {
      data[i][j] = *((a.begin() + i)->begin() + j);
    }
  }
}


// This is a copy constructor for the Matrix2 class. It takes a
//  Matrix2 object other as input and creates a new Matrix2 object with the same values as other.
// The function starts by iterating over the rows and 
// columns of other using nested for loops. For each element in other,
//  the corresponding element in the new Matrix2 object is set to the same value.
// Overall, this function creates a new Matrix2 object
//  that is a copy of an existing Matrix2 object.

Matrix2::Matrix2(const Matrix2 &other)
{ // copy constructor
  // copy matrix elements from other to this
  for (int i = 0; i < rowSize; ++i)
  {
    for (int j = 0; j < colSize; ++j)
    {
      data[i][j] = other.data[i][j];
    }
  }
}

Matrix2 Matrix2::append(const Matrix2 &m, int axis) const
{
  if (axis == 0 && m.rowSize != rowSize)
  {
    throw std::invalid_argument("Matrices must have the same number of rows to be appended horizontally.");
  }
  else if (axis == 1 && m.colSize != colSize)
  {
    throw std::invalid_argument("Matrices must have the same number of columns to be appended vertically.");
  }

  Matrix2 result = Matrix2(rowSize + colSize + m.colSize);
  if (axis == 0)
  {
    result = Matrix2(rowSize, colSize + m.colSize);
    for (int i = 0; i < rowSize; i++)
    {
      for (int j = 0; j < colSize; j++)
      {
        result.data[i][j] = data[i][j];
      }
    }
    for (int i = 0; i < m.rowSize; i++)
    {
      for (int j = 0; j < m.colSize; j++)
      {
        result.data[i][colSize + j] = m.data[i][j];
      }
    }
  }
  else
  {
    result = Matrix2(rowSize + m.rowSize, colSize);
    for (int i = 0; i < rowSize; i++)
    {
      for (int j = 0; j < colSize; j++)
      {
        result.data[i][j] = data[i][j];
      }
    }
    for (int i = 0; i < m.rowSize; i++)
    {
      for (int j = 0; j < m.colSize; j++)
      {
        result.data[rowSize + i][j] = m.data[i][j];
      }
    }
  }
  std::cout << result << std::endl;
  return result;
}

void Matrix2::display() const
{
  int **nonConstData = const_cast<int **>(data);
  // Print out the matrix elements
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      std::cout << nonConstData[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int Matrix2::getRowSize() const { return rowSize; }
int Matrix2::getColSize() const { return colSize; }
int Matrix2::getRowCapacity() const { return rowCapacity; }
int Matrix2::getColCapacity() const { return colCapacity; }

Matrix2 Matrix2::operator*(const Matrix2 &other) const
{
  Matrix2 result(rowSize, other.colSize);
  for (int i = 0; i < rowSize; ++i)
  {
    for (int j = 0; j < other.colSize; ++j)
    {
      for (int k = 0; k < colSize; ++k)
      {
        result.data[i][j] += data[i][k] * other.data[k][j];
      }
    }
  }
  return result;
}

Matrix2 Matrix2::operator+(const Matrix2 &m) const
{
  Matrix2 result(rowSize, colSize);
  for (int i = 0; i < colSize; ++i)
  {
    for (int j = 0; j < rowSize; ++j)
    {
      result.data[i][j] = data[i][j] + m.data[i][j];
    }
  }
  return result;
}

Matrix2 &Matrix2::operator+=(const Matrix2 &m)
{
  for (int i = 0; i < colSize; ++i)
  {
    for (int j = 0; j < rowSize; ++j)
    {
      this->data[i][j] += m.data[i][j];
    }
  }
  return *this;
}

Matrix2 Matrix2::operator-(const Matrix2 &m) const
{
  Matrix2 result(rowSize, colSize);
  for (int i = 0; i < colSize; ++i)
  {
    for (int j = 0; j < rowSize; ++j)
    {
      result.data[i][j] = data[i][j] - m.data[i][j];
    }
  }
  return result;
}

Matrix2 Matrix2::operator|(const Matrix2 &m) const
{
  // check that A and b have compatible dimensions
  if (colSize != m.rowSize)
  {
    throw std::invalid_argument("Matrix dimensions are not compatible for solving Ax=b.");
  }

  // copy the matrix A and vector b into a single augmented matrix
  Matrix2 aug(rowSize, colSize + 1);
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      aug.data[i][j] = data[i][j];
    }
    aug.data[i][colSize] = m.data[i][0];
  }

  // perform Gaussian elimination with partial pivoting
  for (int i = 0; i < rowSize; i++)
  {
    // find pivot row with largest absolute value
    int max_row = i;
    double max_val = std::abs(aug.data[i][i]);
    for (int j = i + 1; j < rowSize; j++)
    {
      double abs_val = std::abs(aug.data[j][i]);
      if (abs_val > max_val)
      {
        max_row = j;
        max_val = abs_val;
      }
    }
    if (max_val < 0.001)
    {
      throw std::runtime_error("Matrix is singular or ill-conditioned.");
    }

    // swap pivot row with current row
    if (max_row != i)
    {
      for (int j = 0; j <= colSize; j++)
      {
        std::swap(aug.data[i][j], aug.data[max_row][j]);
      }
    }

    // eliminate lower triangular part of current column
    for (int j = i + 1; j < rowSize; j++)
    {
      double factor = aug.data[j][i] / aug.data[i][j];
      for (int k = i; k <= colSize; k++)
      {
        aug.data[j][k] -= factor * aug.data[i][k];
      }
    }
  }

  // back-substitute to solve for x
  Matrix2 x(rowSize, 1);
  for (int i = rowSize - 1; i >= 0; i--)
  {
    double sum = 0.0;
    for (int j = i + 1; j < colSize; j++)
    {
      sum += aug.data[i][j] * x.data[j][0];
    }
    x.data[i][0] = (aug.data[i][colSize] - sum) / aug.data[i][i];
  }

  return x;
}

Matrix2 &Matrix2::operator++()
{
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      data[i][j]++;
    }
  }
  return *this;
}

Matrix2 Matrix2::operator++(int)
{
  Matrix2 copy(*this);
  operator++(); // call pre-increment operator
  return copy;
}

Matrix2 &Matrix2::operator--()
{
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      data[i][j]--;
    }
  }
  return *this;
}

Matrix2 Matrix2::operator--(int)
{
  Matrix2 copy(*this);
  operator--(); // call pre-increment operator
  return copy;
}

int *Matrix2::operator[](int index) const
{
  return data[index];
}

bool Matrix2::operator==(const Matrix2 &m) const
{
  // Check sizes first
  if (rowSize != m.rowSize || colSize != m.colSize)
  {
    return false;
  }

  // Check contents
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      if (data[i][j] != m.data[i][j])
      {
        return false;
      }
    }
  }

  // If all checks passed, the matrices are equal
  return true;
}

bool Matrix2::operator<(const Matrix2 &m) const
{
  if (rowSize != m.rowSize)
  {
    return rowSize < m.rowSize;
  }
  if (colSize != m.colSize)
  {
    return colSize < m.colSize;
  }
  int sum = 0;
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      sum += data[i][j];
    }
  }
  int m_sum = 0;
  for (int i = 0; i < m.rowSize; i++)
  {
    for (int j = 0; j < m.colSize; j++)
    {
      m_sum += m.data[i][j];
    }
  }
  return sum < m_sum;
}

bool Matrix2::operator>(const Matrix2 &m) const
{
  if (rowSize != m.rowSize)
  {
    return rowSize > m.rowSize;
  }
  if (colSize != m.colSize)
  {
    return colSize > m.colSize;
  }
  int sum = 0;
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      sum += data[i][j];
    }
  }
  int m_sum = 0;
  for (int i = 0; i < m.rowSize; i++)
  {
    for (int j = 0; j < m.colSize; j++)
    {
      m_sum += m.data[i][j];
    }
  }
  return sum > m_sum;
}

bool Matrix2::operator<=(const Matrix2 &m) const
{
  if (rowSize != m.rowSize)
  {
    return rowSize <= m.rowSize;
  }
  if (colSize != m.colSize)
  {
    return colSize <= m.colSize;
  }
  int sum = 0;
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      sum += data[i][j];
    }
  }
  int m_sum = 0;
  for (int i = 0; i < m.rowSize; i++)
  {
    for (int j = 0; j < m.colSize; j++)
    {
      m_sum += m.data[i][j];
    }
  }
  return sum <= m_sum;
}

bool Matrix2::operator>=(const Matrix2 &m) const
{
  if (rowSize != m.rowSize)
  {
    return rowSize >= m.rowSize;
  }
  if (colSize != m.colSize)
  {
    return colSize >= m.colSize;
  }
  int sum = 0;
  for (int i = 0; i < rowSize; i++)
  {
    for (int j = 0; j < colSize; j++)
    {
      sum += data[i][j];
    }
  }
  int m_sum = 0;
  for (int i = 0; i < m.rowSize; i++)
  {
    for (int j = 0; j < m.colSize; j++)
    {
      m_sum += m.data[i][j];
    }
  }
  return sum >= m_sum;
}

Matrix2 &Matrix2::operator=(const Matrix2 &m)
{
  if (this != &m)
  {
    if (data != nullptr)
    {
      for (int i = 0; i < rowSize; i++)
      {
        delete[] data[i];
      }
      delete[] data;
    }
    rowSize = m.rowSize;
    colSize = m.colSize;
    data = new int *[rowSize];
    for (int i = 0; i < rowSize; i++)
    {
      data[i] = new int[colSize];
      for (int j = 0; j < colSize; j++)
      {
        data[i][j] = m.data[i][j];
      }
    }
  }
  return *this;
}

std::ostream &operator<<(std::ostream &os, const Matrix2 &m)
{
  for (int i = 0; i < m.rowSize; i++)
  {
    for (int j = 0; j < m.colSize; j++)
    {
      os << m.data[i][j] << " ";
    }
    os << std::endl;
  }
  return os;
}
