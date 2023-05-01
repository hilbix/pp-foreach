#include <stdio.h>
#include "pp_repeat.h"

#define	LINEFEED

#define	ENUM1(...)			LINEFEED enum my_enums {
#define	ENUM2(N,NAME,...)		LINEFEED MY_ENUM_##NAME,
#define	ENUM3(...)			LINEFEED };

#define	FUNCTION1(...)
#define	FUNCTION2(N,NAME,ARGS,FN,HELP)	LINEFEED int MY_FN_##NAME ARGS { return FN; }
#define	FUNCTION3(...)

struct my_struct
  {
    const char	*name;
    int		(*fn)();
    int		nargs;
    const char	*help;
  };

#define	STRUCT1(...)			LINEFEED struct my_struct my_struct_data[] = {
#define	STRUCT2(N,NAME,ARGS,FN,HELP)	LINEFEED { #NAME, (int(*)())MY_FN_##NAME, N, HELP },
#define	STRUCT3(...)			LINEFEED 0 };

/* Generate the ENUM constants with offsets into the structure
 * including with the function
 */
PP_APPLY3(
/* Note: Perhaps we can calculate the number of args using a macro.
 * But my experiments with this failed for unknown reason.
 * (PP_NARGS did not work in the expansion)
 *  vvv */
  ( (2, add, (int x, int y), x+y, "add two numbers")
  , (2, sub, (int x, int y), x-y, "subtract second number from first one")
  , (1, neg, (int x),         -x, "negate a number")
  /* you can add more functions here easily	*/
  )
, ENUM
, FUNCTION
, STRUCT
)


int
main()
{
  struct my_struct *ptr;

  for (ptr=my_struct_data; ptr->name; ptr++)
    {
      printf("%s\t%s\n", ptr->name, ptr->help);
      switch (ptr->nargs)
        {
        case 1:
          printf("\texample: %s(%d) = %d\n", ptr->name, 1, ptr->fn(1));
          break;
        case 2:
          printf("\texample: %s(%d,%d) = %d\n", ptr->name, 1, 2, ptr->fn(1, 2));
          break;
        }
    }
  return 0;
}

