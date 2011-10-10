/***********************************************************
*	- Author: Nizar Bousebsi.						       *      
*	- File: network.cpp									   *
*   - Description: Manage Microsoft Native Wifi Functions. *
************************************************************/

#include "wififriend.h"

/* Extracteur de profile. */

void			wififriend_extract_next(GtkWidget* Widget, gpointer Data)
{
	DWORD		Error = ERROR_SUCCESS;
	GtkWidget	*Profil;
	t_wifi		Extract;
	const gchar	*Retrieve;
	long		Size;
	BSTR		UnicodeStr;
	LPWSTR		OutProfil;
	char		*NewProfil;
	FILE		*File;
	int			I = 0;
	char		*PathFile;

	Profil = (GtkWidget *)Data;
	Retrieve = gtk_entry_get_text(GTK_ENTRY(Profil));
	Extract = wififriend_create_handle();
	Extract = wififriend_retrieve_config(Extract);
	Size = lstrlenA(Retrieve);
	UnicodeStr = SysAllocStringLen(NULL, Size);
	MultiByteToWideChar(CP_ACP, 0, Retrieve, Size, UnicodeStr, Size);
	if((Error = WlanGetProfile(Extract.MyHandle, &Extract.MyGuid, UnicodeStr, NULL, &OutProfil, 0, 0)) != ERROR_SUCCESS)
		error_get_profil(0, Retrieve);
	else
	{
		while (OutProfil[I])
			I++;
		NewProfil = (char *)malloc(sizeof(char) * I + 1);
		wcstombs(NewProfil, OutProfil, I + 1);
		PathFile = (char *)malloc(sizeof(char *) * strlen(Retrieve) + 1);
		strcpy(PathFile, Retrieve);
		strcat(PathFile, ".xml");
		File = fopen(PathFile, "w+");
		fputs(NewProfil, File);
		fclose(File);
		free(PathFile);
		error_get_profil_success(0, Retrieve);
	}
	SysFreeString(UnicodeStr);
	WlanCloseHandle(Extract.MyHandle, NULL);
}

void			wififriend_extract_profil(void)
{
	GtkWidget	*Win = NULL;
	GtkWidget	*Vbox = NULL;
	GtkWidget	*ProfilLabel = NULL;
	GtkWidget	*ProfilEntry = NULL;
	GtkWidget	*Button = NULL;

	Win = create_window(260, 100, "Extraire votre profile Wifi");
	Vbox = gtk_vbox_new(FALSE, 0);
	ProfilLabel = gtk_label_new("Nom de votre reseau Wifi");
	gtk_box_pack_start(GTK_BOX(Vbox), ProfilLabel, FALSE, FALSE, 5);
	ProfilEntry = gtk_entry_new();
	gtk_entry_set_max_length(GTK_ENTRY(ProfilEntry), 15);
	gtk_box_pack_start(GTK_BOX(Vbox), ProfilEntry, FALSE, FALSE, 15);
	Button = gtk_button_new_with_label("Extraire");
	gtk_container_add(GTK_CONTAINER(Vbox), Button);
	g_signal_connect(G_OBJECT(Button), "clicked", G_CALLBACK(wififriend_extract_next), (gpointer)ProfilEntry);
	gtk_container_add(GTK_CONTAINER(Win), Vbox);
	display_interface(Win);
}

/* Forcer la déconnexion d'un réseau Wifi. */

void		wififriend_disconnect_user(GtkWidget* Widget, gpointer Data)
{
	t_wifi	Disconnect;

	Disconnect = wififriend_create_handle();
	Disconnect = wififriend_retrieve_config(Disconnect);
	if ((WlanDisconnect(Disconnect.MyHandle, &Disconnect.MyGuid, NULL)!= ERROR_SUCCESS))
		error_cannot_disconnect(0);
	else
		error_disconnect_success(0);
	WlanCloseHandle(Disconnect.MyHandle, NULL);
}

/* Récupération d'un handle pour les prochaines opérations. */

