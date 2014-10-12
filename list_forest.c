/*
 * list_forest.c
 *
 *  Created on: 6 oct. 2014
 *      Author: Valentin Jubert/ Melaine Gbahi
 */
#include <stdlib.h>
#include <strings.h>
#include "list_forest.h"

typedef struct list_forest_struct
{
    void * value;
    list_forest element;
    list_forest father;
    list_forest brother;
    list_forest son;
    void (*copy_value)();
    void (*free_value)();
    void (*copy_element) ();
    void (*free_element) ();
} * list_forest;

typedef struct list_forest_position_struct
{
    list_forest here;
} * list_forest_position ;

extern int list_forest_create ( list_forest * li,
                                void ( * copy_value ) ( const void * value , void ** pt ) ,
                                void ( * free_value ) ( void ** ),
                                void ( * copy_element ) ( const void * element , void ** pt ) ,
                                void ( * free_element ) ( void ** ) )
{
    (*li)->brother=NULL;
    (*li)->element=NULL;
    (*li)->father=NULL;
    (*li)->son=NULL;
    (*li)->value=NULL;
    (*li)->copy_value=copy_value;
    (*li)->free_value=free_value;
    (*li)->copy_element=copy_element;
    (*li)->free_element=free_element;
    return FOREST_LIST_OK;
}

extern int list_forest_position_create ( list_forest li, list_forest_position * pos)
{
    (*pos)->here=li;
    return FOREST_LIST_OK;
}
extern int list_forest_position_destroy ( list_forest_position * pos)
{
    free((*pos)->here);
    free(*pos);
    return FOREST_LIST_OK;
}

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
    if(pos->here->father==NULL)
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
    return (pos->here->son!=NULL)?TRUE:FALSE;
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
    return (pos->here->brother!=NULL)?TRUE:FALSE;
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
    if(pos==NULL || pos->here==NULL || pos->here->value==NULL)
    {
        return NULL;
    }
    puts("test5");
    printf("%d\n",pos->here->value);
    return pos->here->value;
}

extern int list_forest_is_empty ( list_forest li)
{
    if((li==NULL)||((li->value==NULL)&&(li->father==NULL)))
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
    list_forest lf;
    if(pos->here==NULL)
    {
        return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
    if(pos->here->father==NULL&&pos->here->value==NULL)
    {
        puts("test1");
        pos->here->copy_value(value,pos->here->value);
        puts("test3");
    }
    else
    {
        puts("test2");
        lf = malloc(sizeof(list_forest));
        pos->here->copy_value(value,pos->here->value);
        lf->father=pos->here->father;
        lf->element=NULL;
        lf->brother=NULL;
        lf->son=NULL;
        lf->copy_element=pos->here->copy_element;
        lf->copy_value=pos->here->copy_value;
        lf->free_element=pos->here->free_element;
        lf->free_value=pos->here->free_value;
        pos->here->brother = lf;
    }
    return FOREST_LIST_OK;
}
/*marche pas
extern int list_forest_add_left_son ( list_forest_position pos,
				      const void * value ) {
    if(pos->here==NULL){
        return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
    list_forest lf = malloc(sizeof(list_forest));
	lf->value = value;
	lf->father=pos->here->father;
	lf->element=NULL;
	lf->brother=NULL;
	lf->son=NULL;
    pos->here->son = lf;
	return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
}
/*marche pas
extern int list_forest_position_has_element ( list_forest_position pos) {
	if(pos->here == NULL) {
		return FALSE;
	} else {
	    if(pos->here->son==ELEMENT){
            return TRUE;
	    } else {
	        return FALSE;
	    }
	}
}*/

extern int list_forest_position_element_next ( list_forest_position pos)
{
    if(pos->here==NULL)
    {
        return FOREST_LIST_OK;
    }
    else
    {
        if(pos->here->brother!=NULL)
        {
            pos->here=pos->here->brother;
            return FOREST_LIST_OK;
        }
        else
        {
            pos->here=pos->here->father;
            return FOREST_LIST_OK;
        }
    }
}

void affichage_simple (list_forest_position pos)
{
    printf("%d\n",(*((int*)list_forest_position_value(pos))));
}
void copy(const void * value, void ** pt )
{
    puts("test10");
    * pt = NULL ;
    puts("test7");
    * pt = (void *) malloc ( sizeof ( int ) ) ;
    puts("test8");
    memcpy ( * pt , value , sizeof ( int ) );
    puts("test9");
}

static void free2 ( void ** pt ) {
  free ( * pt ) ;
  * pt = NULL ;
}
int main(void)
{
    list_forest li,li2;
    int val,val2, ercode;
    list_forest_position pos1,pos2;
    li=malloc(sizeof(list_forest));
    pos1=malloc(sizeof(list_forest_position));
    pos2=malloc(sizeof(list_forest_position));
    list_forest_create(&li, copy, free2, copy, free2);
    list_forest_position_create(li,&pos1);
    val=2;
    list_forest_add_next_brother(pos1, &val);
    puts("test4");
    affichage_simple(pos1);
    /*list_forest_add_next_brother(pos1, 3);
    affichage_simple(pos1);
    /*if(list_forest_is_empty(li)==TRUE){
        printf("ok");
    } else {
        puts("pas ok");
    }*/
    /*

    li->value=&val;
    affichage_simple(pos1);
    list_forest_position_duplicate(pos1,&pos2);
    affichage_simple(pos2);
    /*val=3;
    affichage_simple(pos);
    li2=malloc(sizeof(list_forest));
    list_forest_create(&li2, copy, free, copy, free);
    val2=3;
    li2->value=&val2;
    li->brother=li2;
    ercode=list_forest_position_next_brother(pos);
    if(ercode==FOREST_LIST_ERROR_FOREST_LIST_EMPTY){
        puts("erreur bro");
    }
    li2->father=li;
    affichage_simple(pos);
    list_forest_position_father(pos);
    affichage_simple(pos);*/

    return 0;
}


