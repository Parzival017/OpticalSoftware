#include "system.h"
#include "Object_Plane.h"
#include <cmath>
#include <iostream>
#include <limits.h>

Obj::Obj(int Diameter, const SMatrix &FOVIN, Standard surface1, Standard surface2, Standard surface3, Image_Plane IMA, int STOIN) {
    Entrance_Pupil_Diameter = Diameter;
    FOV = FOVIN;
    STO = STOIN;
    surface.clear();
    Standard surface0; //?
    Standard IMAsurface;
    IMAsurface.r = INFINITY;
    IMAsurface.O = IMA.O;
    surface = {surface0, surface1, surface2, surface3, IMAsurface};
    Back_System.resize(surface.size());
    Front_System.resize(surface.size());
}

void Obj::CalculateParameters(Object_Plane OBJ) //Obj Front_sysytem, Obj Back_system,
{
    int i = 2;
    int j = 1;
    int n;
    n = 4;//length(surface)=4
    for (i = 2;i <= (n-1);i++)
    {
        surface[i].O = surface[i - 1].O + surface[i - 1].d;
        surface[i].n_1 = surface[i - 1].n_2;
    }
    surface[n].O = surface[n - 1].O + surface[n - 1].d;
    for (i = 1; i <= (STO - 1); i++)
    {
        Front_System[i + 1] = surface[i];
    }
    for (i = STO+1; i <= 3; i++)
    {
        Back_System[j] = surface[i];

    }
    //Calculate the length of Total Track
    if (OBJ.getO() > 9999)       //这里的OBJ.O=0      isinf为判断极限
    {
        Total_Track = surface[n].O;
    }
    else
    {
        Total_Track = surface[n].O + 0;  //这里的零代表OBJ.0
    }
}

void Obj::system_function1()
{
    double phi, phi_1, phi_2;
    double t;
    double delta_2 = 0, delta_1;
    int i = 0;
    int n = 4;   //size(surface,2)=4
    if (n > 2)
    {
        phi_1 = (surface[1].n_2 - surface[1].n_1) * surface[1].c;
        Object_Principle_Plane = surface[1].O;
        for (i = 1; i <= (n - 2);i++)
        {
            phi_2 = (surface[i + 1].n_2 - surface[i + 1].n_1) * surface[i + 1].c;
            t = surface[i].d / surface[i + 1].n_2 - delta_2;
            phi = phi_1 + phi_2 - phi_1 * phi_2 * t;
            delta_1 = phi_2 / phi * t;
            delta_2 = (0 - phi_1) / phi * t;
            Object_Principle_Plane = Object_Principle_Plane + delta_1 * surface[1].n_1;
            Image_Priciple_Plane = delta_2 * surface[i + 1].n_2;
            phi_1 = phi;
        }
    }
    else if (n == 2)
    {
        phi = (surface[i].n_2 - surface[i].n_1) * surface[1].c;
        Object_Principle_Plane = surface[1].O;
        Image_Priciple_Plane = surface[1].O;
    }
    else
    {
        phi = LONG_MAX;                             //NaN为“非数值”的标量表示形式
        Object_Principle_Plane = LONG_MAX;
        Image_Priciple_Plane = LONG_MAX;
    }
    Effective_Focal_Length = 1 / phi;
    Back_Focal_Length = Effective_Focal_Length + Image_Priciple_Plane;
    Image_Priciple_Plane = Image_Priciple_Plane - surface[4 - 1].d;
}
int Obj::length(vector<Standard> surface)
{
    int i = 0;
    int length=0;
    for (i = 0;i <= 3;i++)
    {
        if (surface[i].O)
        {
            length++;
        }
    }
    return length;
}