t_wifi		wififriend_create_handle(void)
{
	t_wifi	Connect;
	DWORD	SetHandle = ERROR_SUCCESS;
	HANDLE	Handle = NULL;
	DWORD	Version = 0;

	if ((SetHandle = WlanOpenHandle(WLAN_API_VERSION, NULL, &Version, &Handle)) != ERROR_SUCCESS)
		error_invalid_handle(1);
	else
		Connect.MyHandle = Handle;
	return (Connect);
}

/* Retourne la configuration de l'interface Wifi. */

t_wifi							wififriend_retrieve_config(t_wifi Connect)
{
	PWLAN_INTERFACE_INFO_LIST	InterfaceList;

	InterfaceList = NULL;
	if(WlanEnumInterfaces(Connect.MyHandle, NULL, &InterfaceList) != ERROR_SUCCESS)
		error_config(1);
	else
	{
		Connect.NumberOfItems = InterfaceList->dwNumberOfItems;
		Connect.MyGuid = InterfaceList->InterfaceInfo->InterfaceGuid;
		Connect.CurrentState = InterfaceList->InterfaceInfo->isState;
	}
	return (Connect);
}

/* Affichage des paramètres de l'interface Wifi. */

void								wififriend_display_wifi_params(GtkWidget* Widget, gpointer Data)
{
	int								I = 0;
	PWLAN_INTERFACE_INFO_LIST		InterfaceList = NULL;
	t_wifi							St;
	GtkWidget						*Win = NULL;
	GtkWidget						*Vbox;
	GtkWidget						*NbInterface = NULL;
	GtkWidget						*NbInterfaceResult = NULL;
	GtkWidget						*Guid = NULL;
	GtkWidget						*GuidResult = NULL;
	GtkWidget						*State = NULL;
	GtkWidget						*StateResult = NULL;
	GtkWidget						*Description = NULL;
	GtkWidget						*DescriptionResult = NULL;
	gchar							*String = NULL;

	St = wififriend_create_handle();
	St = wififriend_retrieve_config(St);
	Win = create_window(300, 180, "Configuration Wifi");
	Vbox = gtk_vbox_new(FALSE, 0);
	if ((WlanEnumInterfaces(St.MyHandle, NULL, &InterfaceList)) != ERROR_SUCCESS)
		error_interface_wifi(0);
	else
	{
		NbInterface = gtk_label_new("- Nombre d'interface Wifi trouvee: ");
		gtk_box_pack_start(GTK_BOX(Vbox), NbInterface, FALSE, FALSE, 0);
		String = g_strdup_printf ("%d", InterfaceList->dwNumberOfItems);
		NbInterfaceResult = gtk_label_new(String);
		gtk_box_pack_start(GTK_BOX(Vbox), NbInterfaceResult, FALSE, FALSE, 2);
		Guid = gtk_label_new("- GUID de votre interface Wifi: ");
		gtk_box_pack_start(GTK_BOX(Vbox), Guid, FALSE, FALSE, 5);
		String = g_strdup_printf ("%d", InterfaceList->InterfaceInfo->InterfaceGuid);
		GuidResult = gtk_label_new(String);
		gtk_box_pack_start(GTK_BOX(Vbox), GuidResult, FALSE, FALSE, 2);
		State = gtk_label_new("- Etat de l'interface: ");
		gtk_box_pack_start(GTK_BOX(Vbox), State, FALSE, FALSE, 5);
		String = g_strdup_printf ("%d", InterfaceList->InterfaceInfo->isState);
		StateResult = gtk_label_new(String);
		gtk_box_pack_start(GTK_BOX(Vbox), StateResult, FALSE, FALSE, 2);
		gtk_container_add(GTK_CONTAINER(Win), Vbox);
		display_interface(Win);
		WlanCloseHandle(St.MyHandle, NULL);
	}
}

/* Connexion à un réseau sécurisé. */

