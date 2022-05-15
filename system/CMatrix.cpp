#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include "CMatrix.h"

using namespace std;

typedef struct CMatrix* Cube;

CMatrix Cinit(int row, int col, int height, double value)
{
    Cube C = (struct CMatrix*)malloc(sizeof(Cube));
    C->m_Col = col;
    C->m_height = height;
    C->m_Row = row;
    if (col <= 0)
        cout << "Error : The col can't be negative!" << endl;
    else if (row <= 0)
        cout << "Error : The row can't be negative!" << endl;
    else if (height <= 0)
        cout << "Error : The height can't be negative!" << endl;
    else
    {
        (C->pMatrix) = (double***)malloc(row * sizeof(double**));
        for (int i = 0; i < row; i++)
            (C->pMatrix)[i] = (double**)malloc(col * sizeof(double*));
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                (C->pMatrix)[i][j] = (double*)malloc(height * sizeof(double));

        for (int r = 0; r < row; r++)
            for (int c = 0; c < col; c++)
                for (int h = 0; h < height; h++)
                    (C->pMatrix)[r][c][h] = value;
    }
    return *C;
}