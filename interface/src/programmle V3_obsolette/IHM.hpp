#ifndef IHM_H
#define IHM_H
#include "ros/ros.h" // Permet d'utilisé les fonctions de ROS
#include "API_schneider.hpp" // Bibliothèque de classe 
using namespace std; // Permet d'éviter de mettre std:: 

class IHM{
	//Attribus
	public :
		API_schneider api1,api2,api3,api4,api5;
		int choix;
		ros::Subscriber sub1_;		//subscriber valeur
	//Methode
	public :
		//Constructeur
		IHM(){};
		//Destructeur	
		~IHM(){};
	
	void welcome();
	void changer_bit_module_2();
	void affichage_module_2();
	void goodbye();


	void changer_bit_module_3_vieux();
	void affichage_module_3_vieux();


};
#endif
