#ifndef HH_VECTOR3D
#define HH_VECTOR3D

#include "Vector.hh"



class Vector3D :public Vector<double,3>
{
private:
	static int Vector3D_Count_Current;
	static int Vector3D_Count_Total;
	
public:
	static int Return_Current();
	static int Return_Total();
	Vector3D();
	Vector3D(double x, double y, double z);
	Vector3D(const Vector<double, 3>& other);
	~Vector3D();
	friend std::istream & operator>>(std::istream& stream, Vector3D& vec);
	//friend std::ostream &operator<<(std::ostream& stream, Vector3D& vec);
};

std::istream & operator>>(std::istream& stream, Vector3D& vec);
//std::ostream &operator<<(std::ostream& stream, Vector3D& vec);

#endif