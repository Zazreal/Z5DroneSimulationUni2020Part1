#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include "../inc/gnuplot_link.hh"
#include "../inc/Vector3D.h"
#include "../inc/Cuboid.h"

using namespace std;


const string kDroneFile("solid/drone.dat");
const string Sea_Floor_File("solid/floor.dat");
const string Water_Surface_File("solid/water.dat");

int main()
{
	std::cout<<"Program Start" <<std::endl;
	double distance = 0, angle = 0;
	int menu = 0;
	//std::cout<<"Initializing drone" <<std::endl;
	Cuboid Drone(kDroneFile);        // To tylko przykladowe definicje zmiennej
	//std::cout<<"gnuplot link\n";
	PzG::GnuplotLink link; // Ta zmienna jest potrzebna do wizualizacji
	//std::cout<<"Init gnuplot\n";
	link.Init();
	link.AddFilename(kDroneFile.c_str(), PzG::LS_CONTINUOUS, 1);
	link.AddFilename(Water_Surface_File.c_str(),PzG::LS_CONTINUOUS,1);
	link.AddFilename(Sea_Floor_File.c_str(),PzG::LS_CONTINUOUS,1);
	link.SetDrawingMode(PzG::DM_3D);

	//std::cout<< "1st draw" << std::endl;
	Drone.draw();

	link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
	cout << "Press ENTER, to continue" << endl;
	cin.ignore(100000, '\n');
	while (menu != -1)
	{
		std::cout << "Menu:\n Enter 1 to rotate the drone\n Enter 2 to move the drone\n Enter 3 To move the drone at an angle\n Enter -1 to end the program" << std::endl;
		std::cout << "Current Vector3D count: " << Vector3D::Return_Current() << std::endl;
		std::cout << "Total Vector3D count: " << Vector3D::Return_Total() << std::endl;
		std::cin >> menu;
		switch (menu)
		{
		case 1: std::cout << "Enter the angle: ";
			std::cin >> angle;
			for (int i = 0; i < 120; ++i)
			{
				Drone.Move(0, angle);
				link.Draw();
				std::this_thread::sleep_for(std::chrono::milliseconds(8));
			}
			break;
		case 2: std::cout << "Enter the distance: ";
			std::cin >> distance;
			for (int i = 0; i < 120; ++i)
			{
				Drone.Move(distance, 0);
				link.Draw();
				std::this_thread::sleep_for(std::chrono::milliseconds(8));
			}
			break; 
		case 3:
			std::cout << "Enter the distance: ";
			std::cin >> distance;
			std::cout << "Enter the angle: ";
			std::cin >> angle;
			for (int i = 0; i < 120; ++i)
			{
				Drone.Move(distance, angle);
				link.Draw();
				std::this_thread::sleep_for(std::chrono::milliseconds(8));
			}
			break;
		case -1:
			menu = -1;
			break;

		}
	}
	return EXIT_SUCCESS;
}

