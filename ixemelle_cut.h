# ifndef __IXEMELLE_CUT_H__
# define __IXEMELLE_CUT_H__

# include "ixemelle.h"


/** Remove all tags that correspond to the criterion.
    Sub-tags are also removed.
 **/
extern int cut ( char const * criterion_str ,
		 list_forest  ) ;

# endif
