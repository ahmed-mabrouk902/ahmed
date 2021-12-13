#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "fonction.h"
int y,x,p,a,f,d;
//button pour entrer
/*void
on_button1_insc_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur,*inscript;
inscript=lookup_widget(button,"inscription");
gtk_widget_destroy(inscript);
DashboardCapteur=create_DashboardCapteur();
gtk_widget_show (DashboardCapteur);
}

/*
void
on_button2_auth_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *username,*password,*DashboardCapteur, *windowAuth, *inscript;
char user[20];
char pasw[20];
int trouve;
username=lookup_widget (button, "entry3_log");
password=lookup_widget (button, "entry4_Pw");
strcpy(user, gtk_entry_get_text(GTK_ENTRY(username)));
strcpy(pasw, gtk_entry_get_text(GTK_ENTRY(password)));
trouve=verif(user,pasw);

if(trouve==1)
{
windowAuth=lookup_widget(button,"authen");
gtk_widget_destroy(windowAuth);
DashboardCapteur=create_DashboardCapteur();
gtk_widget_show (DashboardCapteur);

}

}*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///AJOUT//////////////////////////////////////////////
void
on_buttonAjouter_clicked               (GtkButton       *objet,
                                        gpointer         user_data)
{
capteur c;
FILE *f=NULL;
GtkWidget *ref, *nom, *output;
GtkWidget *combobox1;
char ref1[100];
char nom1[100];
char msg[100];
char T[100];
char R[100];
int trouve=0;


ref = lookup_widget (objet, "entry1Capteur");
nom = lookup_widget (objet, "entry2Capteur");
combobox1=lookup_widget (objet, "combobox1Capteur");

strcpy(c.reference_capteur, gtk_entry_get_text(GTK_ENTRY(ref)));

trouve=verifier(c.reference_capteur);

if (trouve==0)
{

if(strcmp("Temperature",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox1)))==0)
strcpy(T,"capteurTemperature");
else if (strcmp("Debit Eau",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox1)))==0)
strcpy(T,"capteurDebitEau");
else if (strcmp("Fumee",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox1)))==0)
strcpy(T,"capteurFumee");
else if (strcmp("Mouvement",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox1)))==0)
strcpy(T,"capteurMouvement");
else if (strcmp("Autre",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox1)))==0)
strcpy(T,"Autre");


strcpy(c.typeCapteur, T);
strcpy(c.nom_capteur, gtk_entry_get_text(GTK_ENTRY(nom)));

ajouter_capteur (c);

output = lookup_widget(objet, "label93msgajout");
strcpy (msg,"Parfait ! le capteur est bien ajouté");
gtk_label_set_text(GTK_LABEL(output),msg);
}

	else 
	{
	output = lookup_widget(objet, "label93msgajout");
	strcpy (msg,"Erreur ! le capteur existe déjà.");
	gtk_label_set_text(GTK_LABEL(output),msg);
	}

}


void
on_button11_Retour_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur;

DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

DashboardCapteur = create_DashboardCapteur ();
gtk_widget_show (DashboardCapteur) ;
}

///MODIFIER///////////////////////////////



void
on_radiobutton2Capteur_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
x=2;
}


void
on_radiobutton1Capteur_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
x=1;
}




void
on_checkbutton1_Type_modif_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
y=3;
}


void
on_button15_modifier_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
int y=0;
int x=0;
FILE *f,*E;
GtkWidget *ref, *nom, *output,*R;
GtkWidget *combobox2;
GtkWidget * togglebutton1, * togglebutton2,* togglebutton3;
char ref1[100];
char ref2[100];
char nom1[100];
char r[100];
char n[100];
char msg[100];
char T[100];
char T1[100];
int trouve=0,test=0;
R = lookup_widget(button, "entry13Modif");
output = lookup_widget(button, "labelmsgmodification");
ref = lookup_widget (button, "entry14modifier");
nom = lookup_widget (button, "entry15modifier");
combobox2=lookup_widget (button, "combobox2Capteur");
togglebutton1=lookup_widget(button, "radiobutton1Capteur");
togglebutton2=lookup_widget(button, "radiobutton2Capteur");
togglebutton3=lookup_widget(button, "checkbutton1_Type_modif");
strcpy(ref2, gtk_entry_get_text(GTK_ENTRY(R)));
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton1)))
x=1;
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton2)))
x=2;
if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton3)))
y=1;
//kan radio1 yi5dem
if ((x==1)&&(y!=1))
{
strcpy(ref1, gtk_entry_get_text(GTK_ENTRY(ref)));

trouve=verifier(ref2);

test=verifier(ref1);


if ((test==0) && (trouve==1))
{

f=fopen("listecapteur.txt","r+"); 
E=fopen("temporaire.txt","w+"); 
while(fscanf(f,"%s %s %s\n",r,n,T)!=EOF)
       { if(strcmp(r,ref2)==0)
fprintf(E,"%s %s %s\n",ref1,n,T);
else fprintf(E,"%s %s %s\n",r,n,T);
	 }
fclose(E);
fclose(f);

E=fopen("temporaire.txt","r"); 
f=fopen("listecapteur.txt","w+");
while(fscanf(E,"%s %s %s\n",r,n,T)!=EOF)
      { 
fprintf(f,"%s %s %s\n",r,n,T);
	 }
	fclose(f);
   fclose(E);

strcpy (msg,"Parfait ! la reference est modifié");
}

else 
{
strcpy (msg,"Erreur ! ");
}

gtk_label_set_text(GTK_LABEL(output),msg);


}
//kan radio2 yi5dim
if ((x==2)&&(y!=1))
{strcpy(nom1, gtk_entry_get_text(GTK_ENTRY(nom)));//yi7adhar mel entry yi7oto nom1

trouve=0;
trouve=verifier(ref2);

if (trouve==1)//kan l9ah
{

f=fopen("listecapteur.txt","r+"); 
E=fopen("temporaire.txt","w+"); 
while(fscanf(f,"%s %s %s\n",r,n,T)!=EOF)
       { if(strcmp(r,ref2)==0) 
	fprintf(E,"%s %s %s\n",r,nom1,T);
	else fprintf(E,"%s %s %s\n",r,n,T);
	 }
fclose(E);
fclose(f);//c bon tiktib fi E


E=fopen("temporaire.txt","r+"); 
f=fopen("listecapteur.txt","w+");
while(fscanf(E,"%s %s %s\n",r,n,T)!=EOF)
	{ 
	fprintf(f,"%s %s %s\n",r,n,T);//badalna
	}
fclose(f);
fclose(E);

strcpy (msg,"Parfait ! le nom est modifié");
}

else 
{
strcpy (msg,"Erreur ! ");
}

gtk_label_set_text(GTK_LABEL(output),msg);//message
}



//kan radiocheck yi5dem
if ((y==1)&&((x==1)||(x==2)))
{//yi7adher les valeur fi T1
if(strcmp("Temperature",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox2)))==0)
strcpy(T1,"capteurTemperature");
else if (strcmp("Debit Eau",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox2)))==0)
strcpy(T1,"capteurDebitEau");
else if (strcmp("Fumee",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox2)))==0)
strcpy(T1,"capteurFumee");
else if (strcmp("Mouvement",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox2)))==0)
strcpy(T1,"capteurMouvement");
else if (strcmp("Autre",gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox2)))==0)
strcpy(T1,"Autre");

trouve=0;
trouve=verifier(ref2);
//kan l9ah ***********
	if (trouve==1)
	{

	f=fopen("listecapteur.txt","r+"); 
	E=fopen("temporaire.txt","w+"); 
	while(fscanf(f,"%s %s %s\n",r,n,T)!=EOF)
	       { 
		if(strcmp(r,ref2)==0) //yo93ad yilawej
		fprintf(E,"%s %s %s\n",r,n,T1);//l9ah yibadel valeur
			else fprintf(E,"%s %s %s\n",r,n,T);//yiktbo hoa bido
		 }
	fclose(E);
	fclose(f);

	E=fopen("temporaire.txt","r+"); 
	f=fopen("listecapteur.txt","w+");
	while(fscanf(E,"%s %s %s\n",r,n,T)!=EOF)
		{ 
		fprintf(f,"%s %s %s\n",r,n,T);
		}
	fclose(f);
	fclose(E);

	strcpy (msg,"Parfait ! le type du capteur modifié");
	}

		else 
		{
		strcpy (msg,"Erreur ! ");
		}

gtk_label_set_text(GTK_LABEL(output),msg);

}
}


void
on_button4_Retour_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur;

DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

DashboardCapteur = create_DashboardCapteur ();
gtk_widget_show (DashboardCapteur) ;
}

//////////CHERCHER///////////////////////////////////////////////////////////////
void
on_button16_chercher_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ref, *output;
FILE *f=NULL;
char ref1[100];
char r[100];
char n[100];
char msg[100];
char T[100];
int trouve=0;
ref = lookup_widget (button, "entry16Cherchercap");
strcpy(ref1, gtk_entry_get_text(GTK_ENTRY(ref)));
output = lookup_widget(button, "label94msgchercher");

trouve=verifier(ref1);

if (trouve==0)
{
strcpy (msg,"Erreur ! le capteur n'existe pas");
gtk_label_set_text(GTK_LABEL(output),msg);
}

	else
	{
	f=fopen("listecapteur.txt","r");  
		if(f!=NULL){
		while(fscanf(f,"%s %s %s\n",&r,&n,&T)!=EOF) 
		{
			if(strcmp(ref1,r)==0) 
			sprintf(msg,"La référence du capteur : %s \n \nLe numéro : %s \n \nLe type : %s\n",r,n,T);}
	fclose(f);}
	gtk_label_set_text(GTK_LABEL(output),msg);
	}
}


void
on_button17_verifier_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
int trouve=0;
GtkWidget *ref, *output;
char ref1[100];
char msg[100];
ref = lookup_widget (button, "entry16Cherchercap");
strcpy(ref1, gtk_entry_get_text(GTK_ENTRY(ref)));
output = lookup_widget(button, "label49Verif");

trouve=verifier(ref1);

if(trouve==1)
{strcpy (msg,"Le capteur existe, vous pouvez continuer.");
gtk_label_set_text(GTK_LABEL(output),msg);
}
	else if(trouve==0)
	{
	strcpy (msg,"le capteur n'existe pas, veuillez vérifier.");
	gtk_label_set_text(GTK_LABEL(output),msg);
	}
}


void
on_button5_Retour_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur;

DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

DashboardCapteur = create_DashboardCapteur ();
gtk_widget_show (DashboardCapteur) ;
}

//////////////SUPPRIMER//////////////////////////////////////////////////////////
void
on_button18_supprimer_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ref, *output;
char ref1[100];
char msg[200];
char r[100];
char n[100];
char T[100];
FILE *f,*E;
int trouve=0;

ref = lookup_widget (button, "entry7Capteur");
strcpy(ref1, gtk_entry_get_text(GTK_ENTRY(ref)));
output = lookup_widget(button, "labelmsgsuppression");
trouve=verifier(ref1);

if (trouve==0)
{
strcpy (msg,"Erreur ! le capteur n'existe pas");
gtk_label_set_text(GTK_LABEL(output),msg);
}

else {

f=fopen("listecapteur.txt","r"); 
E=fopen("temporaire.txt","w+"); 
while(fscanf(f,"%s %s %s\n",r,n,T)!=EOF)
       { if (strcmp(ref1,r)!=0)
fprintf(E,"%s %s %s\n",r,n,T);
	 }fclose(f);
	fclose(E);

E=fopen("temporaire.txt","r");
f=fopen("listecapteur.txt","w"); 
while(fscanf(E,"%s %s %s\n",r,n,T)!=EOF)
      { 
fprintf(f,"%s %s %s\n",r,n,T);
	 }
	fclose(f);
   fclose(E);


strcpy (msg,"Parfait ! le capteur est bien supprimé");
gtk_label_set_text(GTK_LABEL(output),msg);

}
}


void
on_button6_Retour_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur;

DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

DashboardCapteur = create_DashboardCapteur ();
gtk_widget_show (DashboardCapteur) ;
}

/////////////LISTE/////////////////////////////////
void
on_button7_Retour_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur;

DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

DashboardCapteur = create_DashboardCapteur ();
gtk_widget_show (DashboardCapteur) ;
}


void
on_button12_affListe_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur,*Liste,*treeview;

Liste = create_Liste();
gtk_widget_show (Liste) ;
DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

treeview=lookup_widget(Liste,"treeview1_Liste");
afficher_capteur (treeview);
}

////////////HISTORIQUE////////////////////////////////
void
on_button8_Retour_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur;

DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

DashboardCapteur = create_DashboardCapteur ();
gtk_widget_show (DashboardCapteur) ;
}


void
on_button13_Histo_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur,*Historique,*treeview;

Historique = create_Historique();
gtk_widget_show (Historique) ;
DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

treeview=lookup_widget(Historique,"treeview2_Histo");
afficher_capteur_his(treeview);
}

//////////CAPTDEFFECTUEUX////////////////////////////////
void
on_button14_affdeff_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur,*capteurDeffectueux,*treeview;

capteurDeffectueux = create_capteurDeffectueux();
gtk_widget_show (capteurDeffectueux) ;
DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

treeview=lookup_widget(capteurDeffectueux,"treeview3_captDeff");
afficher_capteur_deff(treeview);
}


void
on_button9_Retour_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur;

DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

DashboardCapteur = create_DashboardCapteur ();
gtk_widget_show (DashboardCapteur) ;
}
///////////////LISTE TREE////////////////////////

void
on_treeview1_Liste_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* ref;
gchar* nom;
gchar* type;
capteur c;

GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model, &iter, path)) {

gtk_tree_model_get (GTK_LIST_STORE(model), &iter,0, &ref,1,&nom,2,&type,-1);

strcpy(c.reference_capteur,ref);
strcpy(c.nom_capteur,nom);
strcpy(c.typeCapteur,type);
//supprim_capteur(c);
afficher_capteur (treeview);
}
}


void
on_button19_retour_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur,*Liste;

DashboardCapteur = create_DashboardCapteur();
gtk_widget_show (DashboardCapteur) ;
Liste=lookup_widget(button,"Liste");
gtk_widget_destroy(Liste);
}

///////////HISTORIQUE TREE//////////////////////////////
void
on_treeview2_Histo_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* jr;
gchar* hr;
gchar* num;
gchar* val;
temp T2;

GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model, &iter, path)) {

gtk_tree_model_get (GTK_LIST_STORE(model), &iter,0, &jr,1,&hr,2,&num,3,&val,-1);

strcpy(T2.jour,jr);
strcpy(T2.heure,num);
strcpy(T2.numT,num);
strcpy(T2.t,val);

afficher_capteur_his(treeview);
}
}


void
on_button20_retour_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur,*Historique;

DashboardCapteur = create_DashboardCapteur();
gtk_widget_show (DashboardCapteur) ;
Historique=lookup_widget(button,"Historique");
gtk_widget_destroy(Historique);
}

///////////////////CAPTDEFF TREE///////////////////////////////
void
on_treeview3_captDeff_row_activated    (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
gchar* jr;
gchar* hr;
gchar* num;
gchar* val;
temp T1;

GtkTreeModel *model = gtk_tree_view_get_model(treeview);

if (gtk_tree_model_get_iter(model, &iter, path)) {

gtk_tree_model_get (GTK_LIST_STORE(model), &iter,0, &jr,1,&hr,2,&num,3,&val,-1);

strcpy(T1.jour,jr);
strcpy(T1.heure,hr);
strcpy(T1.numT,num);
strcpy(T1.t,val);

afficher_capteur_deff(treeview);
}
}


void
on_button21_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *DashboardCapteur,*capteurDeffectueux;

DashboardCapteur = create_DashboardCapteur();
gtk_widget_show (DashboardCapteur) ;
capteurDeffectueux=lookup_widget(button,"capteurDeffectueux");
gtk_widget_destroy(capteurDeffectueux);
}

/////////bouton quitter////////////
void
on_Quitter_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
/*GtkWidget *DashboardCapteur,*inscription;

DashboardCapteur=lookup_widget(button,"DashboardCapteur");
gtk_widget_destroy(DashboardCapteur);

inscription = create_inscription ();
gtk_widget_show (inscription) ;*/
}

