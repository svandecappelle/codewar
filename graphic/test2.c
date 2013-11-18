#include<gtk/gtk.h>
#include<gdk/gdk.h>
#include<stdlib.h>
#include <string.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include "CodeWar.h"
#include "definitions.h"
#include "argumentsGraphiques.h"
#include <math.h>
#include "test2.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



GtkWidget *p_winDemarrer;
extern GtkBuilder  *  p_builder; 
extern struct argument *argmt; 


/*  ## Fonction en cas d'erreur de chargement du Fichier Assembleur ... ## */


void compiler(GtkTextView *item, GtkTextView *texte){
  GtkTextIter *iter;
  GtkWidget *pDialog;
  GtkTextBuffer *pTextBuffer = gtk_text_view_get_buffer(texte);
  gchar* sBuffer;
  int fd;
  //gtk_text_view_get_iter_at_position(texte,iter,NULL,0,1);
  GtkTextIter iStart; 
  GtkTextIter iEnd;
  pid_t pid_fils;
  int statut;



  gtk_text_buffer_get_start_iter(pTextBuffer, &iStart);
  gtk_text_buffer_get_end_iter(pTextBuffer, &iEnd);
  sBuffer = gtk_text_buffer_get_text(pTextBuffer, &iStart, &iEnd, TRUE);
  
  
  /* pDialog = gtk_message_dialog_new(NULL,
     GTK_DIALOG_MODAL,
     GTK_MESSAGE_INFO,
     GTK_BUTTONS_OK,
     "Votre texte :\n%s", sBuffer);
     
     gtk_dialog_run(GTK_DIALOG(pDialog));
     gtk_widget_destroy(pDialog);
     
     /* On libere la memoire */
  printf("%s\n",sBuffer);
  fd = open("temp.a",O_CREAT|O_RDWR,0777);
  if (write(fd,sBuffer,strlen(sBuffer))==-1){
    perror("erreur d'ecriture\n");
    exit;
  }
  



  //#######################################################################
  // compilation avec CWASM

  if( (pid_fils=fork()) == 0){ //On est dans le fils

    execlp("./cwasm", "./cwasm", "temp.a","temp",(char*) NULL);
    printf("blaaaaaaaaaaaaaaaaaa\n");
    exit(0);
    //gtk_label_set_text((GtkLabel*)resultat,"Compilation en cours ...\nCompilation terminee.");
    
    
    
    
  }
  else if(pid_fils == -1){
    //Erreur
    perror("Erreur de création de processus");
  }
  else{ //On est dans le parent
    if(waitpid(pid_fils, &statut, 0) == -1){
      //Erreur
      perror("Dans l'attente du fils");
    }
    else{// Le fils s'est terminé
      char* encour = "Compilation en cours ...\n";
      char* fin = "Compilation terminee.                                              ";
      char *deux = (char*) malloc(strlen(encour)+strlen(fin)+1) ;
      strcpy(deux,encour);
      strcat(deux,fin);
      /*   execl("/bin/bash", "/bin/bash", "./B", NULL); */
      GtkWidget* f= (GtkWidget *)gtk_builder_get_object(p_builder, "window1");
      GtkWidget *resultat= (GtkWidget *)gtk_builder_get_object(p_builder, "res");
      gtk_label_set_text((GtkLabel*)resultat,encour);
      gtk_label_set_justify((GtkLabel*)resultat,GTK_JUSTIFY_LEFT);
      gtk_widget_draw(f,NULL);
      sleep(1/2);
      pDialog = gtk_message_dialog_new(NULL,
				       GTK_DIALOG_MODAL,
				       GTK_MESSAGE_INFO,
				       GTK_BUTTONS_OK,
				       "Message systeme:\n%s", "Compilation termine");
      gtk_dialog_run(GTK_DIALOG(pDialog));
      gtk_widget_destroy(pDialog);
      gtk_label_set_text((GtkLabel*)resultat,deux);
      gtk_widget_draw(f,NULL);
      free(deux);
      
    }
  }    
  close(fd);
  g_free(sBuffer);
  
}




void OK_bouton(GtkButton *bouton,GtkWidget *pWindow){
  
  gtk_widget_destroy(pWindow);
}


