#include "Standard.h"
#include "SMatrix.h"
#include "CMatrix.h"
#include <iostream>

// Initialize surface parameters
Standard::Standard(const double &r, const double &d, const double &n_2) : r(r), d(d), n_2(n_2) {
    c = 1 / r;
}

double Standard::Evaluation(const Standard&, const double& x, const double& y, const double& z)
{
    return (c * (x * x + y * y)) / (1 + sqrt(1 - (1 + k) * c * c * (x * x + y * y))) - z + O;
}

// Solve the intersection of rays and surfaces
CMatrix Standard::Solve_Intersection(const Standard& obj, const CMatrix& Light)
{
    int D1 = Light.m_Row;
    int D3 = Light.m_height;
    CMatrix Inter_P = Cinit(D1, 3, D3, 0);
    for (int j = 0; j < D3; ++j)
    {
        for (int i = 0; i < D1; ++i)
        {
            double x0 = Light.pMatrix[i][0][j];
            double y0 = Light.pMatrix[i][1][j];
            double z0 = Light.pMatrix[i][2][j];
            SMatrix P(3, 1, { x0,y0,z0 });
            double x_p = x0, y_p = y0, z_p = z0;
            double F_1 = Evaluation(obj, x_p, y_p, z_p);
            while (abs(F_1) > 1e-6)
            {
                double delta = 1e-6;
                double x = x_p + delta;
                double y = y_p + delta;
                double F_x = (Evaluation(obj, x, y_p, z_p) - F_1) / delta;
                double F_y = (Evaluation(obj, x_p, y, z_p) - F_1) / delta;
                double m = Light.pMatrix[i][3][j];
                double n = Light.pMatrix[i][4][j];
                double l = Light.pMatrix[i][5][j];
                SMatrix M(3, 3, { F_x, F_y, -1, -l, 0, m, 0, -l, n });
                double F_2 = m * (P.getElement(2, 0) - z0) - l * (P.getElement(0, 0) - x0);
                double F_3 = n * (P.getElement(2, 0) - z0) - l * (P.getElement(1, 0) - y0);
                SMatrix F(3, 1, { F_1, F_2, F_3 });
                P = P - inverse(M) * F;
                x_p = P.getElement(0, 0);
                y_p = P.getElement(1, 0);
                z_p = P.getElement(2, 0);
                F_1 = Evaluation(obj, x_p, y_p, z_p);
            }
            SMatrix pp = P.transpose();
            Inter_P.pMatrix[i][0][j] = pp.getElement(0, 0);
            Inter_P.pMatrix[i][1][j] = pp.getElement(0, 1);
            Inter_P.pMatrix[i][2][j] = pp.getElement(0, 2);
        }
    }
    return Inter_P;
}

//Solve the normal vector at the intersection CMatrix &Normal_Vector(const Standard &, const CMatrix &Inter_P);
CMatrix Standard::Normal_Vector(const Standard& obj, const CMatrix& Inter_P)
{
    int D1 = Inter_P.m_Row;
    int D3 = Inter_P.m_height;
    CMatrix N = Cinit(D1, 3, D3, 0);
    for (int j = 0; j < D3; j++)
    {
        for (int i = 0; i < D1; i++)
        {
            double x0 = Inter_P.pMatrix[i][0][j];
            double y0 = Inter_P.pMatrix[i][1][j];
            double z0 = Inter_P.pMatrix[i][2][j];
            double delta = 1e-6;
            double x = x0 + delta;
            double y = y0 + delta;
            double z = z0 + delta;
            double F_x = Evaluation(obj, x, y0, z0) - Evaluation(obj, x0, y0, z0);
            double F_y = Evaluation(obj, x0, y, z0) - Evaluation(obj, x0, y0, z0);
            double F_z = Evaluation(obj, x0, y0, z) - Evaluation(obj, x0, y0, z0);
            N.pMatrix[i][0][j] = F_x / delta;
            N.pMatrix[i][1][j] = F_y / delta;
            N.pMatrix[i][2][j] = F_z / delta;
            double temp = sqrt((F_x * F_x + F_y * F_y + F_z * F_z) / (delta * delta));
            N.pMatrix[i][0][j] /= temp;
            N.pMatrix[i][1][j] /= temp;
            N.pMatrix[i][2][j] /= temp;
            if (N.pMatrix[i][2][j] < 0)
            {
                N.pMatrix[i][0][j] *= -1;
                N.pMatrix[i][1][j] *= -1;
                N.pMatrix[i][2][j] *= -1;
            }
        }
    }
    return N;
}

//Snell's Law
CMatrix Standard::Refraction(const Standard& obj, const CMatrix& Light, const CMatrix& N)
{
    int D1 = Light.m_Row;
    int D3 = Light.m_height;
    CMatrix Out = Cinit(D1, 3, D3, 0);
    CMatrix In = Cinit(D1, 3, D3, 0);
    for (int i = 0; i < D1; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            for (int k = 0; k < D3; k++)
                In.pMatrix[i][j][k] = Out.pMatrix[i][j + 4][k];
        }
    }
    double u = n_1 / n_2;
    for (int j = 0; j < D3; j++)
    {
        for (int i = 0; i < D1; i++)
        {
            double temp = sqrt(N.pMatrix[i][0][j] * N.pMatrix[i][0][j] + N.pMatrix[i][1][j] * N.pMatrix[i][1][j] + N.pMatrix[i][2][j] * N.pMatrix[i][2][j]);
            N.pMatrix[i][0][j] /= temp;
            N.pMatrix[i][1][j] /= temp;
            N.pMatrix[i][2][j] /= temp;
            double sum = 0;
            for (int k = 0; k < 3; k++)
                sum += In.pMatrix[i][k][j] * N.pMatrix[i][k][j];
            for (int k = 0; k < 3; k++)
            {
                Out.pMatrix[i][k][j] = sqrt(1 - u * u * (1 - sum * sum)) * N.pMatrix[i][k][j] + u * (In.pMatrix[i][k][j] - sum * N.pMatrix[i][k][j]);
            }
            double mid = sqrt(Out.pMatrix[i][0][j] * Out.pMatrix[i][0][j] + Out.pMatrix[i][1][j] * Out.pMatrix[i][1][j] + Out.pMatrix[i][2][j] * Out.pMatrix[i][2][j]);
            Out.pMatrix[i][0][j] /= mid;
            Out.pMatrix[i][1][j] /= mid;
            Out.pMatrix[i][2][j] /= mid;
        }
    }
    return Out;
}
