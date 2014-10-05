# ifndef __IXEMELLE_H__
# define __IXEMELLE_H__


# include "list_forest.h"


# define NAME_MAX_LENGTH 15
# define KEY_MAX_LENGTH 10
# define VALUE_MAX_LENGTH 50


/* ERROR CODE for FUNCTION RETURN */
/** There is a problem with an argument. **/
# define IXEMELLE_WRONG_ARGUMENT -100


/** Structure to record an attribut.
    It is used for the XMLight encoding as well as the criterion encoding.
    It is not hidden because it is used in more than one module. **/
typedef struct attribute_struct {
  char key [ KEY_MAX_LENGTH + 1 ] ;
  char value [ VALUE_MAX_LENGTH + 1 ] ;
} attribute_struct ,
  * attribute ;

/** Used to initialize a list forest customized for xmlight data. */
extern void ixemelle_create ( list_forest * al_py ) ;


# endif
