

#include "../inc/Vector3D.h"
#include <fstream>
int Vector3D::Vector3D_Count_Current = 0;
int Vector3D::Vector3D_Count_Total = 0;

int Vector3D::Return_Current()
{
	return Vector3D_Count_Current;
}

int Vector3D::Return_Total()
{
	return Vector3D_Count_Total;
}

Vector3D::Vector3D()
{
	++Vector3D_Count_Current;
	++Vector3D_Count_Total;
}

Vector3D::Vector3D(double x, double y, double z)
{
	this->vector[0] = x;
	this->vector[1] = y;
	this->vector[2] = z;
	++Vector3D_Count_Current;
	++Vector3D_Count_Total;
}

Vector3D::Vector3D(const Vector<double,3>& other)
{
	this->vector = other.GetVector();
}

Vector3D::~Vector3D()
{
	--Vector3D_Count_Current;
}


std::istream & operator>>(std::istream & stream, Vector3D & vec)
{
	stream >> vec[0] >> vec[1] >> vec[2];
	return stream;
}
/*
std::ostream &operator<<(std::ostream& stream, const Vector3D& vec)
{
	stream << vec[0] << vec[1] << vec[2] << std::endl;
	return stream;
}
*/