/**********************************************
*	- Author: Nizar Bousebsi.				  *      
*	- File: error.cpp						  *
*   - Description: Display all error message. *
***********************************************/

#include "wififriend.h"

void			error_double_contact(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_WARNING,
									GTK_BUTTONS_CLOSE,
									"\nCe contact est deja utilise, veuillez en choisir un autre !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_disconnect_success(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_CLOSE,
									"\nVous-avez ete deconnecte !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_get_profil_success(int Flags, const gchar *ProfilName)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_CLOSE,
									"%s %s %s", "\nVotre profil ", ProfilName, "est sur le repertoire courant !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_get_profil(int Flags, const gchar *ProfilName)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"%s %s %s", "\nImpossible de recuperer le profile Wifi", ProfilName, "!\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_delete_profil_success(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_CLOSE,
									"\nContact supprime avec succes !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}


void			error_extract_profil(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"\nImpossible d'extraire votre profile Wifi !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_interface_wifi(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_CLOSE,
									"\nWififriend ne parvient pas a recuperer votre interface Wifi !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_give_contact(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_WARNING,
									GTK_BUTTONS_CLOSE,
									"\nVeuillez preciser le nom du contact !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_set_profile_success(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_CLOSE,
									"\nContact ajoute avec succes !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_set_profile_failed(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"\nImpossible de charger ce profile, veuillez verifier que votre fichier est valide !\n");
	gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
	gtk_dialog_run (GTK_DIALOG (Dialog));
	gtk_widget_destroy(Dialog);
    if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_empty_contact_file(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_WARNING,
									GTK_BUTTONS_CLOSE,
									"\nVous n'avez aucun contact Wifi dans la liste.\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_open_contact_file(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_WARNING,
									GTK_BUTTONS_CLOSE,
									"\nListe des contacts introuvables ! Avez-vous supprimer le fichier contact.wf ?\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_cannot_disconnect(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_CLOSE,
									"\nImposssible de forcer la deconnexion !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_connect_success(int Flags, char *NetworkName)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_INFO,
									GTK_BUTTONS_CLOSE,
									"\nConnection reussit !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_connect_unknow(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"\nEchec de connexion, veuillez verifier votre peripherique de connexion !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_parameters_connect(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"\nErreur dans les parametres de connexion, veuillez verifier le profile de ce reseau !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_unauthorized_connect(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_WARNING,
									GTK_BUTTONS_CLOSE,
									"\nVous n'etes pas autorise a vous connecter sur ce reseau protege !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_invalid_handle(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"\nWififriend n'a pas pu charger l'environnement WLAN, veuillez redemarrer le programme !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_open_profile(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"\nImpossible de charger ce profile, veuillez verifier le chemin du fichier !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_config(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"\nConfiguration Wifi introuvable !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			error_scan(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"\nImpossible de scanner les points Wifi, veuillez verifier votre peripherique de connexion !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}


void			error_connect(int Flags)
{
	gpointer	Data = NULL;
	GtkWidget	*Dialog = NULL;

	gtk_init(0, NULL);
	Dialog = gtk_message_dialog_new (GTK_WINDOW(Data),
									GTK_DIALOG_DESTROY_WITH_PARENT,
									GTK_MESSAGE_ERROR,
									GTK_BUTTONS_CLOSE,
									"\nImpossible de ce connecter, veuillez verifier votre peripherique de connexion !\n");
 gtk_window_set_position(GTK_WINDOW(Dialog), GTK_WIN_POS_CENTER);
 gtk_dialog_run (GTK_DIALOG (Dialog));
 gtk_widget_destroy(Dialog);
 if (Flags == 1)
		exit(EXIT_FAILURE);
}

void			display_help(GtkWidget* Widget, gpointer Data)
{
	GtkWidget	*Window = NULL;
	GtkWidget	*Vbox = NULL;
	GtkWidget	*Help = NULL;

	Window = create_window(365, 318, "Aide Wififriend");
	gtk_window_set_default_size(GTK_WINDOW(Window), 365, 318);
	Vbox = gtk_vbox_new(FALSE, 0);
	Help = gtk_label_new("- Comment ajouter un nouveau contact ?:\n\n1) Contact/Nouveau contact.\n\n2) Saisissez le nom du reseau et uploader le profile XML.\n\n\n- Comment Supprimer un contact ?:\n\n1) Contact/Supprimer un contact.\n\n\n- Comment se connecter ?:\n\n1) Double-clique sur le reseau ajoute.");
	gtk_box_pack_start(GTK_BOX(Vbox), Help, FALSE, FALSE, 10);
	gtk_container_add(GTK_CONTAINER(Window), Vbox);
	display_interface(Window);
}