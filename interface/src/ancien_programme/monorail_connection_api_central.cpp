/*http://libmodbus.org/documentation/ http://libmodbus.org/docs/v3.0.6/*/

#include "ros/ros.h" // Permet d'utilisé les fonctions de ROS
#include <sstream> 
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std; // Permet d'éviter de mettre std:: 


int main(int argc, char **argv) // fonction principal
{	
	ros::init(argc, argv, "monorail_connection_api_central"); //initialisation de ros
	ros::NodeHandle n; // creation du noeud
  ros::Rate loop_rate(100); // frequence de la boucle
	//-------------------------------------------------------------------------------------------
	
	
	
	
	cout << "Test avant de la boucle \n"<< endl;
  //-------------------------------------------------------------------------------------------
	while (ros::ok() ) //boucle infinie
	{
		cout << "Test de la boucle \n"<< endl;
		ros::spinOnce();
		loop_rate.sleep(); //la boucle s'endort jusqu'à la prochaine activation
	}
return 0;
}
