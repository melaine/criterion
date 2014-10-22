/*
 * list_forest.c
 *
 *  Created on: 6 oct. 2014
 *      Author: Valentin Jubert/ Melaine Gbahi
 */
#include <stdlib.h>
#include <string.h>
#include "list_forest.h"

#define CP_VALUE 0
#define FR_VALUE 1
#define CP_ELEM 2
#define FR_ELEM 3

struct list_forest_struct
{
    void * value;
    list_forest element;
    list_forest father;
    list_forest brother;
    list_forest son;
} ;

struct list_forest_position_struct
{
    list_forest here;
} ;

void (*pt_fct[4]) ();

extern int list_forest_create ( list_forest * li,
                                void ( * copy_value ) ( const void * value , void ** pt ) ,
                                void ( * free_value ) ( void ** ),
                                void ( * copy_element ) ( const void * element , void ** pt ) ,
                                void ( * free_element ) ( void ** ) )
{
    *li=NULL;
    pt_fct[CP_VALUE]=copy_value;
    pt_fct[FR_VALUE]=free_value;
    pt_fct[CP_ELEM]=copy_element;
    pt_fct[FR_ELEM]=free_element;
    return FOREST_LIST_OK;
}

extern int list_forest_position_create ( list_forest li, list_forest_position * pos)
{
    *pos=NULL;
    *pos=malloc(sizeof(list_forest_position));
    (*pos)->here=li;
    return FOREST_LIST_OK;
}
/*incomplet*/
extern int list_forest_position_destroy ( list_forest_position * pos)
{
    free(*pos);
    pos=NULL;
    return FOREST_LIST_OK;
}
/*pas bon*/
extern int list_forest_position_duplicate ( list_forest_position dup, list_forest_position * res)
{
    (*res)->here=dup->here;
    return FOREST_LIST_OK;
}
/*todo*/
extern int list_forest_position_left_son_remove ( list_forest li,
        list_forest_position pos) ;
/*todo*/
extern int list_forest_position_next_brother_remove ( list_forest li,
        list_forest_position pos) ;

