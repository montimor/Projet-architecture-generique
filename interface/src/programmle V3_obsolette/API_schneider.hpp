#ifndef API_SCHNEIDER_H
#define API_SCHNEIDER_H

#define ADRESSE_IP_API1 "192.168.0.101"
#define ADRESSE_IP_API2 "192.168.0.102" 
#define ADRESSE_IP_API3 "192.168.0.103"
#define ADRESSE_IP_API4 "192.168.0.104"
#define ADRESSE_IP_API5 "192.168.0.105" 

#include <modbus/modbus.h> // Fournit les fonctions accédant a l'API
#include "ros/ros.h" // Permet d'utilisé les fonctions de ROS

using namespace std; // Permet d'éviter de mettre std:: 

class API_schneider{
	//Attribus
	public :
	modbus_t *api; //creation d'une structure permettant de recuperer toutes les informations
	uint16_t get_input_captor_d_module_1[16];//Contient les informations des bits du module 1 de l API   
 	uint16_t get_output_actionneur_module_2[16];//Contient les informations des bits du module 2 de l API
	uint16_t get_output_actionneur_module_3[16];//Contient les informations des bits du module 3 de l API
	uint16_t set_output_actionneur_module_2[16];//Contient les set des bits du module 2 de l API
	uint16_t set_output_actionneur_module_3[16];//Contient les set des bits du module 3 de l API
	/*ros::Subscriber sub1_;		// subscriber valeur
	ros::NodeHandle nh_;		// noeud ros
	ros::Publisher pub1_;*/
	//Methode
	public :
	//Constructeur
	API_schneider(){};//constructeur de base
	//Destructeur	
	~API_schneider(){};
	
	
	//------------------------- Fonction pour les API schneider recent -------------------------//
	void connection_API(int numero_API);//Connection a l API
	void deconnection_API();//Deconnection a l API 
	void lecture_registre_entree(int indice_du_module);//Lecture des entrees de l API et sauvegarde des bits du module selectionne : 1 pour les D5,D6,D8... 2 pour les A,V et 3 pour les S1,S2,..
	void lecture_registre_entree(int indice_du_module, int numero_du_bit_a_lire);//Lecture des entrees de l API et sauvegarde des bits du module selectionne : 1 pour les D5,D6,D8... 2 pour les A,V et 3 pour les S1,S2,. 
	void ecriture_registre(int indice_du_module);//Ecriture des sorties de l API suivant le module selectionne : 2 A1,V1,A2,... et 3 pour les S1,S2,...
	void ecriture_registre(int indice_du_module, int valeur,int numero_bit);//Ecriture des sorties de l API suivant le module et le bit selectionne : 2 A1,V1,A2,... et 3 pour les S1,S2,...


	//------------------------- Fonction pour les API schneider vieux -------------------------//
	void lecture_registre_entree_vieux(int indice_du_module);
	void lecture_registre_entree_vieux(int indice_du_module, int numero_du_bit_a_lire);
	void ecriture_registre_vieux();
	void ecriture_registre_vieux(int valeur,int numero_bit);
};
#endif
