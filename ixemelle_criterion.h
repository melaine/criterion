# ifndef __IXEMELLE_CRITERION_H__
# define __IXEMELLE_CRITERION_H__

# include "ixemelle.h"

# include "list_forest.h"


/* ERROR CODE for FUNCTION RETURN */

# define XMLIGHT_CRITERION_OK 0
# define XMLIGHT_CRITERION_ERROR -1
# define XMLIGHT_CRITERION_ERROR_DUPLICATE_DEFINITION -2
# define XMLIGHT_CRITERION_ERROR_UNDEFINED_NODE -10


/* String used to denote the dirrefent relatives of a criterion. */

# define IXEMELLE_CRITERION_STRING_SELF "."
# define IXEMELLE_CRITERION_STRING_FATHER "<-"
# define IXEMELLE_CRITERION_STRING_ANCESTOR "<--"
# define IXEMELLE_CRITERION_STRING_SON "->"
# define IXEMELLE_CRITERION_STRING_DESCENDANT "-->"


# ifndef TRUE
/* BOOLEAN VALUES */
# define TRUE (0==0)
# define FALSE (0!=0)
# endif


/** Type for criterion
    (hidden in the module body) **/
typedef struct ixemelle_criterion_struct * ixemelle_criterion ;


/** To create an initialize a criterion.
    The criterion is defined by a string.
    A criterion is denoted by a conjuction of basic criterion:
    . tag[key="value"] for the node (self)
    <- tag[key="value"] for its father
    <-- tag[key="value"] for some ancestor
    -> tag[key="value"] for some son
    -> tag[key="value"] for some descendant
    . is optional if first condition
    tag can be empty to mean any tag
    [key="value"] is optional (i.e. no constrain on elements)
    There is at most one of each . <- <-- -> -->

    Examples:
    P [ V="33"]
    any node with tag P and attribute V defined with value "33"
    P
    any node with tag P
    [ V="33"]
    any node with the attribute V defined with value "33"
    P [ V="33" ] -> UL
    same but must have a son (direct) with tag LI
    P --> LI [ try="no" ]
    any with tag P that has a descendant with tag LI and attribute try="no"
    P --> [ try="no" ]
    any with tag P that has a descendant with attribute try="no"
    LI <- UL <-- P --> B
    any with tag LI whose father has tag UL and has an ancestor with tag P and a descendant with tag B
    <-- body --> I
    Any node that has an ascendant with name body and a descendant with name I
**/
extern int ixemelle_criterion_create ( ixemelle_criterion * , const char * ) ;

/** To terminate and release related ressources. **/
extern void ixemelle_criterion_destroy ( ixemelle_criterion * ) ;

/** Print a criterion.
    This is useful to follow a treatment as well as debugging.. **/
extern void ixemelle_criterion_fprint ( FILE * output ,
					ixemelle_criterion ) ;

/** tells whether the indicate node satisfy the given part of the criterion.
    Return FALSE if invalid part.
 */
extern int ixemelle_criterion_satisfy ( ixemelle_criterion ,
					list_forest_position pos ) ;

# endif