/////////////////ACTUALISER/////////////////////////////////////////////////////////
void
on_button23_actualiser_Liste_clicked   (GtkButton       *objet,
                                        gpointer         user_data)
{
GtkWidget *Liste;
GtkWidget *treeview6;


Liste=lookup_widget(objet,"Liste");

treeview6=lookup_widget(Liste,"treeview1_Liste");

afficher_liste_alarmes_mouvements(treeview6);
}


void
on_button22_actualiser_Histo_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button24_act_captdeff_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{

}

////////////////////////calcul
void
on_button22_calcul_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
int b,c,h;
float a;
char ch[100];
char msg[100];
FILE *f;
GtkWidget *choix,*output1,*output2,*output3,*output4,*output5,*output6,*output7;

//outputs
output1=lookup_widget(button,"temperatureCapteur");
output2=lookup_widget(button,"debiteauCapteur");
output3=lookup_widget(button,"fumeeCapteur");
output4=lookup_widget(button,"mouvementCapteur");
output5=lookup_widget(button,"autreCapteur");
output6=lookup_widget(button,"totalCapteur");
output7=lookup_widget(button,"choixCapteur");

{
choix=lookup_widget(button,"spinbutton1Capteur");
c=gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(choix));
//outputs
strcpy (ch,"saisir choix avec spinbutton");
strcpy (msg,ch);
gtk_label_set_text(GTK_LABEL(output7),msg);

if (c==1)//temperature
	{a=calcul(c);
	sprintf(ch,"%\t%.2f",a);
	strcpy (msg,ch);
	gtk_label_set_text(GTK_LABEL(output1),msg);}

else if(c==2)//debiteau
	{a=calcul(c);
	sprintf(ch,"%\t%.2f",a);
	strcpy (msg,ch);
	gtk_label_set_text(GTK_LABEL(output2),msg);}
else if(c==3)//fumee
	{a=calcul(c);
	sprintf(ch,"%\t%.2f",a);
	strcpy (msg,ch);
	gtk_label_set_text(GTK_LABEL(output3),msg);}
else if (c==4)//mouvement
	{ a=calcul(c);
	sprintf(ch,"%\t%.2f",a);
	     strcpy (msg,ch);
	gtk_label_set_text(GTK_LABEL(output4),msg);}
else if (c==5)//autre
	{ a=calcul(c);
	sprintf(ch,"%\t%.2f",a);
	strcpy (msg,ch);
	gtk_label_set_text(GTK_LABEL(output5),msg);}
else if (c==6)//total
	{b=compt();
	sprintf(ch,"%d",b);
	strcpy (msg,ch);
	gtk_label_set_text(GTK_LABEL(output6),msg);}

};
}

