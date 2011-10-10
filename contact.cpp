/******************************************************
*	- Author: Nizar Bousebsi.						  *      
*	- File: contact.cpp								  *
*   - Description: Management of contact list.        *
*******************************************************/

#include <stdio.h>
#include <string.h>
#include <glib/gprintf.h>
#include "wififriend.h"

/* Variable globale pour la liste. */

GtkWidget	*ListOfView;

/* Récupération et setup du profile dans l'environnement WLAN de Windows. */

void							wififriend_load_profile(GtkWidget* Widget, gpointer Data)
{
	t_newcontact				*Contact;
	FILE						*File;
	long						Size;
	BSTR						UnicodeStr;
	char						*NewProfile;
	t_wifi						Connection;
	DWORD						ReasonCode;
	char						*FileName;
	const gchar					*ContactName;

	Contact = (t_newcontact *)Data;
	FileName = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(Widget));
	ContactName = gtk_entry_get_text(GTK_ENTRY(Contact->EntryNc));
	File = fopen("./Data/contact.wf", "a");
	fputs(ContactName, File);
	fputs("\n", File);
	fclose(File);
	if ((File = fopen(FileName, "rb")) == NULL)
		error_open_profile(0);
	else
		{
			fseek(File, 0, SEEK_END);
			Size = ftell(File);
			rewind(File);
			NewProfile = (char *)malloc(sizeof(char) * Size + 1);
			fread(NewProfile, 1, Size, File);
			UnicodeStr = SysAllocStringLen(NULL, Size);
			MultiByteToWideChar(CP_ACP, 0, NewProfile, Size, UnicodeStr, Size);
			Connection = wififriend_create_handle();
			Connection = wififriend_retrieve_config(Connection);
			if ((WlanSetProfile(Connection.MyHandle, &Connection.MyGuid, 0, UnicodeStr, NULL, TRUE, NULL, &ReasonCode)) != ERROR_SUCCESS)
			error_set_profile_failed(0);
			else
				error_set_profile_success(0);
			WlanCloseHandle(Connection.MyHandle, NULL);
		}
}

/* Ajoute le nouveau contact Wifi dans la liste. */

void				wififriend_display_new_contact(GtkWidget* Widget, gpointer Data)
{
	t_newcontact	*Contact;
	const gchar		*ContactName;
	GtkListStore	*Store;
	GtkTreeIter		Iter;

	Contact = (t_newcontact *)Data;
	ContactName = gtk_entry_get_text(GTK_ENTRY(Contact->EntryNc));
	Store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(ListOfView)));
	gtk_list_store_append(Store, &Iter);
	gtk_list_store_set(Store, &Iter, TEXT_COLUMN, ContactName, -1);
}

/* Fonction qui vérifie les contacts en doubles dans la liste. */

void				wififriend_double_contact(GtkWidget* Widget, gpointer Data)
{
	t_newcontact	*Contact;
	const gchar		*ContactName;
	char			*NewContact;
	FILE			*File;
	long			Size;
	char			*Str;
	int				Flag;

	Contact = (t_newcontact *)Data;
	ContactName = gtk_entry_get_text(GTK_ENTRY(Contact->EntryNc));
	NewContact = (char *)malloc(sizeof(char *) * strlen(ContactName) + 1);
	strcpy(NewContact, ContactName);
	strcat(NewContact, "\n");
	File = fopen("./Data/contact.wf", "r");
	fseek(File, 0, SEEK_END);
	Size = ftell(File);
	rewind(File);
	Str = (char *)malloc(sizeof(char) * Size + 1);
	Flag = 0;
	if (strlen(ContactName) == 0)
	{
		error_give_contact(0);
		Flag = 1;
	}
	while(fgets(Str, Size, File))
	{
		if (strcmp(NewContact, Str) == 0)
		{
			error_double_contact(0);
			Flag = 1;
		}
	}
	if (Flag != 1)
	{
		wififriend_display_new_contact(Widget, Data);
		wififriend_load_profile(Widget, Data);
	}
}

/* Fonction d'ajout d'un nouveau contact. */

int					wififriend_add_new_contact(void)
{
	t_newcontact	Contact;
	GtkWidget		*Button;
	GtkFileFilter	*Filter;

	Contact.Window = create_window(340, 150, "Nouveau contact");
	Contact.Vbox = gtk_vbox_new(FALSE, 0);
	Contact.nc = gtk_label_new("Nom du contact (Identique a celui du profile)");
	gtk_box_pack_start(GTK_BOX(Contact.Vbox), Contact.nc, FALSE, FALSE, 10);
	Contact.EntryNc = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(Contact.EntryNc), 15);
	gtk_box_pack_start(GTK_BOX(Contact.Vbox), Contact.EntryNc, FALSE, FALSE, 10);
	Button = gtk_file_chooser_button_new(("Chargement du profile"), GTK_FILE_CHOOSER_ACTION_OPEN); 
	Filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(Filter, "*.xml");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(Button), Filter);
	gtk_box_pack_start(GTK_BOX(Contact.Vbox), Button, FALSE, FALSE, 5);
	Contact.FileName = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(Button));
	g_signal_connect((gpointer)Button, "selection_changed", G_CALLBACK(wififriend_double_contact), (gpointer)&Contact);
	gtk_container_add(GTK_CONTAINER(Contact.Window), Contact.Vbox);
	display_interface(Contact.Window);
	return (0);
}

/* Destruction du profile. */

