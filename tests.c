/* This Works is placed under the terms of the Copyright Less License,
 * see file COPYRIGHT.CLL.  USE AT OWN RISK, ABSOLUTELY NO WARRANTY.
 * Read: Free as in free beer, free speech and free baby
 *
 * Test the Macros.
 *
 * This perhaps needs GCC 11, as this is a bit eigen where it adds spaces.
 */

#include <stdio.h>
#include <string.h>

int
main()
{
#define PP_TEST(X,Y)	PP_TEST_(X,#Y,Y)
#define	PP_TEST_(X,Y,...)	if (strcmp(X,#__VA_ARGS__)) err=printf("#E#%s#%d#0#fail#\nfail: %s\ngive: %s\nwant: %s\n", __FILE__, __LINE__, Y, #__VA_ARGS__, X);
#define	PP_TEST_FAIL(...)	/* ignore those tests for now	*/

  int err = 0;
#include "pp_repeat.h"
  return !!err;
}

