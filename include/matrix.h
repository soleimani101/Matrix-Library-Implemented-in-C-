#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>

class Matrix2 {


public:
    int** data;


    // Constructors

    Matrix2();
    Matrix2(int size);
    Matrix2(int row, int column);
    Matrix2(std::initializer_list<std::initializer_list<int>> a);
    Matrix2(const Matrix2& m);
    
    // Member functions
     Matrix2 append(const Matrix2& m, int axis = 0) const;
    void display() const;
    int getRowSize() const;
    int getColSize() const;
    int getRowCapacity() const;
    int getColCapacity() const;
    
    // Operators
    Matrix2 operator*(const Matrix2& m) const;
    Matrix2 operator+(const Matrix2& m) const;
    Matrix2& operator+=(const Matrix2& m);
    Matrix2 operator-(const Matrix2& m) const;
    Matrix2 operator|(const Matrix2& m) const;
    Matrix2& operator++();
    Matrix2 operator++(int);
    Matrix2& operator--();
    Matrix2 operator--(int);
    int* operator[](int index) const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix2& m);
    bool operator==(const Matrix2& m) const;
    
    bool operator<(const Matrix2& m) const;
    bool operator>(const Matrix2& m) const;
    bool operator<=(const Matrix2& m) const;
    bool operator>=(const Matrix2& m) const;
    Matrix2& operator=(const Matrix2& m);

private:
    int rowSize;
    int colSize;
    int rowCapacity;
    int colCapacity;
    
    // void expandRowCapacity();
    // void expandColCapacity();
    // void expandCapacity();
};

#endif // MATRIX_H
