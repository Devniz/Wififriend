/******************************
*	- Author: Nizar Bousebsi. *      
*	- File: wififriend.cpp    *
*   - Description: Main file. *
*******************************/

#include "wififriend.h"

/* Entrée principale du programme. */

int							main(int argc, char **argv)
{
	LPSECURITY_ATTRIBUTES	s = NULL;
	FILE					*ContactFile;

	FreeConsole();
	CreateDirectory("./Data", s);
	ContactFile = fopen("./Data/contact.wf", "a");
	fclose(ContactFile);
	set_interface(argc, argv);
	return (0);
}