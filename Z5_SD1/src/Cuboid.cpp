#include "../inc/Cuboid.h"
#include "../inc/Matrix.hh"
#include "../inc/SystemOfLinearEquations.hh"
#include <fstream>
#include <iostream>
#include <cmath>
Cuboid::Cuboid()
{
	//std::cout<<"Default Constructor" <<std::endl;
	std::ifstream inputFile;
	std::cout<<kModelCuboid<<std::endl;
	inputFile.open(kModelCuboid);
	//std::cout<<"File opened" << kModelCuboid<<std::endl;
	if (!inputFile.is_open())
	{
		std::cerr << "Unable to load model Cuboid file!"
			<< std::endl;
		return;
	}
	Vector3D point;
	while (inputFile >> point)
	{
		//std::cout<<"Point: "<<point<<std::endl;
		points.emplace_back(point);
	}
	inputFile.close();
//	std::cout<<"endl Constructor: Default\n";
}

Cuboid::Cuboid(std::string s_filename): filename{s_filename}// , angle {0},translation{0,0,0}
{
	//std::cout<<"string Constructor" <<std::endl;
	std::ifstream inputFile;
	std::cout<<kModelCuboid<<std::endl;
	inputFile.open(kModelCuboid);
	//std::cout<<"File opened " << kModelCuboid<<std::endl;
	if (!inputFile.is_open())
	{
		std::cerr << "Unable to load model Cuboid file!"
			<< std::endl;
		return;
	} 
	//std::cout<<"Init vec temp"<<std::endl;
	Vector3D point; 
	//std::cout<<"starting reading\n";
	while (inputFile >> point)
	{
		points.emplace_back(point);
	}
	inputFile.close();
	//std::cout<<"endl Constructor: string\n";
}

void Cuboid::draw() const
{
	//std::cout<<"start drawing\n";
	std::ofstream outputFile;
	outputFile.open(filename);
	if (!outputFile.is_open())
	{
		std::cerr << "Unable to open drone file!" << std::endl;
		return;
	}
	std::cout<<"Current Angle: "<<this->angle << std::endl;

	std::vector<std::vector<double>> Rot_By_Z = 
	{
		{std::cos(angle),-std::sin(angle),0},
		{std::sin(angle),std::cos(angle),0},
		{0,0,1}
	};

	Matrix<double,3> Rotation_Matrix(Rot_By_Z);
	Rotation_Matrix.AddEl({1,1,1});
	SystemOfLinearEquations<double> SoLE(Rotation_Matrix);
	SoLE.Gauss();
	Vector<double,3>  RotV = SoLE.Result();
	//std::cout<<"Vec Rot: " <<RotV<<std::endl;

	for (unsigned i = 0; i < points.size(); ++i)
	{
		outputFile << (points[i] * RotV) + translation << std::endl;
		if (i % 4 == 3) // triggers after every 4 points
		{
			outputFile << "#\n\n";
		}
	}
	outputFile.close();
	//std::cout<<"End drawing"<<std::endl;
}

void Cuboid::Rotate(const double & other)
{
	this->angle = this->angle + other;
}

void Cuboid::translate(const Vector3D& change)
{
	translation = translation + change;
}

void Cuboid::Move(double s_distance, double s_angle)
{
	double ua = s_angle / 120, ud = s_distance/120;

	Vector3D movement(cos(s_angle)*ud,0,sin(s_angle)*ud);

	Rotate(ua);
	translate(movement);
	this->draw();

}

Cuboid::~Cuboid()
{
}
