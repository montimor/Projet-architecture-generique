/*http://libmodbus.org/documentation/ http://libmodbus.org/docs/v3.0.6/*/

#include "ros/ros.h" // Permet d'utilisé les fonctions de ROS
#include <sstream> 
#include <iostream>
#include <unistd.h>
#include <modbus/modbus.h> // Fournit les fonctions accédant a l'API
#include <stdio.h>
#include <stdlib.h>






using namespace std; // Permet d'éviter de mettre std:: 

int main(int argc, char **argv) // fonction principal
{	
	
	ros::init(argc, argv, "monorail_connection_api_central"); //initialisation de ros
	ros::NodeHandle n; // creation du noeud
        ros::Rate loop_rate(100); // frequence de la boucle

	int i,retour_lecteur_registre;
        int j = 0 , k = 0;
        int adresse_registre[1024], valeur_registre[1024];


	modbus_t *api_central; //creation d'une structure permettant de recuperer toutes les informations
	uint16_t tab_reg[64]; // variable des registres
	api_central = modbus_new_tcp("192.168.0.103", 502); // alloue et initialise une structure modbus_t pour communiquer avec un serveur Modbus TCP/IPv4
	
	//-------------------------------------------------------------------------------------------
	modbus_connect(api_central); // Etablie la connection 
        cout << "Test de connection \n"<< endl;
 	//----- Test de la connection -----//
	//Test de l'allocation mémoire de la structure modbus_t
	if (api_central == NULL) 
	{
 	printf("Impossible d'alloué la memoire\n");
	return -1;
	}
	//Test de la connection
if (modbus_connect(api_central) == -1) 
	{
	printf("Echec de connection : %s\n", modbus_strerror(errno));
	modbus_free(api_central);
	return -1;
	}

			cout << "Test avant de la boucle \n"<< endl;
  //-------------------------------------------------------------------------------------------
	while (ros::ok() ) //boucle infinie
	{
		retour_lecteur_registre = modbus_read_registers(api_central,j , 1, tab_reg);	//lecture du registre
		printf("retour_lecteur_registre = %d\n",retour_lecteur_registre);
		if (retour_lecteur_registre == -1) //Si la lecteur du registre renvoie -1 => erreur
		{
			printf("Erreur, %s\n", modbus_strerror(errno));
			return -1;
		}
		for (i=0; i < retour_lecteur_registre; i++) 
		{
    	printf("reg[%d]=%d (0x%X)\n", i, tab_reg[i], tab_reg[i]);
                if(tab_reg[i] !=0)
			{
				adresse_registre[k] = j ;
				valeur_registre[k] = tab_reg[i];
				k=k+1;
			}		
		}
	


                if (j==250)
                {
                    for(i=0;i<k;i++)
                        {
                        printf("Adresse mémoire : %d\tValeur : %d\n",adresse_registre[i],valeur_registre[i]);
                        }
                        printf("Fin de la boucle\n");
                        modbus_close(api_central);
                        modbus_free(api_central);
                        return 0;


                }
		printf("j= %d \n",j);
		cout << "Test de la boucle \n"<< endl;
                if (j<1023)
                j=j+1;

	ros::spinOnce();
	loop_rate.sleep(); //la boucle s'endort jusqu'à la prochaine activation

	}




return 0;
}
