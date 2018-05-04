#include "API_schneider.hpp"


void API_schneider::connection_API(int numero_API)
{	if (numero_API == 1)
	api = modbus_new_tcp(ADRESSE_IP_API1, 502); // alloue et initialise une structure modbus_t pour communiquer avec un serveur Modbus TCP/IPv4
	if (numero_API == 2)
	api = modbus_new_tcp(ADRESSE_IP_API2, 502); // alloue et initialise une structure modbus_t pour communiquer avec un serveur Modbus TCP/IPv4
	if (numero_API == 3)
	api = modbus_new_tcp(ADRESSE_IP_API3, 502); // alloue et initialise une structure modbus_t pour communiquer avec un serveur Modbus TCP/IPv4
	if (numero_API == 4)
	api = modbus_new_tcp(ADRESSE_IP_API4, 502); // alloue et initialise une structure modbus_t pour communiquer avec un serveur Modbus TCP/IPv4
	if (numero_API == 5)
	api = modbus_new_tcp(ADRESSE_IP_API5, 502); // alloue et initialise une structure modbus_t pour communiquer avec un serveur Modbus TCP/IPv4
	modbus_connect(api); // Etablie la connection 
	cout << "Test de connection \n"<< endl;
 	//----- Test -----//
	//Test de l'allocation mémoire de la structure modbus_t
	if (api == NULL) 
	{
 	printf("Impossible d'alloué la memoire\n");
	exit(-1);
	}
	//Test de la connection
if (modbus_connect(api) == -1) 
	{
	printf("Echec de connection : %s\n", modbus_strerror(errno));
	modbus_free(api);
	exit(-1);
	} 
	cout << "Connection réussie" << endl;
}
	//-------------------------------------------------------------------------------------------
void API_schneider::deconnection_API()
{	
	modbus_close( api);//Fermeture de la connection
  modbus_free( api);//Liberation de la memoire
	cout<< "Déconnection réussie " << endl;
}
	//-------------------------------------------------------------------------------------------
void API_schneider::lecture_registre_entree(int indice_du_module)
{
	int i=0;//i compteur de la boucle for
	uint16_t tab_reg[1];
	for (i=0 ; i < 16 ; i++) 
	{	tab_reg[0]=0;
		printf("valeur du registre : %d\n",i+((indice_du_module-1)*100));
		if(modbus_read_registers(api,(i+((indice_du_module-1)*100)), 1, tab_reg) != -1) //Si la lecteur du registre est different de -1 alors on enregistre
		{	if(indice_du_module == 1){printf("valeur de tab_reg module 1 : %d\n",tab_reg[0]);
				get_input_captor_d_module_1[i] = tab_reg[0];}
			if(indice_du_module == 2){printf("valeur de tab_reg module 2 : %d\n",tab_reg[0]);
				get_output_actionneur_module_2[i] = tab_reg[0];}
			if(indice_du_module == 3){printf("valeur de tab_reg module 3 : %d\n",tab_reg[0]);
				get_output_actionneur_module_3[i] = tab_reg[0];}
		}
		else//Sinon si la lecture du registre renvoie -1 alors erreur
		{
			printf("Erreur : %s \n", modbus_strerror(errno));
			exit(-1);
		}
	}    
}
	//-------------------------------------------------------------------------------------------

void API_schneider::lecture_registre_entree(int indice_du_module, int numero_du_bit_a_lire)
{
		uint16_t tab_reg[1];
	if(modbus_read_registers(api,(((indice_du_module-1)*100)+numero_du_bit_a_lire), 1, tab_reg) != -1) //Si la lecteur du registre est different de -1 alors on enregistre
		{	if(indice_du_module == 1){//printf("valeur de tab_reg module 1 : %d\n",tab_reg[0]);
				get_input_captor_d_module_1[numero_du_bit_a_lire] = tab_reg[0];}
			if(indice_du_module == 2){//printf("valeur de tab_reg module 2 : %d\n",tab_reg[0]);
				get_output_actionneur_module_2[numero_du_bit_a_lire] = tab_reg[0];}
			if(indice_du_module == 3){//printf("valeur de tab_reg module 3 : %d\n",tab_reg[0]);
				get_output_actionneur_module_3[numero_du_bit_a_lire] = tab_reg[0];}
		}
		else//Sinon si la lecture du registre renvoie -1 alors erreur
		{
			printf("Erreur : %s \n", modbus_strerror(errno));
			exit(-1);
		}
	
}

	//-------------------------------------------------------------------------------------------
