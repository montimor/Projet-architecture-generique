/*http://libmodbus.org/documentation/ http://libmodbus.org/docs/v3.0.6/*/

#include "ros/ros.h" // Permet d'utilisé les fonctions de ROS
#include <sstream> 
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std; // Permet d'éviter de mettre std:: 


#include "API_schneider.hpp" // Bibliothèque de classe 


	//-------------------------------------------------------------------------------------------
	//---------------------------------PROGRAMME PRINCIPAL---------------------------------------
	//-------------------------------------------------------------------------------------------

int main(int argc, char **argv) // fonction principal
{	
	int i;	
	ros::init(argc, argv, "monorail_connection_api_central"); // Initialisation de ros
	ros::NodeHandle n; // Creation du noeud
 	ros::Rate loop_rate(0.5); // Frequence de la boucle ROS
	API_schneider api_central; // Creation d'une classe
	
	api_central.connection_API(3); // Connection a l API

	cout << "Test avant de la boucle \n"<< endl; // Affichage

	while (ros::ok() ) //boucle infinie ROS
	{ 
	
	api_central.lecture_registre_entree(1); // Lecture des 16 registres du module 1
	api_central.ecriture_registre(2, 0, 0); // Mise a 0 du bit 0 du module 2
	api_central.ecriture_registre(2, 1, 0); // Mise a 0 du bit 1 du module 2
	cout << "Test fin de la boucle \n"<< endl; // Affichage
	ros::spinOnce(); // Tourner dans le vide 
	loop_rate.sleep(); // La boucle s'endort jusqu'à la prochaine activation
	}

		api_central.deconnection_API(); // Deconnection de l API apres la fin du while

return 0;
}
