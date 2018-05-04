#include "IHM.hpp"
#include "API_schneider.hpp"


void IHM::welcome()
{

	while((choix <1) || (choix>4))
	{
		printf("Bienvenue. Que désirez vous faire ? \n");
		printf("Tapez 1 pour vous connecter a l automate central\nTapez 2 pour se connecter a tous les automates\nTapez 3 pour quitter\nTapez 4 pour vous connectez au vieille automate\nVotre choix : ");
		scanf("%d",&choix);	
	}	
	if(choix ==1)
	{
		api3.connection_API(3);
	}
	if(choix ==2)
	{
		api1.connection_API(1);
		api2.connection_API(2);
		api3.connection_API(3);
		api4.connection_API(4);
		api5.connection_API(5);
	}
	if(choix ==3)
	{
		exit(-1);
	}
	if(choix ==4)
	{
		api2.connection_API(2);
	}
}



void IHM::goodbye()
{
	if(choix ==1)
	{
		api3.deconnection_API();
	}
	if(choix ==2)
	{
		api1.deconnection_API();
		api2.deconnection_API();
		api3.deconnection_API();
		api4.deconnection_API();
		api5.deconnection_API();
	}
	if(choix ==4)
	{
		api4.deconnection_API();
	}
}




void IHM::changer_bit_module_2()
{
  int bit=-1;
  int valeur=-1;
  int numero_API=0;
  /*while( (numero_API <1) || (numero_API >5))
  {
    printf("Sur quel API voulez interagir ? (1 a 5)\n");
    scanf("%d",&bit);
  }*/ //a faire plus tard
  while((bit <0) || (bit >15))
  {
    printf("\nQuel bit du module 2 voulez ? (0 a 15) : ");
    scanf("%d",&bit);
  }
  while((valeur <0) || (valeur >1))
  {
    printf("\nQuel valeur voulez vous attribuer au bit (0 ou 1) : ");
    scanf("%d",&valeur);
  }
  api3.ecriture_registre(2,valeur,bit);
}

void IHM::affichage_module_2()
{
  int i=0;
  api3.lecture_registre_entree(2);
  printf("N° bit\tValeur bit\n");
  for(i=0;i<15;i++)
  {
    printf("n°%d\t %d\n",i,api3.get_output_actionneur_module_2[i]);
  }

}


void IHM::changer_bit_module_3_vieux()
{
  int bit=-1;
  int valeur=-1;
  int numero_API=0;

  while((bit <0) || (bit >15))
  {
    printf("\nQuel bit du module 3 voulez ? (0 a 15) : ");
    scanf("%d",&bit);
  }
  while((valeur <0) || (valeur >1))
  {
    printf("\nQuel valeur voulez vous attribuer au bit (0 ou 1) : ");
    scanf("%d",&valeur);
  }
  api2.ecriture_registre_vieux(valeur,bit);
}

void IHM::affichage_module_3_vieux()
{
  int i=0;
  api2.lecture_registre_entree_vieux(3);
  printf("N° bit\tValeur bit\n");
  for(i=0;i<15;i++)
  {
    printf("n°%d\t %d\n",i,api2.get_output_actionneur_module_3[i]);
  }

}