int								wififriend_connect_secure_network(HANDLE Handle, const GUID *Id, char *Strxml)
{
	DWORD						Error = ERROR_SUCCESS;
	WLAN_CONNECTION_PARAMETERS	Connect;
	int							Size;
	BSTR						UnicodeStr;

	memset(&Connect, 0, sizeof(WLAN_CONNECTION_PARAMETERS));
	Connect.wlanConnectionMode = wlan_connection_mode_profile;
	Size = lstrlenA(Strxml);
	UnicodeStr = SysAllocStringLen(NULL, Size);
	MultiByteToWideChar(CP_ACP, 0, Strxml, Size, UnicodeStr, Size);
	Connect.strProfile = UnicodeStr;
	Connect.pDot11Ssid = NULL;
	Connect.pDesiredBssidList = NULL;
	Connect.dot11BssType = dot11_BSS_type_any;
	Connect.dwFlags = 0;
	if ((Error = WlanConnect(Handle, Id, &Connect, NULL)) != ERROR_SUCCESS)
		switch(Error)
		{
			case ERROR_INVALID_HANDLE:
			error_invalid_handle(0);
			break;
			case ERROR_ACCESS_DENIED:
			error_unauthorized_connect(0);
			break;
			case ERROR_INVALID_PARAMETER:
			error_parameters_connect(0);
			break;
			default: 
				error_connect_unknow(0);
		}
	else
		error_connect_success(0, (char *)UnicodeStr);
	WlanCloseHandle(Handle, NULL);
	return (0);
}

/* Connexion à un réseau non sécurisé. */

void							wififriend_connect_to_unsecure_network(GtkWidget* Widget, gpointer Data)
{
	t_wifi						Unsecure;
	DWORD						Error = ERROR_SUCCESS;
	WLAN_CONNECTION_PARAMETERS	Connect;

	Unsecure = wififriend_create_handle();
	Unsecure = wififriend_retrieve_config(Unsecure);
	memset(&Connect, 0, sizeof(WLAN_CONNECTION_PARAMETERS));
	Connect.wlanConnectionMode = wlan_connection_mode_discovery_unsecure;
	Connect.strProfile = NULL;
	Connect.pDot11Ssid = NULL;
	Connect.pDesiredBssidList = 0;
	Connect.dot11BssType = dot11_BSS_type_infrastructure;
	Connect.dwFlags = WLAN_CONNECTION_IGNORE_PRIVACY_BIT;
	if((Error = WlanConnect(Unsecure.MyHandle, &Unsecure.MyGuid, &Connect, NULL)) != ERROR_SUCCESS)
		error_unauthorized_connect(0);
	WlanCloseHandle(Unsecure.MyHandle, NULL);
}

/* Scanner de réseau Wifi. */

void								wififriend_scan_network(GtkWidget* Widget, gpointer Data)
{
	DWORD							Error = ERROR_SUCCESS;
	PWLAN_AVAILABLE_NETWORK_LIST	Network = NULL;
	t_wifi							St;
	int								I;
	GtkWidget						*WinScan = NULL;
	GtkWidget						*ListOfWifi = NULL;

	I = 1;
	St = wififriend_create_handle();
	St = wififriend_retrieve_config(St);
	if((WlanGetAvailableNetworkList(St.MyHandle, &St.MyGuid, 0x00000001, NULL, &Network)) != ERROR_SUCCESS)
		error_scan(0);
	else
	{
		WinScan = create_window(236, 27, "Wifi scan");
		ListOfWifi = gtk_combo_box_new_text();
		while(I != Network->dwNumberOfItems)
		{
			gtk_combo_box_prepend_text(GTK_COMBO_BOX(ListOfWifi), (const gchar *)Network->Network[I].dot11Ssid.ucSSID);
			I++;
		}
		gtk_combo_box_set_active(GTK_COMBO_BOX(ListOfWifi), 0);
		gtk_container_add(GTK_CONTAINER(WinScan), ListOfWifi);
		g_signal_connect(G_OBJECT(ListOfWifi), "changed", G_CALLBACK(wififriend_connect_to_unsecure_network), (gpointer)ListOfWifi);
		display_interface(WinScan);
		WlanCloseHandle(St.MyHandle, NULL);
	}
}