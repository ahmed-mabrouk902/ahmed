#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
enum
{
	REF,
	NOM,
	TYPE,
	COLUMNS
};
enum
{
J,
H,
N,
TE,
COLUMNS1

};

enum
{
JR,
HR,
NR,
TR,
COLUMNS2

};
////auth ou inscript
int verif( char log[],char Pw[])
{
FILE *f=NULL;
int trouve=-1;
char ch1[20],ch2[20];
f=fopen("user.txt","r");
if(f!=NULL){
while(fscanf(f,"%s %s",ch1,ch2)!=EOF);
{
if((strcmp(ch1,log)==0)&&(strcmp(ch2,Pw)==0))
trouve=1;

}
fclose(f);

}
return (trouve);
}
///////////////////////////////////////////calcul
float calcul(int c)
{int i=0,j=0,x;
float a;
char r[100],n[100];
FILE *f;
 
if (c==1)//temperature
{f=fopen("listecapteur.txt","r"); 
	while(fscanf(f,"%s %d %s\n",&r,&x,&n)!=EOF) 
	{
	j++;//total
	if(strcmp("capteurTemperature",n)==0) 
		{i++;//quantite
		
		}
	}

	a=(100*i)/j;//calcul pourcentage
	return a;
fclose(f);
}

else if(c==2)//debiteau
{f=fopen("listecapteur.txt","r"); 
	    
	while(fscanf(f,"%s %d %s\n",&r,&x,&n)!=EOF) 
	{
	j++;
	if(strcmp("capteurDebitEau",n)==0) 
		{i++;}
		
	}

	a=(100*i)/j;//calcul pourcentage
	return a;
fclose(f);
}//

else if(c==3)//fumee
{f=fopen("listecapteur.txt","r"); 
	while(fscanf(f,"%s %d %s\n",&r,&x,&n)!=EOF) 
	{
	j++;
	if(strcmp("capteurFumee",n)==0) 
		{i++;
		
		}
	}

	a=(100*i)/j;//calcul pourcentage  
	return a;
fclose(f);
} //

else if (c==4)//mouvement
{ f=fopen("listecapteur.txt","r"); 
	while(fscanf(f,"%s %d %s\n",&r,&x,&n)!=EOF) 
	{
	j++;
	if(strcmp("capteurMouvement",n)==0) 
		{i++;
		
		}
	}

	a=(100*i)/j;//calcul pourcentage  
	return a;
fclose(f);    
}//

else if (c==5)//autre
{f=fopen("listecapteur.txt","r"); 
	while(fscanf(f,"%s %d %s\n",&r,&x,&n)!=EOF) 
	{
	j++;
	if(strcmp("Autre",n)==0)
		{i++;
		
		}
	}

	a=(100*i)/j;//calcul pourcentage  
	return a;
fclose(f); 
}//
}
//////////////////////////////////////////compt
int compt()
{int j=0,x,a;
char r[100],n[100];
FILE *f;
f=fopen("listecapteur.txt","r"); 
while(fscanf(f,"%s %d %s",&r,&x,&n)!=EOF) 
	{j++;}
a=j;
return a;
fclose(f);
}
/////////////////////////////////////////////ajout

void ajouter_capteur (capteur c)
{
FILE *f;
f=fopen("listecapteur.txt","a+");
if (f!=NULL)
{
fprintf(f,"%s %s %s\n",c.reference_capteur,c.nom_capteur,c.typeCapteur); 
fclose(f);
}
}

void afficher_capteur (GtkWidget *liste)
{
 GtkCellRenderer *renderer;
 GtkTreeViewColumn *column;
 GtkTreeIter iter;
 GtkListStore *store;

char reference_capteur[20];
char nom_capteur[20];
char typeCapteur[20];
store=NULL;

FILE *f;
capteur c;
store=gtk_tree_view_get_model(liste);

if (store==NULL)
{
 renderer = gtk_cell_renderer_text_new ();
 column= gtk_tree_view_column_new_with_attributes("reference_capteur",renderer, "text",REF,NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste),column);

 renderer = gtk_cell_renderer_text_new();
 column= gtk_tree_view_column_new_with_attributes("nom_capteur",renderer, "text",NOM, NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste),column);

 renderer = gtk_cell_renderer_text_new();
 column= gtk_tree_view_column_new_with_attributes("typeCapteur",renderer, "text",TYPE,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


store=gtk_list_store_new(COLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);

f= fopen("listecapteur.txt","r");

if (f==NULL)//kano faragh yarja3
	{return;}
else{//sinon yi7ot
f=fopen("listecapteur.txt","a+");
	 while(fscanf(f,"%s %s %s\n",&c.reference_capteur,&c.nom_capteur,&c.typeCapteur)!=EOF)
	{
	gtk_list_store_append (store, &iter);

	gtk_list_store_set (store, &iter,REF,c.reference_capteur, NOM, c.nom_capteur, TYPE, c.typeCapteur, -1);
	}
fclose(f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste), GTK_TREE_MODEL (store));
	g_object_unref (store);
    }
}
}

