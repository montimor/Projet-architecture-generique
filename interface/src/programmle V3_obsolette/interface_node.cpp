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

#define ADRESSE_IP_API2 "192.168.0.102" 
	//-------------------------------------------------------------------------------------------
	//---------------------------------PROGRAMME PRINCIPAL---------------------------------------
	//-------------------------------------------------------------------------------------------

int main(int argc, char **argv) // fonction principal
{	
	int i;	
	ros::init(argc, argv, "monorail_connection_api_central"); // Initialisation de ros
	ros::NodeHandle n; // Creation du noeud
 	ros::Rate loop_rate(0.5); // Frequence de la boucle ROS
	cout << "Test avant de la boucle \n"<< endl; // Affichage
	
	modbus_t *ap;
	ap = modbus_new_tcp(ADRESSE_IP_API2,502);
	uint16_t registre;
	modbus_connect(ap);
	int adresse_registre = 0;
	int nombre_registres =1;
	int toto;	
	uint16_t tab_reg[1]={0};
	
	int j;
	while (ros::ok() ) //boucle infinie ROS
	{ 
			
		toto = modbus_read_registers(ap,0,1,tab_reg);
		printf("Nombre de valeur lu : %d\n",toto);	
		printf("Valeur en hexadecimal : (0x%X)\n", tab_reg[i]);





		
		cout << "Test boucle\n"<< endl; // Affichage
		ros::spinOnce(); // Tourner dans le vide 
		loop_rate.sleep(); // La boucle s'endort jusqu'à la prochaine activation
	}
	// On ouvre la liaison Modbus avec l'automate
	modbus_close(ap);
	modbus_free(ap);

return 0;
}
