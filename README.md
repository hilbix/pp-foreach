# PP_FOREACH

Foreach loop for C Preprocessor

## Usage

	git submodule add https://github.com/hilbix/pp-foreach.git
	ln --relative -s pp-foreach/*.h .

then

	#include "pp_foreach.h"

## EXAMPLE

From <pp_foreach.h>:

	#include "pp_foreach.h"
	PP_APPLY((hello,world,!),a,b)x

gives

	a(hello) a(world) a(!) b(hello) b(world) b(!)x

From <pp_repeat.h>:

	#include "pp_repeat.h"
	PP_REPEAT(3,"hello world"))

gives

	"hello world" (0)"hello world" (1)"hello world" (2)

and

	#include "pp_repeat.h"
	PP_REDUCE(PP_HAVE2ARGS,PP_SUM,1,2,3)

with the given

	#define PP_SUM(x,y,...)	x+y,##__VA_ARGS__

gives

	1+2+3

Note that it would also work with something like

	#define PP_SUM(x,y,...)	x+y,__VA_ARGS__

## FAQ

WTF why?

- Because I always wanted it since the 1980s!

License?

- This Works is placed under the terms of the Copyright Less License,  
  see file COPYRIGHT.CLL.  USE AT OWN RISK, ABSOLUTELY NO WARRANTY.
- Read: Free as free beer, free speech and free baby.