void		wififriend_delete_profile(gchar *NetworkName)
{
	DWORD	Error = ERROR_SUCCESS;
	t_wifi	Delete;
	long	Size;
	BSTR	UnicodeStr;

	Delete = wififriend_create_handle();
	Delete = wififriend_retrieve_config(Delete);
	Size = lstrlenA(NetworkName);
	UnicodeStr = SysAllocStringLen(NULL, Size);
	MultiByteToWideChar(CP_ACP, 0, NetworkName, Size, UnicodeStr, Size);
	if ((Error = WlanDeleteProfile(Delete.MyHandle, &Delete.MyGuid, UnicodeStr, NULL))== ERROR_SUCCESS)
		error_delete_profil_success(0);
	WlanCloseHandle(Delete.MyHandle, NULL);
}

/* Supprime le contact du fichier contact.wf. */

int			wififriend_delete_from_file(gchar *Current)
{
	FILE	*File;
	FILE	*NewFile;
	long	Size;
	char	*Str;
	int		I;

	File = fopen("./Data/contact.wf", "r");
	NewFile = fopen("./Data/contact_0.wf", "w");
	fseek(File, 0, SEEK_END);
	Size = ftell(File);
	rewind(File);
	Str = (char *)malloc(sizeof(char *) * Size + 1);
	while(fgets(Str, Size, File))
	{
		if (strcmp(Current, Str) != 0)
			fputs(Str, NewFile);
	}
	fclose(File);
	fclose(NewFile);
	remove("./Data/contact.wf");
	rename("./Data/contact_0.wf", "./Data/contact.wf");
	free(Str);
	I = 0;
	while (Current[I])
	{
		if (Current[I] == '\n')
			Current[I] = 0;
		I++;
	}
	wififriend_delete_profile(Current);
	return (0);
}

/* Suppression du contact de la liste. */

void					wififriend_delete_contact(GtkWidget* Widget, gpointer Data)
{
	GtkTreeSelection	*Selection;
	GtkListStore		*Store;
	GtkTreeModel		*Model;
	GtkTreeIter			Iter;
	gchar				*Rom;

	Selection  = gtk_tree_view_get_selection(GTK_TREE_VIEW(ListOfView));
	Store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW (ListOfView)));
	Model = gtk_tree_view_get_model (GTK_TREE_VIEW (ListOfView));
	gtk_tree_model_get_iter_first(Model, &Iter);
	if ((gtk_tree_selection_get_selected(GTK_TREE_SELECTION(Selection), &Model, &Iter)))
	{
		gtk_tree_model_get(Model, &Iter, TEXT_COLUMN, &Rom, -1);
		wififriend_delete_from_file(Rom);
		gtk_list_store_remove(Store, &Iter);
	}
}

/* Connection sur le réseau séléctionné. */

static void						cb_row(GtkTreeView *p_treeview, GtkTreePath * p_path, GtkTreeViewColumn * p_column, gpointer p_data)
{
	GtkTreeModel				*p_model;
	GtkTreeIter					Iter;
	char						*WifiName;
	t_wifi						Connection;
	int							I;
	
	p_model = (GtkTreeModel *)p_data;
	if (gtk_tree_model_get_iter (p_model, &Iter, p_path))
		gtk_tree_model_get(p_model, &Iter, 0, &WifiName, -1);
    Connection = wififriend_create_handle();
	Connection = wififriend_retrieve_config(Connection);
	I = 0;
	while(WifiName[I])
	{
		if (WifiName[I] == '\n')
			WifiName[I] = 0;
		I++;
	}
	wififriend_connect_secure_network(Connection.MyHandle, &Connection.MyGuid, WifiName);
}

/* Création et gestion de la liste de contact. */

void			wififriend_display_contact(t_interface *Build)
{
	int			Size;
	char		*str;
	FILE		*ContactFile;
	t_contact	contact = {0};
	
	contact.ListOfContact = gtk_list_store_new(1, G_TYPE_STRING);
	str = (char *)malloc(sizeof(char *) * BUFSIZE);
	if ((ContactFile = fopen("./Data/contact.wf", "r")) == NULL)
		error_open_contact_file(1);
	fseek(ContactFile, 0, SEEK_END);
	Size = ftell(ContactFile);
	rewind(ContactFile);
	if (Size == 0)
		error_empty_contact_file(0);
	while(fgets(str, BUFSIZE, ContactFile))
	{
		gtk_list_store_append(contact.ListOfContact, &contact.Iter);
		gtk_list_store_set(contact.ListOfContact, &contact.Iter, TEXT_COLUMN, str, -1);
	}
	ListOfView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(contact.ListOfContact));
	contact.ContactName = gtk_cell_renderer_text_new();
	contact.Column = gtk_tree_view_column_new_with_attributes("\t\t\tMes wififriends", contact.ContactName, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(ListOfView), contact.Column); 
	contact.ScrollBar = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(contact.ScrollBar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(contact.ScrollBar), ListOfView);
	gtk_container_add(GTK_CONTAINER(Build->MyVbox), contact.ScrollBar);
	contact.SelectContact = gtk_tree_view_get_selection(GTK_TREE_VIEW(ListOfView));
	gtk_tree_selection_set_mode(contact.SelectContact, GTK_SELECTION_SINGLE);
	g_signal_connect(G_OBJECT(ListOfView), "row-activated", G_CALLBACK(cb_row), (gpointer)contact.ListOfContact);
	free(str);
	fclose(ContactFile);
}