void API_schneider::ecriture_registre(int indice_du_module)
{	
	int i; // Compteur de la boucle for
	for(i=0 ; i<16 ; i++) 
	{
		if(indice_du_module==2) // Si on est sur le module 2 (Output)
		{	
			if(modbus_write_register(api,((indice_du_module-1)*100)+50+i,set_output_actionneur_module_2[i])==1) // Test d ecriture
			{
				cout<<"ecriture reussie"<<endl; // Confirmation
			}
		}
		if(indice_du_module==3) // Si on est sur le module 3
		{
			if(modbus_write_register(api,((indice_du_module-1)*100)+50+i,set_output_actionneur_module_3[i])==1) // Test d ecriture
			{
				cout<<"ecriture reussie"<<endl;
			}
		}
	}
}


	//-------------------------------------------------------------------------------------------
void API_schneider::ecriture_registre(int indice_du_module, int valeur, int numero_bit)
{	
	if(indice_du_module == 2)
	{		set_output_actionneur_module_2[numero_bit] = valeur;	}
	if(indice_du_module == 3)
	{		set_output_actionneur_module_3[numero_bit] = valeur;	}
	if(modbus_write_register(api,((indice_du_module-1)*100)+50+numero_bit,valeur) == 1)
	{
		cout<<"ecriture reussie"<<endl;
	}
}

	//-------------------------------------------------------------------------------------------
void API_schneider::lecture_registre_entree_vieux(int indice_du_module)
{
	int i=0;//i compteur de la boucle for
	uint16_t tab_reg[1];
	for (i=0 ; i < 16 ; i++) 
	{	//tab_reg[1]=0;
		//printf("valeur du registre : %d\n",i+((indice_du_module-1)*100));
		if(modbus_read_registers(api,(i+((indice_du_module-2)*100)), 1, tab_reg) != -1) //Si la lecteur du registre est different de -1 alors on enregistre
		{	if(indice_du_module == 2){//printf("valeur de tab_reg module 1 : %d\n",tab_reg[0]);
				get_input_captor_d_module_1[i] = tab_reg[0];}
			if(indice_du_module == 3){//printf("valeur de tab_reg module 3 : %d\n",tab_reg[0]);
				get_output_actionneur_module_3[i] = tab_reg[0];}
		}
		else//Sinon si la lecture du registre renvoie -1 alors erreur
		{
			printf("Erreur : %s \n", modbus_strerror(errno));
			exit(-1);
		}
	}    
}
	//-------------------------------------------------------------------------------------------

void API_schneider::lecture_registre_entree_vieux(int indice_du_module, int numero_du_bit_a_lire)
{
	uint16_t tab_reg[1];
	if(modbus_read_registers(api,(((indice_du_module-2)*100)+numero_du_bit_a_lire), 1, tab_reg) != -1) //Si la lecteur du registre est different de -1 alors on enregistre
		{	if(indice_du_module == 2){//printf("valeur de tab_reg module 1 : %d\n",tab_reg[0]);
				get_input_captor_d_module_1[numero_du_bit_a_lire] = tab_reg[0];}
			if(indice_du_module == 3){//printf("valeur de tab_reg module 3 : %d\n",tab_reg[0]);
				get_output_actionneur_module_3[numero_du_bit_a_lire] = tab_reg[0];}
		}
		else//Sinon si la lecture du registre renvoie -1 alors erreur
		{
			printf("Erreur : %s \n", modbus_strerror(errno));
			exit(-1);
		}
	
}



	//-------------------------------------------------------------------------------------------
void API_schneider::ecriture_registre_vieux()
{	
	int i; // Compteur de la boucle for
	for(i=0 ; i<16 ; i++) 
	{
		if(modbus_write_register(api,((3-2)*100)+50+i,set_output_actionneur_module_3[i])==1) // Test d ecriture
		{
			cout<<"ecriture reussie"<<endl; // Confirmation
		}
	}
}


	//-------------------------------------------------------------------------------------------
void API_schneider::ecriture_registre_vieux(int valeur, int numero_bit)
{	
	set_output_actionneur_module_3[numero_bit] = valeur;	
	if(modbus_write_register(api,((3-2)*100)+50+numero_bit,valeur) == 1)
	{
		cout<<"ecriture reussie"<<endl;
	}
}



































