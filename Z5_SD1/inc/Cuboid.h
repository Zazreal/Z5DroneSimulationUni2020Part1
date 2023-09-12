#ifndef H_CUBOID
#define H_CUBOID
#include "Vector3D.h"
#include <vector>
#include <string>
#include "Shape.h"


const std::string kModelCuboid("solid/model.dat");

class Cuboid: public Shape 
{
private:
	std::vector<Vector3D> points;
	Vector3D translation = {0,0,0};
	double angle = 0;
	std::string filename;
public:
	Cuboid();
	Cuboid(std::string s_filename);
	void Rotate(const double& other);
	void draw() const;
	void translate(const Vector3D& change);
	void Move(double s_distance, double s_angle);
	~Cuboid();
};

#endif