# ifndef __IXEMELLE_IO_H__
# define __IXEMELLE_IO_H__

# include "list_forest.h"

# include "ixemelle.h"


/* ERROR CODE for FUNCTION RETURN */

# define XMLIGHT_SYNTAX_OK 0
# define XMLIGHT_SYNTAX_ERROR -1


# define XMLIGHT_SYNTAX_ERROR_NAME_EMPTY -10
# define XMLIGHT_SYNTAX_ERROR_NAME_TOO_LONG -11
# define XMLIGHT_SYNTAX_ERROR_NAME_END -12

# define XMLIGHT_SYNTAX_ERROR_TAG_END -20
# define XMLIGHT_SYNTAX_ERROR_TAG_WRONG_CLOSING -21
# define XMLIGHT_SYNTAX_ERROR_TAG_OTHER_TOP -22

# define XMLIGHT_SYNTAX_ERROR_KEY_EMPTY -30
# define XMLIGHT_SYNTAX_ERROR_KEY_TOO_LONG -31
# define XMLIGHT_SYNTAX_ERROR_KEY_END -32

# define XMLIGHT_SYNTAX_ERROR_VALUE_EMPTY -40
# define XMLIGHT_SYNTAX_ERROR_VALUE_TOO_LONG -41
# define XMLIGHT_SYNTAX_ERROR_VALUE_END -42
# define XMLIGHT_SYNTAX_ERROR_VALUE_START - 43

# define XMLIGHT_SYNTAX_ERROR_ATTRIBUTE_START -50


/** Read an xmlight source from the file input.
    The data read is stored in newly created list_forest that will be recorded in al.
    int return error value or XMLIGHT_SYNTAX_OK if OK.
**/
extern int ixemelle_fscan ( FILE * input ,
			    list_forest * ) ;

/** xmlight output onto the FILE.
 Each time there is non son, the  < ... /> form is used. **/
extern void ixemelle_fprint ( FILE * output ,
			      list_forest ) ;

# endif