void affiche_erreur(){


  GtkBuilder *unBuilder;
  GError      *  p_err       = NULL;
  GtkWidget *pWindow;
  
  
   /* Creation d'un nouveau GtkBuilder */
   unBuilder = gtk_builder_new ();

   if (unBuilder != NULL)
   {
      /* Chargement du XML dans unBuilder */
      gtk_builder_add_from_file (unBuilder, "FinJeu.xml", & p_err);
      
      if (p_err == NULL)
      {
	GtkLabel *label;
	
         /* Recuparation d'un pointeur sur la fenetre. */
	pWindow = (GtkWidget *) gtk_builder_get_object ((GtkBuilder*)unBuilder, "window1");

	label = (GtkLabel*)gtk_builder_get_object (unBuilder, "Resultat");
	gtk_label_set_text(label,"Erreur de chargement de fichier Assembleur, veuillez charger au moin un fichier Valide");
	
	 /* Signal du menu Nouveau Jeu */
	
         g_signal_connect (
			   gtk_builder_get_object (unBuilder, "ok_button"),
			   "clicked", G_CALLBACK (OK_bouton), pWindow 
			   );
	

	 g_signal_connect(G_OBJECT(pWindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);
         gtk_widget_show_all (pWindow);
         gtk_main ();

      }
      else
      {
         /* Affichage du message d'erreur de GTK+ */
         g_error ("%s", p_err->message);
         g_error_free (p_err);
      }
   }
  
}





























/* ###  Fonction du signal de choix de la couleur processeur ###*/
void colorChanged(GtkColorButton *button, demarage *demarre){
  GdkColor color;  
  couleur_processeur coul;
    gtk_color_button_get_color(button,&color);
    coul.composed.b = color.blue>>11;
    coul.composed.r = color.red>>11;
    coul.composed.v = color.green>>11;
   /*  printf("Couleur red: %d, green: %d, blue: %d\n", coul.composed.r, coul.composed.v, coul.composed.b); */

    demarre->couleur = coul.tout;
    
}

/* ###  Fonction du signal de choix du fichier de programme processeur ###*/
void file_changed(GtkButton *button, demarage *d) {
  gchar *file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
  d->cheminAssembleur = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
}


/* ###  Fonction du signal de choix de coordonnées processeur ###*/
void coord_changed(GtkButton *button, demarage *d) {
  if (strcmp(gtk_widget_get_name((GtkWidget *)button),"coord1X")==0){
    d->xy.x = gtk_spin_button_get_value_as_int((GtkSpinButton*)button)-1;
  }else if (strcmp(gtk_widget_get_name((GtkWidget *)button),"coord2X")==0){
    d->xy.x = gtk_spin_button_get_value_as_int((GtkSpinButton*)button)-1;
  }else if (strcmp(gtk_widget_get_name((GtkWidget *)button),"coord2Y")==0){
    d->xy.y = gtk_spin_button_get_value_as_int((GtkSpinButton*)button)-1;
  }else if (strcmp(gtk_widget_get_name((GtkWidget *)button),"coord1Y")==0){
    d->xy.y = gtk_spin_button_get_value_as_int((GtkSpinButton*)button)-1;
  }
  
}


void Cancel(GtkWidget *widget,GtkWidget *fenetre){
  gtk_widget_destroy(fenetre);
}


/*Fonction du signal du boutton OK dans le panel Démarrer permettant 
                   de charger les données des processeurs */
int Demarer(GtkWidget *widget,plateauGraphique *p){
  GtkColorButton *couleur1;
  GdkColor color;
  int prog;
  int i;
  int nberr = 0;
  char *argv[] = {
    "CodeWar",
    p->demarre[0].cheminAssembleur,
    p->demarre[1].cheminAssembleur,
  };
 /*  printf("Coordonnees Proc 1 :x =%d, y=%d\n",p->demarre[0].xy.x,p->demarre[0].xy.y); */
/*   printf("Proc 1 :couleur = %04X, cheminAssembleur = %s\n\n",p->demarre[0].couleur,p->demarre[0].cheminAssembleur); */
  
/*   printf("Coordonnees Proc 2 :x =%d, y=%d\n",p->demarre[1].xy.x,p->demarre[1].xy.y); */
/*   printf("Proc 2 :couleur = %04X, cheminAssembleur = %s\n\n",p->demarre[1].couleur,p->demarre[1].cheminAssembleur); */
  for (i = 0 ; i<2 ; i+=1){
    if (strcmp(p->demarre[i].cheminAssembleur,"/home")== 0){
      nberr+=1;
    } 
  }
  if (nberr > 1){
    affiche_erreur();
    return 0;
  }
  
  p->plateau = p_builder;
  gtk_widget_destroy(p_winDemarrer);
  prog = main2(3,argv,p);
  return 1;
}


/*Fonction du signal de l'item Jeu->Démarrer permettant de saisir les */
                        /*données des processeurs */

void NewGame(argument *arg){
  GtkBuilder  *  p_builder2   = NULL;
  GError      *  p_err       = NULL;
  plateauGraphique p;
  demarage d;
  demarage d2;
  coordonnees c;
  couleur_processeur mixer; 
  const gchar *car;
  GtkWidget *fichier;
  GdkColor color;
  GtkColorButton *couleur1;
  GtkSpinButton *coord;
  int a;
  p.demarre[1].cheminAssembleur = (char *) malloc(sizeof (char)* 2000);
  p.demarre[0].cheminAssembleur = (char *) malloc(sizeof (char)* 2000);

  strcpy(p.demarre[1].cheminAssembleur,"/home");
  strcpy(p.demarre[0].cheminAssembleur,"/home");
  /* Creation d'un nouveau GtkBuilder */
   p_builder2 = gtk_builder_new ();

   if (p_builder2 != NULL)
   {
      /* Chargement du XML dans unBuilder */
      gtk_builder_add_from_file (p_builder2, "Demarer.xml", & p_err);
      if (p_err == NULL)
	{
	  /* Recuparation d'un pointeur sur la fenetre. */
	  p_winDemarrer = (GtkWidget *) gtk_builder_get_object (p_builder2, "dialog1");
	  
	  /* couleur de processeur 1 de processeur 1*/
	  couleur1 = (GtkColorButton *)gtk_builder_get_object (p_builder2, "pross1");	  	 
	  
	  gtk_color_button_get_color(couleur1,&color);
	  mixer.composed.b = color.blue>>11;
	  mixer.composed.r = color.red>>11;
	  mixer.composed.v = color.green>>11;
	  p.demarre[0].couleur = mixer.tout;
	  
	  
	  g_signal_connect(GTK_OBJECT(couleur1), "color-set",
			   G_CALLBACK(colorChanged), &p.demarre[0]);
	  
	  
	 /* Pour sauvegarder le chemin du fichier choisi ! */
	 fichier =  (GtkWidget *)gtk_builder_get_object(p_builder2, "Fichier1");
	 g_signal_connect(GTK_OBJECT(fichier), "selection_changed",
			  G_CALLBACK(file_changed), &p.demarre[0]);
	 fichier =  (GtkWidget *)gtk_builder_get_object(p_builder2, "Fichier2");
	 g_signal_connect(GTK_OBJECT(fichier), "selection_changed",
			   G_CALLBACK(file_changed), &p.demarre[1]);
	 /* COuleur Processeur 2 */


	 couleur1 =  (GtkColorButton *)gtk_builder_get_object (p_builder2, "pross2");	 
	 gtk_color_button_get_color(couleur1,&color);
	 mixer.composed.b = color.blue>>11;
	 mixer.composed.r = color.red>>11;
	 mixer.composed.v = color.green>>11;
	 p.demarre[1].couleur = mixer.tout;
	 g_signal_connect(GTK_OBJECT(couleur1), "color-set",
			  G_CALLBACK(colorChanged), &p.demarre[1]);	 
	 /* Coordonnees des processeurs */
	

	 /* random ... */
	 a = 1 + rand()%16;
	 coord =  (GtkSpinButton *)gtk_builder_get_object (p_builder2, "coord1X");
	 gtk_spin_button_set_value((GtkSpinButton*)coord, a);
	 p.demarre[0].xy.x = gtk_spin_button_get_value_as_int((GtkSpinButton*)coord)-1;
	 g_signal_connect(GTK_OBJECT(coord), "value_changed",
			  G_CALLBACK(coord_changed), &p.demarre[0]);
	 
	 
 	 a = 1 + rand()%16;
	 coord =  (GtkSpinButton *)gtk_builder_get_object (p_builder2, "coord1Y");
	 gtk_spin_button_set_value((GtkSpinButton*)coord, a);
	 p.demarre[0].xy.y = gtk_spin_button_get_value_as_int((GtkSpinButton*)coord)-1;
	 g_signal_connect(GTK_OBJECT(coord), "value_changed",
			  G_CALLBACK(coord_changed), &p.demarre[0]);
	 
	 
	 
 	 a = 1 + rand()%16;
	 coord =  (GtkSpinButton *)gtk_builder_get_object (p_builder2, "coord2X");
	 gtk_spin_button_set_value((GtkSpinButton*)coord, a);
	 p.demarre[1].xy.x = gtk_spin_button_get_value_as_int((GtkSpinButton*)coord)-1;
	 g_signal_connect(GTK_OBJECT(coord), "value_changed",
			  G_CALLBACK(coord_changed), &p.demarre[1]);
	 
	 
	 
	 
 	 a = 1 + rand()%16;
	 coord =  (GtkSpinButton *)gtk_builder_get_object (p_builder2, "coord2Y");
	 gtk_spin_button_set_value((GtkSpinButton*)coord, a);
	 p.demarre[1].xy.y = gtk_spin_button_get_value_as_int((GtkSpinButton*)coord)-1;
	 g_signal_connect(GTK_OBJECT(coord), "value_changed",
			  G_CALLBACK(coord_changed), &p.demarre[1]);
	 
	 
	 /* lancement du signal de traitement des donnée sauvegardées */
	 
	 p.plateau=arg->window;
	 g_signal_connect (gtk_builder_get_object (p_builder2, "OK"),"clicked", G_CALLBACK (Demarer), &p);
	 
	 /* Signal d'annulation de la fenetre de démarrage */
	 g_signal_connect (gtk_builder_get_object (p_builder2, "Cancel"),"clicked", G_CALLBACK (Cancel), p_winDemarrer);
	 
	 g_signal_connect(G_OBJECT(p_winDemarrer),"destroy",G_CALLBACK(gtk_main_quit),NULL);
         gtk_widget_show_all (p_winDemarrer);
         gtk_main ();
	 
	 
	}
      else
	{
	  /* Affichage du message d'erreur de GTK+ */
	  g_error ("%s", p_err->message);
	  g_error_free (p_err);
	}
   }
   

}

static void NouveauJeu(){
  gtk_main_quit ();
}


static void about(GtkWidget *p){

  GtkBuilder  *  p_builder2   = NULL;
  GError      *  p_err       = NULL;
  GtkWidget *pWindow;
  /* Creation d'un nouveau GtkBuilder */
  p_builder2 = gtk_builder_new ();

   if (p_builder2 != NULL)
   {
      /* Chargement du XML dans p_builder */
      gtk_builder_add_from_file (p_builder2, "about.xml", & p_err);

      if (p_err == NULL)
      {
	/* Recuparation d'un pointeur sur la fenetre. */
	pWindow = (GtkWidget *) gtk_builder_get_object (p_builder2, "window1");
	

	g_signal_connect (gtk_builder_get_object (p_builder2, "Close"),"clicked", G_CALLBACK (Cancel),pWindow);



 
	 g_signal_connect(G_OBJECT(pWindow),"destroy",G_CALLBACK(gtk_main_quit),NULL);
         gtk_widget_show_all (pWindow);
         gtk_main ();


      }
      else
      {
         /* Affichage du message d'erreur de GTK+ */
         g_error ("%s", p_err->message);
         g_error_free (p_err);
      }
   }

}

static void cb_quit (GtkWidget * p_wid, gpointer p_data)
{
   gtk_main_quit ();
}


int main (int argc, char ** argv)
{
  GtkColorButton *couleur1;
  GdkColor color;
  GError      *  p_err       = NULL;
  GtkWidget *window;
  argument arg;




  
  int couleur;

  p_builder=NULL;
  argmt = NULL;



  arg.argc = argc;
  arg.argv = argv;
  arg. window = p_builder;
  argmt = &arg;
  /* Initialisation de GTK+ */
  gtk_init (& argc, & argv);
   /* Creation d'un nouveau GtkBuilder */
   p_builder = gtk_builder_new ();

   if (p_builder != NULL)
   {
      /* Chargement du XML dans p_builder */
      gtk_builder_add_from_file (p_builder, "CodeWar.xml", & p_err);
      
      if (p_err == NULL)
      {
	
	
         /* Recuparation d'un pointeur sur la fenetre. */
         GtkWidget * p_win = (GtkWidget *) gtk_builder_get_object (
            p_builder, "window1"
         );
	 arg. window = p_builder;

	 /* Signal du menu Nouveau Jeu */
         g_signal_connect (
			   gtk_builder_get_object (p_builder, "NouveauJeu"),
			   "activate", G_CALLBACK (NewGame), &arg
			   );
	 
	 g_signal_connect (
			   gtk_builder_get_object (p_builder, "Quit"),
			   "activate", G_CALLBACK (gtk_main_quit), &arg
			   );
		 
	 g_signal_connect (
			   gtk_builder_get_object (p_builder, "About"),
			   "activate", G_CALLBACK (about), &arg
			   );

		 
	 g_signal_connect (
			   gtk_builder_get_object (p_builder, "compiler"),
			   "activate", G_CALLBACK (compiler), gtk_builder_get_object (p_builder, "textcompilation")
			   );




	 g_signal_connect(G_OBJECT(p_win),"destroy",G_CALLBACK(gtk_main_quit),NULL);
         gtk_widget_show_all (p_win);
         gtk_main ();
      }
      else
      {
         /* Affichage du message d'erreur de GTK+ */
         g_error ("%s", p_err->message);
         g_error_free (p_err);
      }
   }


   return EXIT_SUCCESS;
}
