#pragma once
#include <cmath>
#include "SMatrix.h"
#include "CMatrix.h"

using namespace std;

//参数引用
//构造函数

class Standard
{
public:
    double O = 0;     // the position
    double r = 0;     // the radius
    double c = 0;     // the curvature
    double k = 0;     // the conic constant
    double D = 0;     // the semi diameter
    double d = 0;     // the thickness
    double n_1 = 1;   // Refractive index before surface
    double n_2 = 1;   // Refractive index behind surface
    Standard() = default;
    Standard(const double &r, const double &d, const double &n_2);
    double Evaluation(const Standard &, const double &x, const double &y, const double &z);
    CMatrix Solve_Intersection(const Standard &, const CMatrix &Light);
    CMatrix Normal_Vector(const Standard &, const CMatrix &Inter_P);
    CMatrix Refraction(const Standard &, const CMatrix &, const CMatrix &);
};

