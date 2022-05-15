#pragma once
#include<iostream>

class Object_Plane
{
private:
	double O;
public:
	Object_Plane() = default;
	Object_Plane(double O);
	double getO() { return O; }
};
//classdef Object_Plane
//properties
//O% position of Object Plane
//end
//methods
//function obj = Object_Plane(O)
//obj.O = O;
//end
//end
//end