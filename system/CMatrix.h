#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

typedef struct CMatrix *Cube;

struct CMatrix
{
    int m_Col;
    int m_Row;
    int m_height;
    double ***pMatrix;
};

CMatrix Cinit(int row, int col, int height, double value);