extern int list_forest_position_has_father ( list_forest_position pos)
{
    if(NULL==pos||NULL==pos->here->father)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
extern int list_forest_position_father ( list_forest_position pos)
{
    if(list_forest_position_has_father(pos))
    {
        pos->here=pos->here->father;
        return FOREST_LIST_OK;
    }
    else
    {
        return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
}

extern int list_forest_position_has_left_son ( list_forest_position pos)
{
    return (NULL!=pos->here->son)?TRUE:FALSE;
}

extern int list_forest_position_left_son ( list_forest_position pos)
{
    if(list_forest_position_has_left_son(pos))
    {
        pos->here=pos->here->son;
        return FOREST_LIST_OK;
    }
    else
    {
        return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
}

extern int list_forest_position_has_next_brother ( list_forest_position pos)
{
    return (NULL!=pos->here->brother)?TRUE:FALSE;
}

extern int list_forest_position_next_brother ( list_forest_position pos)
{
    if(list_forest_position_has_next_brother(pos))
    {
        pos->here=pos->here->brother;
        return FOREST_LIST_OK;
    }
    else
    {
        return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
}

extern void * list_forest_position_value ( list_forest_position pos)
{
    if(NULL==pos||NULL==pos->here||NULL==pos->here->value)
    {
        return NULL;
    }
    return pos->here->value;
}

extern int list_forest_is_empty ( list_forest li)
{
    if((NULL==li)||((NULL==li->value)&&(NULL==li->father)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
extern int list_forest_add_next_brother ( list_forest_position pos ,
        const void * value )
{
    void * save=NULL;
    if(NULL==pos->here){
        pos->here=malloc(sizeof(struct list_forest_struct));
        pos->here->father=NULL;
        pos->here->brother=NULL;
        pos->here->element=NULL;
        pos->here->son=NULL;
        pt_fct[CP_VALUE] (value,&pos->here->value);
        return FOREST_LIST_OK;
    } else {
       if(list_forest_position_has_next_brother(pos)){
            save=pos->here;
            while(list_forest_position_has_next_brother(pos)){
                list_forest_position_next_brother(pos);
            }
            list_forest_add_next_brother(pos,value);
            /**on remet � l'�lement actuel*/
            list_forest_position_father(pos);
            list_forest_position_left_son(pos);
            while(save!=pos->here){
                list_forest_position_next_brother(pos);
            }
            return FOREST_LIST_OK;
       } else {
            pos->here->brother=malloc(sizeof(struct list_forest_struct));
            (pt_fct[CP_VALUE]) (value,&pos->here->brother->value);
            pos->here->brother->father=pos->here->father;
            pos->here->brother->element=NULL;
            pos->here->brother->brother=NULL;
            pos->here->brother->son=NULL;
            return FOREST_LIST_OK;
        }
    }
}
extern int list_forest_add_left_son ( list_forest_position pos,
				      const void * value ) {
    if(NULL==pos->here){
        pos->here=malloc(sizeof(struct list_forest_struct));
        pos->here->father=NULL;
        pos->here->brother=NULL;
        pos->here->element=NULL;
        pos->here->son=NULL;
        pt_fct[CP_VALUE] (value,&pos->here->value);
        return FOREST_LIST_OK;
    } else {
        if(list_forest_position_has_left_son(pos)){
            list_forest_position_left_son(pos);
            list_forest_add_next_brother(pos,value);
            list_forest_position_father(pos);
            return FOREST_LIST_OK;
        } else {
            pos->here->son=malloc(sizeof(struct list_forest_struct));
            (pt_fct[CP_VALUE]) (value,&pos->here->son->value);
            pos->here->son->father=pos->here;
            pos->here->son->element=NULL;
            pos->here->son->brother=NULL;
            pos->here->son->son=NULL;
            return FOREST_LIST_OK;
        }
    }
}
extern int list_forest_position_has_element ( list_forest_position pos) {
	if(NULL==pos->here) {
		return FALSE;
	} else {
	    if(NULL==pos->here->element){
            return FALSE;
	    } else {
	        return TRUE;
	    }
	}
}
extern void * list_forest_position_element ( list_forest_position pos) {
    if(list_forest_position_has_element(pos)){
        return (void *) (pos->here->element->value);
    } else {
        return (void *) FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
}
/*a test�*/
extern int list_forest_add_element ( list_forest_position pos ,
				     const void * element )
{
    if(NULL==pos->here){
        return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
    if(NULL==pos->here->element){
        pos->here->element=malloc(sizeof(struct list_forest_struct));
        pos->here->element->father=NULL;
        pos->here->element->brother=NULL;
        pos->here->element->son=NULL;
        pos->here->element->element=NULL;
        (pt_fct[CP_ELEM]) (element,&(pos->here->element->value));
        return FOREST_LIST_OK;
    } else {
        if(NULL==pos->here->element->brother){
            pos->here->element->brother=malloc(sizeof(struct list_forest_struct));
            pos->here->element->brother->father=pos->here->element;
            pos->here->element->brother->brother=NULL;
            pos->here->element->brother->son=NULL;
            pos->here->element->brother->element=NULL;
            (pt_fct[CP_ELEM]) (element,&(pos->here->element->brother->value));
            return FOREST_LIST_OK;
        } else {/**a faire*//*
            lf=malloc(sizeof(list_forest));
            lf->father=pos->here->element->father;
            lf->brother=pos->here->element;
            pos->here->element->father->brother=lf;
            pos->here->element->brother=lf;
            pos->here->element=lf;
            lf->son=NULL;
            lf->element=NULL;
            (pt_fct[CP_ELEM]) (element,&(lf->value));
            return FOREST_LIST_OK;*/
        }
    }
}
extern int list_forest_position_element_next ( list_forest_position pos)
{
   if(list_forest_position_has_element(pos)){
        pos->here->element=pos->here->element->brother;
        return FOREST_LIST_OK;
   } else {
       return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
   }
}
void affichage_simple (list_forest_position pos)
{
    printf("%d\n",(*((int*)list_forest_position_value(pos))));
}
void copy2(const void * value, void ** pt )
{
    * pt = NULL ;
    * pt = (void *) malloc ( sizeof ( int ) ) ;
    memcpy ( * pt , value , sizeof ( int ) );
}

static void free2 ( void ** pt ) {
  free ( * pt ) ;
  * pt = NULL ;
}
int main(void)
{
    list_forest lf = NULL;
    list_forest_position pos = NULL;
    int b = 3 ;
    list_forest_create ( & lf ,
		       & copy2 ,
		       & free2 ,
		       & copy2 ,
		       & free2 ) ;
    list_forest_position_create ( lf , & pos ) ;
    list_forest_add_left_son ( pos , (void *) & b ) ;
    affichage_simple(pos);
    b=4;
    list_forest_add_left_son ( pos , (void *) & b ) ;
    b=5;
    list_forest_add_left_son ( pos , (void *) & b ) ;
    list_forest_position_left_son(pos);
    list_forest_position_next_brother(pos);
    list_forest_position_father(pos);
    affichage_simple(pos);
    return 0;
}
