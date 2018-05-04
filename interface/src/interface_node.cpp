/*http://libmodbus.org/documentation/ http://libmodbus.org/docs/v3.0.6/*/

#include "ros/ros.h" // Permet d'utilisé les fonctions de ROS
#include <sstream> 
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std; // Permet d'éviter de mettre std:: 


#include "API_schneider.hpp" // Bibliothèque de classe 
#include "IHM.hpp" // Bibliothèque de classe 


	//-------------------------------------------------------------------------------------------
	//---------------------------------PROGRAMME PRINCIPAL---------------------------------------
	//-------------------------------------------------------------------------------------------

int main(int argc, char **argv) // fonction principal
{	
	int i;	
	ros::init(argc, argv, "monorail_connection_api_central"); // Initialisation de ros
	ros::NodeHandle n; // Creation du noeud
 	ros::Rate loop_rate(0.5); // Frequence de la boucle ROS
	IHM ihm;
	cout << "Test avant de la boucle \n"<< endl; // Affichage
	ihm.welcome();	
	
	while (ros::ok() ) //boucle infinie ROS
	{ 
			
	
	ihm.changer_bit_module_2();
	ihm.affichage_module_2();

 
	cout << "Test boucle\n"<< endl; // Affichage
	ros::spinOnce(); // Tourner dans le vide 
	loop_rate.sleep(); // La boucle s'endort jusqu'à la prochaine activation
	}
	ihm.goodbye();

return 0;
}
