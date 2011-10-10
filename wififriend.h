/*******************************
*	- Author: Nizar Bousebsi.  *      
*	- File: wififriend.h       *
*   - Description: header file.*
*******************************/

#ifndef _WIFIFRIEND_H_
# define _WIFIFRIEND_H_

#include <windows.h>
#include <wlanapi.h>
#include <gtk/gtk.h>

#define BUFSIZE	1024

enum
{
	TEXT_COLUMN,
	TOGGLE_COLUMN,
	N_COLUMN
};

typedef struct	s_interface
{
	GtkWidget	*MyWindow;
	GtkWidget	*MyVbox;
	GtkWidget	*MyMenuBar;
	GtkWidget	*MyMenu;
	GtkWidget	*MyMenuItem;
}				t_interface;

typedef struct	s_tools
{
	GtkWidget   *ToolBar;
    GtkToolItem *Connect;
    GtkToolItem *Disconnect;
    GtkToolItem *Add;
    GtkToolItem *Del;
    GtkToolItem *Scan;
    GtkToolItem *Parameters;
    GtkToolItem *Quit;
}				t_tools;

typedef struct				s_wifi
{
	HANDLE					MyHandle;
	DWORD					NumberOfItems;
	WCHAR					InterfaceDescription[256];
	WLAN_INTERFACE_STATE	CurrentState;
	GUID					MyGuid;
	PWSTR					Profil;
	LPCWSTR					Network;
}							t_wifi;

typedef struct			s_contact
{
	int					i;
	FILE				*ContactStream;
	GtkListStore		*ListOfContact;
	GtkTreeIter			Iter;
	GtkWidget			*ListOfView;
	GtkCellRenderer		*ContactName;
	GtkTreeViewColumn	*Column;
	GtkTreeSelection	*SelectContact;
	GtkWidget			*ScrollBar;
	char				*Str;
}						t_contact;

typedef struct	s_newcontact
{
	GtkWidget	*Window;
	GtkWidget	*Vbox;
	GtkWidget	*nc;
	GtkWidget	*EntryNc;
	GtkWidget	*Profile;
	GtkWidget	*Button;
	GtkWidget	*Confirm;
	char		*FileName;
}				t_newcontact;

/* INTERFACE */

int			set_interface(int argc, char **argv);
GtkWidget   *create_window(gint Width, gint Height, const gchar *Title);
t_interface	create_vbox(GtkWidget *Window);
t_interface	*create_menu_one(t_interface *Info);
void		create_menu_two(t_interface *Build);
void		create_menu_three(t_interface *Build);
void		create_menu_for(t_interface *Build);
void		create_menu_five(t_interface *Build);
void		create_toolbar(t_interface *Build);
void		display_interface(GtkWidget *Window);
void		about(GtkWidget* Widget, gpointer Data);
void		quit(GtkWidget* Widget, gpointer Data);

/* WIRELESS */

t_wifi		wififriend_create_handle(void);
t_wifi		wififriend_retrieve_config(t_wifi Connect);
void		wififriend_scan_network(GtkWidget* Widget, gpointer Data);
void		wififriend_display_wifi_params(GtkWidget* Widget, gpointer Data);
int			wififriend_connect_secure_network(HANDLE Handle, const GUID *Id, char *Strxml);
void		wififriend_connect_to_unsecure_network(GtkWidget* Widget, gpointer Data);
void		wififriend_disconnect_user(GtkWidget* Widget, gpointer Data);
void		wififriend_extract_profil(void);

/* CONTACT LIST */

void		wififriend_display_contact(t_interface *Build);
void		wififriend_delete_contact(GtkWidget* Widget, gpointer Data);
int			wififriend_add_new_contact(void);
void		wififriend_load_profile(GtkWidget* Widget, gpointer Data);
static void	cb_row(GtkTreeView *p_treeview, GtkTreePath * p_path, GtkTreeViewColumn * p_column, gpointer p_data);
int			wififriend_delete_from_file(gchar *Current);
void		wififriend_delete_profile(gchar *NetworkName);
void		wififriend_double_contact(GtkWidget* Widget, gpointer Data);
void		wififriend_extract_next(GtkWidget* Widget, gpointer Data);
void		wififriend_display_new_contact(GtkWidget* Widget, gpointer Data);

/* ERROR */

void	error_config(int Flags);
void	error_scan(int Flags);
void	error_connect(int Flags);
void	error_open_profile(int Flags);
void	error_invalid_handle(int Flags);
void	error_unauthorized_connect(int Flags);
void	error_parameters_connect(int Flags);
void	error_connect_unknow(int Flags);
void	error_connect_success(int Flags, char *NetworkName);
void	error_cannot_disconnect(int Flags);
void	error_open_contact_file(int Flags);
void	error_empty_contact_file(int Flags);
void	error_set_profile_failed(int Flags);
void	error_set_profile_success(int Flags);
void	error_give_contact(int Flags);
void	error_interface_wifi(int Flags);
void	error_get_profil(int Flags);
void	error_delete_profil_success(int Flags);
void	error_double_contact(int Flags);
void	error_get_profil(int Flags, const gchar *ProfilName);
void	error_get_profil_success(int Flags, const gchar *ProfilName);
void	error_disconnect_success(int Flags);
void	error_double_contact(int Flags);

/* HELP */

void	display_help(GtkWidget* Widget, gpointer Data);

#endif