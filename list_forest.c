/*
 * list_forest.c
 *
 *  Created on: 6 oct. 2014
 *      Author: Valentin Jubert/ Melaine Gbahi
 */

#include "list_forest.h"

typedef struct list_forest_struct {
	void * value;
	list_forest* element;
	list_forest* father;
	list_forest* brother;
	list_forest* son;
} list_forest;

typedef struct list_forest_position_struct {

} list_forest_position ;

extern int list_forest_is_empty ( list_forest li) {
	if(li.son==NULL)
		return TRUE;
	else
		return FALSE;
}
