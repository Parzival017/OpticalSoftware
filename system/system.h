#pragma once
#pragma once
#include "Image_Plane.h"
#include "Object_Plane.h"
#include "SMatrix.h"
#include "Standard.h"

#include <iostream>
#include <vector>
#define QT_DEBUG
#ifdef QT_DEBUG
#include <QDebug>
#endif
using namespace std;


class Obj
{
    vector<Standard> surface;
public:
    SMatrix FOV;          //FOV为2*2的矩阵

    //Surface surface;      //Surface的数据类型待定
    int STO;
    double Total_Track;
    double Object_Principle_Plane;
    double Effective_Focal_Length;
    double Back_Focal_Length;
    double Image_Priciple_Plane;
    double Entrance_Pupil_Position;
    double Entrance_Pupil_Diameter;
    double Exit_Pupil_Position;
    double Exit_Pupil_Diameter;
    double Object_Principle_Plane1;
    double Object_Principle_Plane2;
    double Image_Priciple_Plane1;
    double Image_Priciple_Plane2;
    vector<Standard> Front_System;
    vector<Standard> Back_System;
    //    Obj() = default;
    Obj(int Diameter, const SMatrix &FOVIN, Standard surface1, Standard surface2, Standard surface3, Image_Plane IMA, int STOIN);
    void CalculateParameters(Object_Plane OBJ); //Obj Front_sysytem, Obj Back_system,
    void system_function1();
    void Calculate_Planes(Obj &);
    int length(vector<Standard>);

    //!    代码组数据传输相关接口，请不要修改
public:
    Obj() {
        Entrance_Pupil_Diameter = 0;
        FOV = SMatrix(2, 2, {0, 0, 0, 0});
        STO = 0;
        surface.clear();
        Standard surface0; //?
        Standard IMAsurface;
        IMAsurface.r = INFINITY;
        IMAsurface.O = 0;
        surface = {surface0, IMAsurface};
        Back_System.resize(surface.size());
        Front_System.resize(surface.size());
    }
    double check();
    void setDiameter(int Diameter) { Entrance_Pupil_Diameter = Diameter; }; //入瞳直径
    void setFOVIN(const SMatrix &FOVIN) { FOV = FOVIN; };                   //视场
    void setIMA(Image_Plane IMA) { surface.end()->O = IMA.O; }
    void setSTO(int STOIN) { STO = STOIN; };
    void addSurface(int index, Standard sur) //插入在index处
    { surface.emplace(surface.begin() + index, sur); };
    void addSurface(int index, double r = INFINITY, double d = 0, double n = 1) //插入在index处
    { surface.emplace(surface.begin() + index, Standard(r, d, n)); };
    void delSurface(int index) { surface.erase(surface.begin() + index); }
    Standard getSurface(int index) { return surface[index]; }
    int getSurfaceSize() { return surface.size(); };
    void setSurface_radiu(int index, double r) { surface[index].r = r; }
    void setSurface_thick(int index, double d) { surface[index].d = d; }
    void setSurface_ref(int index, double n) { surface[index].n_2 = n; }
    void setSurface_conic(int index, double c) { surface[index].k = c; }
    void setSurface_semiD(int index, double D) { surface[index].D = D; }
#ifdef QT_DEBUG
    void
    log() {
        int index = 0;
        for (auto sur : surface)
            qDebug() << index++ << sur.r << sur.d << sur.D << sur.k << sur.n_2;
    }
#endif
};
