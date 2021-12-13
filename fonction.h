#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct 
{
char reference_capteur[20];
char nom_capteur[20];
char typeCapteur[20];
}capteur;

//capteur c;

typedef struct{
char jour[20];
char heure[20];
char numT[20];
char t[20];
}temp;

//temp T1,T2;

typedef struct{
char j[20];
char h[20];
char numcapt[20];
char etat[20];
}fum;

//fum F;
int verif( char log[],char Pw[]);
void ajouter_capteur (capteur c);
void afficher_capteur (GtkWidget *liste);
void supprim_capteur(capteur c);
void vider(GtkWidget *liste);

int verifier(char ref_capt[]);

void afficher_capteur_deff (GtkWidget *liste1);
void viderD(GtkWidget *liste1);



void afficher_liste_alarmes_mouvements(GtkWidget *liste3);

int compt();
float calcul(int c);
