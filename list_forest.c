/*
 * list_forest.c
 *
 *  Created on: 6 oct. 2014
 *      Author: Valentin Jubert/ Melaine Gbahi
 */
#include <stdlib.h>
#include <strings.h>
#include "list_forest.h"

typedef struct list_forest_struct {
	void * value;
	list_forest element;
	list_forest father;
	list_forest brother;
	list_forest son;
} * list_forest;

typedef struct list_forest_position_struct{
	list_forest here;
} * list_forest_position ;

extern int list_forest_position_create ( list_forest li, list_forest_position * pos) {
	pos=malloc(sizeof(list_forest_position));
	(*pos)->here=malloc(sizeof(list_forest));
	(*pos)->here=li;
	return FOREST_LIST_OK;
}
extern int list_forest_position_destroy ( list_forest_position * pos){
	free((*pos)->here);
	free(*pos);
	return FOREST_LIST_OK;

}

extern int list_forest_position_duplicate ( list_forest_position dup, list_forest_position * res) {
    memcpy(dup,(*res),sizeof(list_forest_position));
    return FOREST_LIST_OK;
}
//todo
extern int list_forest_position_left_son_remove ( list_forest li,
						  list_forest_position pos) ;
//todo
extern int list_forest_position_next_brother_remove ( list_forest li,
						      list_forest_position pos) ;

extern int list_forest_position_has_father ( list_forest_position pos) {
    if(pos->here->father==NULL){
        return FALSE;
    } else {
        return TRUE;
    }
}
extern int list_forest_position_father ( list_forest_position pos) {
    pos->here=pos->here->father;
    return FOREST_LIST_OK;
}

/** Tell whether the node has a left node. **/
extern int list_forest_position_has_left_son ( list_forest_position ) ;

/** Move onto left son and first element on its list (if any). **/
extern int list_forest_position_left_son ( list_forest_position ) ;

/** Tell whether the node has a next brother. **/
extern int list_forest_position_has_next_brother ( list_forest_position ) ;

/** Move onto next brother and first element on its list (if any). **/
extern int list_forest_position_next_brother ( list_forest_position ) ;

extern void * list_forest_position_value ( list_forest_position pos) {
    return &(pos->here->value);
}



int main(void){
}