void supprim_capteur(capteur c)
{
capteur c2;
char reference_capteur[20];
char nom_capteur[20];
char typeCapteur[20];
FILE *f,*g;
f=fopen("listecapteur.txt","r");
g=fopen ("tempo.txt","w");

if(f==NULL || g==NULL)
	{return;}
	else
	{ while(fscanf(f,"%s %s %s \n",&c2.reference_capteur,&c2.nom_capteur,&c2.typeCapteur)!=EOF)
		{ if (strcmp(c.reference_capteur,c2.reference_capteur)!=0 || strcmp(c.nom_capteur,c2.nom_capteur)!=0 || strcmp(c.typeCapteur,c2.typeCapteur)!=0 )
		fprintf(g,"%s %s %s \n",c2.reference_capteur,c2.nom_capteur,c2.typeCapteur);
		}//yio93ad yilawej lin yil9a capteur
fclose(f);
fclose(g);
remove ("listecapteur.txt");
rename("tempo.txt","listecapteur.txt");
	}
}



void vider(GtkWidget *liste){//vider liste//////////////////////////

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkTreeIter iter;
  GtkListStore *store;

store=NULL;
char reference_capteur[20];
char nom_capteur[20];
char typeCapteur[20];

FILE *f;

store=gtk_tree_view_get_model(liste);
if (store==NULL)
{
   renderer=gtk_cell_renderer_text_new ();
 column=gtk_tree_view_column_new_with_attributes("reference_capteur",renderer, "text",REF,NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

 renderer=gtk_cell_renderer_text_new ();
 column= gtk_tree_view_column_new_with_attributes("nom_capteur",renderer, "text",NOM,NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

 renderer=gtk_cell_renderer_text_new ();
 column=gtk_tree_view_column_new_with_attributes("typeCapteur",renderer, "text",TYPE,NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


}//faragh
store=gtk_list_store_new(COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
gtk_list_store_append(store,&iter);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste),GTK_TREE_MODEL(store));
}

//////////////affcaptdeff///////////////////////////////////////////////////////////////////
void afficher_capteur_deff (GtkWidget *liste1)
{

 GtkCellRenderer *renderer;

 GtkTreeViewColumn *column1;

 GtkTreeIter iter;

 GtkListStore *store;

char jour[20];
char heure[20];
char numT[20];
char t[20];
store=NULL;
FILE *f;
temp T;

store=gtk_tree_view_get_model(liste1);

if (store==NULL)
{
 renderer = gtk_cell_renderer_text_new ();
 column1= gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",J,NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste1),column1);

 renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Heure",renderer, "text",H, NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste1),column1);

 renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Numero capteur",renderer, "text",N,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste1),column1);
  renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Temperature",renderer, "text",TE,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste1),column1);
}

store=gtk_list_store_new(COLUMNS1,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);



f= fopen("temperaturedeff.txt","r");

if (f==NULL)
{return;}
else {
f=fopen("temperaturedeff.txt","a+");
 while(fscanf(f,"%s %s %s %s\n",T.jour,T.heure,T.numT,T.t)!=EOF)
{ 
gtk_list_store_append (store, &iter);

gtk_list_store_set (store, &iter,J,T.jour, H, T.heure, N, T.numT,TE,T.t, -1);
}
 fclose(f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste1), GTK_TREE_MODEL (store));
g_object_unref (store);

}


}
///////////historique////////////////
void afficher_capteur_his (GtkWidget *liste1)
{

 GtkCellRenderer *renderer;

 GtkTreeViewColumn *column1;

 GtkTreeIter iter;

 GtkListStore *store;

char jour[20];
char heure[20];
char numT[20];
char t[20];
store=NULL;
FILE *f;

temp T;
store=gtk_tree_view_get_model(liste1);

if (store==NULL)
{
 renderer = gtk_cell_renderer_text_new ();
 column1= gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",J,NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste1),column1);

 renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Heure",renderer, "text",H, NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste1),column1);

 renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Numero capteur",renderer, "text",N,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste1),column1);
  renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Temperature",renderer, "text",TE,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste1),column1);
}

store=gtk_list_store_new(COLUMNS1,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);



f= fopen("temperature.txt","r");

if (f==NULL)
{return;}
else {
f=fopen("temperature.txt","a+");
 while(fscanf(f,"%s %s %s %s\n",T.jour,T.heure,T.numT,T.t)!=EOF)
{ 
gtk_list_store_append (store, &iter);

gtk_list_store_set (store, &iter,J,T.jour, H, T.heure, N, T.numT,TE,T.t, -1);
}
 fclose(f);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste1), GTK_TREE_MODEL (store));
g_object_unref (store);

}


}
////////////////////viderdeff///////////////////////////////////////////////////////////
void viderD(GtkWidget *liste1)
{
 GtkCellRenderer *renderer;
  GtkTreeViewColumn *column1;
  GtkTreeIter iter;
  GtkListStore *store;

store=NULL;
char jour[20];
char heure[20];
char numT[20];
char t[20];
store=NULL;


FILE *f;

store=gtk_tree_view_get_model(liste1);
if (store==NULL)
{
 renderer = gtk_cell_renderer_text_new ();
 column1= gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",J,NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste1),column1);

 renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Heure",renderer, "text",H, NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste1),column1);

 renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Numero capteur",renderer, "text",N,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste1),column1);
  renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Temperature",renderer, "text",TE,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste1),column1);


}
store=gtk_list_store_new(COLUMNS, G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
gtk_list_store_append(store,&iter);
gtk_tree_view_set_model (GTK_TREE_VIEW (liste1),GTK_TREE_MODEL(store));



}
//verifier/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int verifier(char ref_capt[])
{
    FILE *f=NULL;
int trouve=0;
char r[100];
char n[100];
int x;
f=fopen("listecapteur.txt","r");  
if(f!=NULL){
while(fscanf(f,"%s %d %s\n",&r,&x,&n)!=EOF) 
{
if(strcmp(ref_capt,r)==0) 
trouve=1;}
fclose(f);
}

	 return (trouve);
}



void chercher_capteur_defecteux(int ch)
{
	int i=0,j,h,num,jour,numcapt,c,p1,p2;
	float T;
	FILE *f=NULL;
	
		switch (ch) {
                    case 1 : {do{
                                printf("donner le jour du mois (du 1er au 29 Novembre):\n");
                                scanf("%d",&jour);
                                }while (jour<1 || jour>29);
                                do{
                                printf("Vous souhaiter filtrer avec une plage horaire?\n");
                                printf("0 Oui \n");
                                printf("1 Non\n");
                                scanf("%d",&c);
                                }while (c!=0 && c !=1);
                                                    switch(c){
                                                       case 0 :{ do {
							   printf("donner une plage horaire alors entre 1h et 24h :\n");
                                                            printf("De :"); 
                                                            scanf("%d",&p1);
                                                            printf("Jusqu'à :");	
                                                            scanf("%d",&p2);
                                                            }while (p1<1 && p2>24);
                                                         f=fopen("temperature.txt","r");  
                                                        while(fscanf(f,"%d %d %d %f",&j,&h,&numcapt,&T)!=EOF)
                                                        { 
                                                        if( j==jour && (T<10.00 || T>30.00) && (h>=p1) && (h<=p2))  
                                                        {i++;
							printf("jour : %d lheure :%d numero capteur: %d valeur hors norme :%.2f\n",j,h,numcapt,T);
                                                        }}
                                                        fclose(f);
                                                        if(i==0)
                                                        printf("\nPas de capteur defectuex le %d \n",jour);
                                                        }
                                                        break;
                                                               
                                                        case 1 :{	
                                                        f=fopen("temperature.txt","r");  
                                                        while(fscanf(f,"%d %d %d %f",&j,&h,&numcapt,&T)!=EOF)
                                                        { 
                                                        if( j==jour && (T<10.00 || T>30.00))  
                                                        {i++;
                                                        printf("jour : %d lheure :%d numero capteur: %d valeur hors norme :%.2f\n",j,h,numcapt,T);
                                                        }}
                                                        fclose(f);
                                                        if(i==0)
                                                        printf("\nPas de capteur defectuex le %d \n",jour);
                                                        }
                                                        break;}}
                        break;
	      
	       case 2 :
			{
			do{
			printf("donner le numéro de capteur (1/2/3):\n");
			scanf("%d",&num);
			}while (num <1 || num>3);

			f=fopen("temperature.txt","r");  
			while(fscanf(f,"%d %d %d %f",&j,&h,&numcapt,&T)!=EOF)
			{ 
			if( numcapt==num && (T<10.00 || T>30.00))  
			{ i++;
			printf("jour : %d lheure :%d numero capteur: %d valeur hors norme :%.2f\n",j,h,numcapt,T);
			}
			} 
			fclose(f);
			if(i==0)
			printf("\nLe capteur numéro '%d' n'est pas defectuex.\n",num);}
			break;
		}


	}

void liste_alarmes(int ch)
{
	int i=0,etat,j,h,num,jour,numcapt;
	
	FILE *f=NULL;
	
		switch (ch) {
		case 1 : {f=fopen("mouvement.txt","r");  
			while(fscanf(f,"%d %d %d %d",&j,&h,&numcapt,&etat)!=EOF)
			{ 
			{if( etat==1 && h>=6 && h<=24)  
			{i++;
			printf("jour : %d lheure :%d numero capteur: %d \n",j,h,numcapt);
			 }}}
			fclose(f);
			if(i==0)
			printf("\nPas de mouvement detecté entre minuit et 6h.\n");
			}
			break;
	       case 2 :
			{
			f=fopen("fumee.txt","r");  
			while(fscanf(f,"%d %d %d %d",&j,&h,&numcapt,&etat)!=EOF)
			{ 
			if( etat==1)  
			{ i++;
			printf("jour : %d lheure :%d numero capteur: %d \n",j,h,numcapt);
			 }
			} 
			fclose(f);
			if(i==0)
			printf("\nPas de détection de fumée.\n");} 
			break;
		}

}


void afficher_liste_alarmes_mouvements(GtkWidget *liste3)
{

GtkCellRenderer *renderer;

 GtkTreeViewColumn *column1;

 GtkTreeIter iter;

 GtkListStore *store;

char j[20];
char h[20];
char numcapt[20];
char etat[20];
store=NULL;
FILE *f;

fum F;
store=gtk_tree_view_get_model(liste3);

if (store==NULL)
{
 renderer = gtk_cell_renderer_text_new ();
 column1= gtk_tree_view_column_new_with_attributes("Jour",renderer, "text",JR,NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste3),column1);

 renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Heure",renderer, "text",HR, NULL);
 gtk_tree_view_append_column(GTK_TREE_VIEW (liste3),column1);

 renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Numero capteur",renderer, "text",NR,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste3),column1);
  renderer = gtk_cell_renderer_text_new();
 column1= gtk_tree_view_column_new_with_attributes("Etat",renderer, "text",TR,NULL);
 gtk_tree_view_append_column (GTK_TREE_VIEW (liste3),column1);
}

store=gtk_list_store_new(COLUMNS2,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);



f= fopen("fumee.txt","r");

if (f==NULL)
{return;}
else 
{
	f=fopen("fumee.txt","a+");
	 while(fscanf(f,"%s %s %s %s\n",F.j,F.h,F.numcapt,F.etat)!=EOF) 
	{ if(strcmp(F.etat,"1")==0)
		{
		strcpy(F.etat,"Fumée détectée");
		gtk_list_store_append (store, &iter);

		gtk_list_store_set (store, &iter,JR,F.j, HR, F.h, NR, F.numcapt,TR,F.etat, -1);
		}
	}
	 fclose(f);
	gtk_tree_view_set_model (GTK_TREE_VIEW (liste3), GTK_TREE_MODEL (store));
	g_object_unref (store);

}

}
