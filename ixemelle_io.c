# ifndef __IXEMELLE_IO_H__
# define __IXEMELLE_IO_H__

# include "list_forest.h"

# include "ixemelle.h"

#include <stdlib.h>
#include <stdio.h>


extern int ixemelle_fscan ( FILE * fichier ,
			    list_forest * li ) {
	/*ouverture du fichier*/
	FILE * fopen(const char *list_forest,const char *ouverture )
/*pointeur sur le fichier initaialisé a NULL*/
		FILE* fichier =NULL;
	/*lecture du fichier*/
		input=fopen("list_forest","r");
		if(fichier!= NULL){
			return XMLIGHT_SYNTAX_OK 0;
			fclose(fichier);
		}else{
			XMLIGHT_SYNTAX_ERROR -1;
		}

}
