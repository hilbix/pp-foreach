/* This Works is placed under the terms of the Copyright Less License,
 * see file COPYRIGHT.CLL.  USE AT OWN RISK, ABSOLUTELY NO WARRANTY.
 *
 * Read: This is free as free beer, free speech and free baby.
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "pp_repeat.h"

static void
OOPS(const char *s, ...)
{
  va_list	list;

  fprintf(stderr, "%s", s);
  va_start(list, s);
  for (; s; s=va_arg(list, const char *))
    fprintf(stderr, ": %s", s);
  va_end(list);
  fprintf(stderr, "\n");
  fflush(stderr);
  exit(23);
}

#define	TYPE				long long
#define	PTYPE				"%lld"
#define	STYPE				strtoll

/* Here is a recipe on how to use PP_APPLY3() properly
 */

#ifndef	LINEFEED
#define	LINEFEED			/* cpp -DLINEFEED=LINEFEED example.c | sed -n 's/LINEFEED/\n/gp' */
#endif

#define	ENUM1(...)			LINEFEED enum my_enums {
#define	ENUM2(N,NAME,...)		LINEFEED MY_ENUM_##NAME,
#define	ENUM3(...)			LINEFEED };

#define	FUNCTION1(...)
#define	FUNCTION2(N,NAME,ARGS,FN,HELP)	LINEFEED TYPE MY_FN_##NAME ARGS { return FN; }
#define	FUNCTION3(...)

struct my_struct
  {
    const char	*name;
    TYPE	(*fn)();
    int		nargs;
    const char	*help;
  };

#define	STRUCT1(...)			LINEFEED struct my_struct my_struct_data[] = {
#define	STRUCT2(N,NAME,ARGS,FN,HELP)	LINEFEED { #NAME, (TYPE(*)())MY_FN_##NAME, N, HELP },
#define	STRUCT3(...)			LINEFEED 0 };

/* Generate the ENUM constants with offsets into the structure
 * including with the function
 */
PP_APPLY3(
/* Note: Perhaps we can calculate the number of args using a macro.
 * But my experiments with this failed for unknown reason.
 * (PP_NARGS did not work in the expansion)
 *  vvv */
  ( (2, add, (TYPE x, TYPE y), x+y, "add two numbers")
  , (2, sub, (TYPE x, TYPE y), x-y, "subtract second number from first one")
  , (1, neg, (TYPE x),          -x, "negate number")
  , (2, mul, (TYPE x, TYPE y), x*y, "multiply two numbers")
  /* you can add more functions here easily	*/
  )
, ENUM
, FUNCTION
, STRUCT
)

static int
usage(void)
{
  struct my_struct *ptr;

  for (ptr=my_struct_data; ptr->name; ptr++)
    {
      printf("%s\t%s\n", ptr->name, ptr->help);
      switch (ptr->nargs)
        {
        default:
          OOPS("internal error: wrong argument count for %s", ptr->name, NULL);
        case 1:
          printf("\texample: %s %d: "PTYPE"\n", ptr->name, 1, ptr->fn(1));
          break;
        case 2:
          printf("\texample: %s %d %d: "PTYPE"\n", ptr->name, 2, 3, ptr->fn(1, 2));
          break;
        }
    }
  return 42;
}

struct _
  {
    int n;
    char **a;
  };

/* This is not meant to be optimal.
 * In fact it is probably the most stupid implementation.
 */
static TYPE
answer(struct _ *_)
{
  struct my_struct	*ptr;
  const char		*arg;
  char			*end;
  TYPE			n;

  /* get the next token	*/
  if (!_->n--)
    OOPS("out of arguments", NULL);
  arg	= *_->a++;

  /* check token being a function	*/
  for (ptr=my_struct_data; ptr->name; ptr++)
    if (!strcmp(arg, ptr->name))
      switch (ptr->nargs)
        {
        TYPE x;
        case 1:	return ptr->fn(answer(_));
        case 2:	x = answer(_); return ptr->fn(x,answer(_));
        }
  n	= STYPE(arg, &end, 0);
  if (!end || *end)
    OOPS("cannot interpret", arg, NULL);
  return n;
}


int
main(int argc, char **argv)
{
  if (argc<2)
    return usage();

  struct _ args = { argc-1, argv+1 };
  printf("the answer is "PTYPE"\n", answer(&args));
  if (args.n)
    OOPS("not all arguments were used starting with", *args.a, NULL);
  return 0;
}

