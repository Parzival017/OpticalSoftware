#pragma once
#include <new>
#include <cmath>
#include <iostream>

using namespace std;

class SMatrix
{
private:
    int m_Col;    // 矩阵的列数
    int m_Row;   // 矩阵的行数
    double** m_pMatrix;  // 通过二重指针来实现动态矩阵
public:
    SMatrix() = default;
    SMatrix(int colNum);
    SMatrix(int rowNum, int colNum);
    SMatrix(const SMatrix& other);
    SMatrix(SMatrix&& copy_from_me);
    SMatrix(int m, int n, initializer_list<double> lst);
    SMatrix operator + (const SMatrix& rightM);
    SMatrix operator - (const SMatrix& rightM);
    SMatrix operator * (double k);
    SMatrix operator * (const SMatrix& rightM);
    SMatrix operator = (const SMatrix& rightM);
    SMatrix operator = (SMatrix&& rightM);
    double getElement(int m, int n);
    bool setElement(int m, int n, double val);
    inline void alloc(int colNum, int rowNum);
    void show();
    void setCol(int colNum);
    void setRow(int rowNum);
    SMatrix transpose();
    friend double* getLine(const SMatrix& a, int line);
    friend SMatrix inverse(SMatrix& a);
    friend ostream& operator << (ostream& os, const SMatrix& rightM);
};
