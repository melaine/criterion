# ifndef __FOREST_LIST_H__
# define __FOREST_LIST_H__

# include <stdio.h>

/** Each node contains:
    - a value
    - a list of elements

    Please notice:
    - "value" will always refer to the value of some node
    - "element" will always refer to an element of a list in a node.

    The forest structure works as follows. Each node indicates:
    - father (if any)
    - left(-most) son (if any)
    - next node (on the right) (if any)

    This is a forest. The root and its brothers are the roots of trees.
**/


/*  RETURN CODE value of functions  */

/** Everything went well.  **/
# define FOREST_LIST_OK 0

/*  ERROR RETURN CODE  */

/** Operation not allowed on an empty list_forest. **/
# define FOREST_LIST_ERROR_FOREST_LIST_EMPTY 1

/** Incoherent structure. **/
# define FOREST_LIST_ERROR_NOT_A_FOREST_LIST -1

/** System problem, usually an unsucess malloc.
    The structure might be corrupted and memory leaks should be expected.
**/
# define FOREST_LIST_ERROR_MEMORY -100


# ifndef TRUE
/* BOOLEAN VALUES */
# define TRUE (0==0)
# define FALSE (0!=0)
# endif


/** Type list_forest
    (hidden in the module body) **/
typedef struct list_forest_struct * list_forest ;


/** Creation of a generic list_forest
    - list_forest_pt: pointer on the  list_forest to initialize,
    - copy_value: used to copy a value (of unknown type and size,
      void * is used for that, allocate any memory needed),
    - free_value: used to destroy a value (do any needed de-allocation),
    - copy_element: used to copy an element of the list (...)
    - free_element: used to destroy an element of the list (...)
**/
extern int list_forest_create ( list_forest * ,
				void ( * copy_value ) ( const void * value , void ** pt ) ,
				void ( * free_value ) ( void ** ),
				void ( * copy_element ) ( const void * element , void ** pt ) ,
				void ( * free_element ) ( void ** ) ) ;

/** Destroy the list_forest and release all allocated resources.
    MUST be used not to avoid memory leaks.
    Uses free_value and free_element.
**/
extern int list_forest_destroy ( list_forest * ) ;

/** Tell whether the forest is empty. **/
extern int list_forest_is_empty ( list_forest ) ;

/** Empty the forest, i.e. remove every node. **/
extern int list_forest_empty ( list_forest ) ;


/** VISITING THE FOREST **/

/** Type used to record a position in a list_forest_parcours.
    It is locate on a node and at a given list element.
    It should be created and at the end destroyed. **/
typedef struct list_forest_position_struct * list_forest_position ;

/** Create a new position locate at the root of the forest.  **/
extern int list_forest_position_create ( list_forest ,
					 list_forest_position *  ) ;

/** Create a position by duplication. **/
extern int list_forest_position_duplicate ( list_forest_position ,
					    list_forest_position * ) ;

/** Destroy the list_forest_position and release all allocated resources.
    MUST be used not to avoid memory leaks.
**/
extern int list_forest_position_destroy ( list_forest_position * ) ;

/** Remove the left son node (and all its descendants).
**/
extern int list_forest_position_left_son_remove ( list_forest ,
						  list_forest_position ) ;

/** Remove the next brother node (and all its descendants).
 **/
extern int list_forest_position_next_brother_remove ( list_forest ,
						      list_forest_position ) ;

/** Tell whether the current node has a father.
    Only the root has no father. **/
extern int list_forest_position_has_father ( list_forest_position ) ;

/** Positionne sur le father.
    Positionne en début de liste du father. **/
extern int list_forest_position_father ( list_forest_position ) ;

/** Tell whether the node has a left node. **/
extern int list_forest_position_has_left_son ( list_forest_position ) ;

/** Move onto left son and first element on its list (if any). **/
extern int list_forest_position_left_son ( list_forest_position ) ;

/** Tell whether the node has a next brother. **/
extern int list_forest_position_has_next_brother ( list_forest_position ) ;

/** Move onto next brother and first element on its list (if any). **/
extern int list_forest_position_next_brother ( list_forest_position ) ;

/** Return the address of the value.
    Please note, it is the direct address, no copy is done
    (copy_value is not used). **/
extern void * list_forest_position_value ( list_forest_position ) ;


/* MODIFICATION of the FOREST */

/** Add a node as next brother.
    Uses copy_value **/
extern int list_forest_add_next_brother ( list_forest_position ,
					  const void * value ) ;

/** Add a node as left son.
    Uses copy_value **/
extern int list_forest_add_left_son ( list_forest_position ,
				      const void * value ) ;

/* MOVING inside the ELEMENT LIST */

/** Tell whether it is on an element.
    It is not the case when the list is empty or the list has been entirely visited. **/
extern int list_forest_position_has_element ( list_forest_position ) ;

/** Move onto the next element (or out of the list if it was the last element). **/
extern int list_forest_position_element_next ( list_forest_position ) ;

/** Return the current element.
    Please note, it is the direct address, no copy is done
    (copy_element is not used). **/
extern void * list_forest_position_element ( list_forest_position ) ;


/* MODIFYING the ELEMENT LIST */

/** Before current element (if any).
    Uses copy_element **/
extern int list_forest_add_element ( list_forest_position ,
				     const void * element ) ;

/** Printing.
    Comes handy when debugging. **/
extern void list_forest_fprint ( FILE * ,
				 list_forest ,
				 void ( * print_value ) ( FILE * , void * ) ,
				 void ( * print_element ) ( FILE * , void * ) );

# endif