void Obj::Calculate_Planes(Obj &Sys) {
    double delta_2;
    double delta_1;
    if (length(Sys.Front_System) == 0) {
        //获取矩阵Sys.Front_System的列数
        this->Entrance_Pupil_Position = Sys.surface[1].O;
        double phi_1 = (Sys.Back_System[1].n_2 - Sys.Back_System[1].n_1) * Sys.Back_System[1].c;
        double phi = phi_1;
        delta_2 = 0;
        Object_Principle_Plane = 0;//属性
        Image_Priciple_Plane = 0;//属性
        for (int i = 1; i <= length(Sys.Back_System) - 1; i++) {
            double phi_2 = (Sys.Back_System[i + 1].n_2 - Sys.Back_System[i + 1].n_1) * Sys.Back_System[i + 1].c;
            double t = Sys.Back_System[i].d / Sys.Back_System[i].n_2 - delta_2;
            phi = phi_1 + phi_2 - phi_1 * phi_2 * t;
            double delta_1 = phi_2 / phi * t;
            double delta_2 = -phi_1 / phi * t;
            Object_Principle_Plane = Object_Principle_Plane + delta_1 * Sys.Back_System[1].n_1;
            Image_Priciple_Plane = delta_2 * Sys.Back_System[i + 1].n_2;
            phi_1 = phi;
        }
        double n1 = Sys.Back_System[1].n_1;
        double n2 = Sys.Back_System[length(Sys.Back_System)].n_2;
        double z1 = -(Object_Principle_Plane + Sys.Back_System[1].O);
        double z2 = n2 / (n1 / z1 + phi);
        Exit_Pupil_Position = z2 + Image_Priciple_Plane - Sys.Back_System[length(Sys.Back_System)].d;
        double f1 = -n1 / phi;
        double f2 = n2 / phi;
        double m = -z2 * f1 / (z1 * f2);
        Exit_Pupil_Diameter = abs(m * Sys.Entrance_Pupil_Diameter);
    }
    else if (length(Sys.Back_System) == 0) {
        Exit_Pupil_Position = -Sys.surface[length(Sys.surface) - 1].d;
        double phi_1 = (Sys.Front_System[1].n_2 - Sys.Front_System[1].n_1) * Sys.Front_System[1].c;
        double phi = phi_1;
        double delta_2 = 0;
        Object_Principle_Plane = 0;
        Image_Priciple_Plane = 0;
        for (int i = 1; i <= length(Sys.Front_System) - 1; i++) {
            double phi_2 = (Sys.Front_System[i + 1].n_2 - Sys.Front_System[i + 1].n_1) * Sys.Front_System[i + 1].c;
            double t = Sys.Front_System[i].d / Sys.Front_System[i].n_2 - delta_2;
            phi = phi_1 + phi_2 - phi_1 * phi_2 * t;
            double delta_1 = phi_2 / phi * t;
            delta_2 = -phi_1 / phi * t;
            Object_Principle_Plane = Object_Principle_Plane + delta_1 * Sys.Front_System[1].n_1;
            Image_Priciple_Plane = delta_2 * Sys.Front_System[i + 1].n_2;
            phi_1 = phi;
        }
        double n1 = Sys.Front_System[1].n_1;
        double n2 = Sys.Front_System[length(Sys.Front_System)].n_2;
        double z2 = Sys.Front_System[length(Sys.Front_System)].d - Image_Priciple_Plane;
        double z1 = n1 / (n2 / z2 - phi);
        Entrance_Pupil_Position = z1 + Object_Principle_Plane;
        double f1 = -n1 / phi;
        double f2 = n2 / phi;
        double m = -z2 * f1 / (z1 * f2);
        Exit_Pupil_Diameter = abs(m * Sys.Entrance_Pupil_Diameter);
    }
    else {
        double phi_11 = (Sys.Front_System[1].n_2 - Sys.Front_System[1].n_1) * Sys.Front_System[1].c;
        double phi1 = phi_11;
        double delta_2 = 0;
        Object_Principle_Plane1 = 0;
        Image_Priciple_Plane1 = 0;
        for (int i = 1; i <= length(Sys.Front_System) - 1; i++) {
            double phi_12 = (Sys.Front_System[i + 1].n_2 - Sys.Front_System[i + 1].n_1) * Sys.Front_System[i + 1].c;
            double t = Sys.Front_System[i].d / Sys.Front_System[i].n_2 - delta_2;
            phi1 = phi_11 + phi_12 - phi_11 * phi_12 * t;
            double delta_1 = phi_12 / phi1 * t;
            double delta_2 = -phi_11 / phi1 * t;
            Object_Principle_Plane1 = Object_Principle_Plane1 + delta_1 * Sys.Front_System[1].n_1;
            Image_Priciple_Plane1 = delta_2 * Sys.Front_System[i + 1].n_2;
            phi_11 = phi1;
        }
        double n11 = Sys.Front_System[1].n_1;
        double n12 = Sys.Front_System[length(Sys.Front_System)].n_2;
        double z12 = Sys.Front_System[length(Sys.Front_System)].d - Image_Priciple_Plane1;
        double z11 = n11 / (n12 / z12 - phi1);
        Entrance_Pupil_Position = z11 + Object_Principle_Plane1;

        double phi_21 = (Sys.Back_System[1].n_2 - Sys.Back_System[1].n_1) * Sys.Back_System[1].c;
        double phi2 = phi_21;
        delta_2 = 0;
        Object_Principle_Plane2 = 0;
        Image_Priciple_Plane2 = 0;
        for (int i = 1; i <= length(Sys.Back_System) - 1; i++) {
            double phi_22 = (Sys.Back_System[i + 1].n_2 - Sys.Back_System[i + 1].n_1) * Sys.Back_System[i + 1].c;
            double t = Sys.Back_System[i].d / Sys.Back_System[i].n_2 - delta_2;
            phi2 = phi_21 + phi_22 - phi_21 * phi_22 * t;
            delta_1 = phi_22 / phi2 * t;
            delta_2 = -phi_21 / phi2 * t;
            Object_Principle_Plane2 = Object_Principle_Plane2 + delta_1 * Sys.Back_System[1].n_1;
            Image_Priciple_Plane2 = delta_2 * Sys.Back_System[i + 1].n_2;
            phi_21 = phi2;
        }
        double n21 = Sys.Back_System[1].n_1;
        double n22 = Sys.Back_System[length(Sys.Back_System)].n_2;
        double z21 = -(Object_Principle_Plane2 + Sys.surface[Sys.STO].d);
        double z22 = n22 / (n21 / z21 + phi2);
        Exit_Pupil_Position = z22 + Image_Priciple_Plane2 - Sys.Back_System[length(Sys.Back_System)].d;

        double n1 = Sys.Front_System[1].n_1;
        double n2 = Sys.Back_System[length(Sys.Back_System)].n_2;
        double z1 = Entrance_Pupil_Position - Sys.Object_Principle_Plane;
        double z2 = Exit_Pupil_Position - Sys.Image_Priciple_Plane;
        double f1 = -n1 * Sys.Effective_Focal_Length;
        double f2 = n2 * Sys.Effective_Focal_Length;
        double m = -z2 * f1 / (z1 * f2);
        Exit_Pupil_Diameter = abs(m * Sys.Entrance_Pupil_Diameter);
    }
}

double Obj::check() {
    //位置 inf
    Object_Plane OBJ = Object_Plane(__DBL_MAX__);
    // 曲率、厚度、折射率
    Standard Surface1 = Standard(73.895, 10.5, 1.517);
    Standard Surface2 = Standard(-73.895, 10.5, 1.649);
    Standard Surface3 = Standard(-73.895, 68.71244, 1);
    //
    Image_Plane IMA = Image_Plane();
    static SMatrix FOVIN = SMatrix(2, 2, {0, 0, 0, 0.0524});
    // 			   Obj(int Diameter,const SMatrix& FOVIN, Standard surface1, Standard surface2, Standard surface3, Image_Plane IMA,int STOIN)
    Obj M_System = Obj(10, FOVIN, Surface1, Surface2, Surface3, IMA, 1);
    M_System.CalculateParameters(OBJ);
    M_System.system_function1();
    return M_System.Effective_Focal_Length;
}
