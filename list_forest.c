/*
 * list_forest.c
 *
 *      Author: Valentin Jubert
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
/**Tableau regroupant les 4 fonctions sur les elements et les valeurs*/
void (*pt_fct[4]) ();

extern int list_forest_create ( list_forest * li,
                                void ( * copy_value ) ( const void * value , void ** pt ) ,
                                void ( * free_value ) ( void ** ),
                                void ( * copy_element ) ( const void * element , void ** pt ) ,
                                void ( * free_element ) ( void ** ) )
{
    *li=malloc(sizeof(struct list_forest_struct));
    (*li)->father=NULL;
    (*li)->brother=NULL;
    (*li)->son=NULL;
    (*li)->element=NULL;
    (*li)->value=NULL;
    pt_fct[CP_VALUE]=copy_value;
    pt_fct[FR_VALUE]=free_value;
    pt_fct[CP_ELEM]=copy_element;
    pt_fct[FR_ELEM]=free_element;
    return FOREST_LIST_OK;
}

extern int list_forest_position_create ( list_forest li, list_forest_position * pos)
{
    *pos=malloc(sizeof(list_forest_position));
    (*pos)->here=li;
    return FOREST_LIST_OK;
}
/**Supprime les elements*/
extern int list_forest_empty_elem(list_forest lf){
    if(NULL!=lf->brother){
        list_forest_empty_elem(lf->brother);
    }
    if(NULL!=lf->father){
        list_forest_empty_elem(lf->father);
    }
    pt_fct[FR_ELEM] (&lf->value);
    free(lf);
    lf=NULL;
    return FOREST_LIST_OK;
}
/**Supprime les valeurs, puis passe aux elements et récursivement à son fils et à son frère*/
extern int list_forest_empty ( list_forest lf) {
    if(!list_forest_is_empty(lf)){
        return FOREST_LIST_OK;
    } else {
        list_forest_empty(lf->brother);
        list_forest_empty(lf->son);
        (pt_fct[FR_VALUE]) (&lf->value);
        list_forest_empty_elem(lf->element);
        free(lf);
        lf=NULL;
        return FOREST_LIST_OK;
    }
}
extern int list_forest_destroy ( list_forest * plf) {
    list_forest_empty(*plf);
    *plf=NULL;
    return FOREST_LIST_OK;
}
extern int list_forest_position_left_son_remove ( list_forest lf,
						  list_forest_position pos ) {
    list_forest lf2;
    if(NULL==pos->here ||list_forest_is_empty(lf)){
        return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
    lf2=pos->here->son;
    if(NULL!=lf2){
        lf2->brother=NULL;
    }
    pos->here->son=pos->here->son->brother;
    list_forest_destroy(&lf2);
    return FOREST_LIST_OK;
						  }

extern int list_forest_position_next_brother_remove ( list_forest lf ,
						      list_forest_position pos ) {
    list_forest lf2;
    if(NULL==pos->here ||list_forest_is_empty(lf)){
        return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
    lf2=pos->here->brother;
    if(NULL!=lf2){
        lf2->brother=NULL;
    }
    pos->here->brother=pos->here->brother->brother;
    list_forest_destroy(&lf2);
    return FOREST_LIST_OK;
}

extern void list_forest_fprint ( FILE * f,
				 list_forest lf,
				 void ( * print_value ) ( FILE * , void * ) ,
				 void ( * print_element ) ( FILE * , void * ) ){
        /**Nombre de décalage espace nécessaire (pour faire apparaitre la parenté)*/
        static int nb_dec=0;
        int i;
        if(lf==NULL) {
            return ;
        }
        for (i=0;i<nb_dec;i++){
            fprintf(f," ");
        }
       (*print_value) (f,lf->value);
       fprintf(f," [ ");
       /**Print les elements*/
       if(NULL!=lf->element){
        while(NULL!=lf->element->brother){
                /*on va au dernier element*/
                lf->element=lf->element->brother;
            }
       }
       while(NULL!=lf->element){
            /*on print les elements en parcourant la list du dernier au premier (a cause de l'ajout en précédent*/
        (*print_element) (f,lf->element->value);
        fprintf(f," ");
        lf->element=lf->element->father;
       }
       fprintf(f,"] \n");
       /**Fin du print element*/
       nb_dec++;
       list_forest_fprint(f,lf->son,print_value,print_element);
       nb_dec--;
       list_forest_fprint(f,lf->brother,print_value,print_element);
}
extern int list_forest_position_destroy ( list_forest_position * pos){
    (*pos)->here=NULL;
    free(*pos);
    *pos=NULL;
    return FOREST_LIST_OK;
}
extern int list_forest_position_duplicate ( list_forest_position dup, list_forest_position * res){
    *res=malloc(sizeof(struct list_forest_position_struct));
    memcpy(*res,dup,sizeof(sizeof(list_forest_position)));
    return FOREST_LIST_OK;
}

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
    if(NULL==pos||pos->here==NULL){
            return FALSE;
    }
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
    return (NULL!=pos&&NULL!=pos->here&&NULL!=pos->here->brother)?TRUE:FALSE;
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
/**Si li est null ou si elle a un père et une valeur null*/
extern int list_forest_is_empty ( list_forest li)
{
    return (NULL==li||((NULL==li->father)&&(NULL==li->value)))?TRUE:FALSE;
}
extern int list_forest_add_next_brother ( list_forest_position pos ,
        const void * value )
{
    /*sauvegarde de position actuel*/
    void * save=NULL;
    if(list_forest_is_empty(pos->here)){
        /*Si premier ajout dans la list*/
        pos->here->father=NULL;
        pos->here->brother=NULL;
        pos->here->element=NULL;
        pos->here->son=NULL;
        pt_fct[CP_VALUE] (value,&pos->here->value);
        return FOREST_LIST_OK;
    } else {
       if(list_forest_position_has_next_brother(pos)){
           /*si ya déjà un frère,on va ajouter en dernier frère*/
           /*sauvegarde de la position actuel*/
            save=pos->here;
            while(list_forest_position_has_next_brother(pos)){
                /*on va au dernier frère*/
                list_forest_position_next_brother(pos);
            }
            list_forest_add_next_brother(pos,value);
            /**on remet à l'élement actuel*/
            list_forest_position_father(pos);
            /*on va sur le fils du père, donc un de ses frères*/
            list_forest_position_left_son(pos);
            while(save!=pos->here){
                    /*on revient à la position initiale*/
                list_forest_position_next_brother(pos);
            }
            return FOREST_LIST_OK;
       } else {
           /*si ya pas de frère*/
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
    if(list_forest_is_empty(pos->here)){
            /* si premier ajout dans la liste*/
        pos->here->father=NULL;
        pos->here->brother=NULL;
        pos->here->element=NULL;
        pos->here->son=NULL;
        pt_fct[CP_VALUE] (value,&pos->here->value);
        return FOREST_LIST_OK;
    } else {
        if(list_forest_position_has_left_son(pos)){
            /* si ya déjà un fils on va ajouter en tant que frère du fils*/
            list_forest_position_left_son(pos);
            list_forest_add_next_brother(pos,value);
            list_forest_position_father(pos);
            /*on est revenu à la position initial*/
            return FOREST_LIST_OK;
        } else {
            /* si ya pas de fils*/
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
	if(NULL==pos||list_forest_is_empty(pos->here)) {
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
        return (pos->here->element->value);
    } else {
        return (void *) FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
}
/**Teste si l'element actuel a un suivant */
extern int list_forest_position_has_element_next(list_forest_position pos){
    return (NULL!=pos->here->element->father?TRUE:FALSE);
}
/**Teste si l'element actuel a un precedent*/
extern int list_forest_position_has_element_prev(list_forest_position pos){
    return (NULL!=pos->here->element->brother?TRUE:FALSE);
}
/**Ajoute un element avant l'actuel*/
extern int list_forest_add_element ( list_forest_position pos ,
				     const void * element )
{
    list_forest lf;
    if(NULL==pos||list_forest_is_empty(pos->here)){
        return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
    }
    if(NULL==pos->here->element){
            /* si ya pas d'element*/
        pos->here->element=malloc(sizeof(struct list_forest_struct));
        pos->here->element->father=NULL;
        pos->here->element->brother=NULL;
        pos->here->element->son=NULL;
        pos->here->element->element=NULL;
        (pt_fct[CP_ELEM]) (element,&(pos->here->element->value));
        return FOREST_LIST_OK;
    } else {
        if(NULL==pos->here->element->father){
            /*si ya pas de precedent*/
            lf = malloc(sizeof(struct list_forest_struct));
            /*on ajoute en suivant l'element actuel*/
            lf->brother=pos->here->element;
            lf->father=NULL;
            lf->son=NULL;
            (pt_fct[CP_ELEM]) (element,&(lf->value));
            /*on ajoute en précédent de l'actuel*/
            pos->here->element->father=lf;
            return FOREST_LIST_OK;
        } else {
            /*si ya déjà un précédent*/
            lf = malloc (sizeof(struct list_forest_struct));
            /*en suivant on met l'actuel*/
            lf->brother=pos->here->element;
            /*en precedent on met le precedent de l'actuel*/
            lf->father=pos->here->element->father;
            lf->son=NULL;
            (pt_fct[CP_ELEM]) (element,&(lf->value));
            /*le suivant du precedent de l'actuel devient celui qu'on ajoute*/
            pos->here->element->father->brother=lf;
            /*le precedent de l'actuel devient celui qu'on ajoute*/
            pos->here->element->father=lf;
            return FOREST_LIST_OK;
        }
    }
}
/**Va a l'element suivant*/
extern int list_forest_position_element_next ( list_forest_position pos)
{
   if(list_forest_position_has_element_next(pos)){
        pos->here->element=pos->here->element->father;
        return FOREST_LIST_OK;
   } else {
       return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
   }
}
/**Va a l'element precedent*/
extern int list_forest_position_element_prev ( list_forest_position pos)
{
   if(list_forest_position_has_element_prev(pos)){
        pos->here->element=pos->here->element->brother;
        return FOREST_LIST_OK;
   } else {
       return FOREST_LIST_ERROR_FOREST_LIST_EMPTY;
   }
}
