#include<iostream>
#include<cfloat>

#include"Image_Plane.h"
#include"Standard.h"
#include"Object_Plane.h"
#include "system.h"

using namespace std;
int main()
{
	Object_Plane OBJ = Object_Plane(DBL_MAX);//参数inf
	Standard Surface1 = Standard(73.895, 10.5, 1.517);
	Standard Surface2 = Standard(-73.895, 10.5, 1.649);
	Standard Surface3 = Standard(-73.895, 68.71244, 1);
	Image_Plane IMA = Image_Plane();
	Obj M_System = Obj(10, SMatrix(2, 2, { 0,0,0,0.0524 }), Surface1, Surface2, Surface3,IMA,1);
	M_System.CalculateParameters(OBJ);
	M_System.system_function1();
	cout << M_System.Effective_Focal_Length << endl;
}

//OBJ = Object_Plane(inf);	??正无穷
//Surface1 = Standard(73.895, 10.5, 1.517);
//Surface2 = Standard(-73.895, 10.5, 1.649);
//Surface3 = Standard(-73.895, 68.71244, 1);
//IMA = Image_Plane();   ??默认参数

//SpotDiagram(OBJ, M_System);