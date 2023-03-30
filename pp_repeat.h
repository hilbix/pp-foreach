/* This Works is placed under the terms of the Copyright Less License,
 * see file COPYRIGHT.CLL.  USE AT OWN RISK, ABSOLUTELY NO WARRANTY.
 * Read: Free as in free beer, free speech and free baby
 *
 * Assembled basycally on ideas found at
 * - https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
 * - and numerous others
 */

#include "pp_foreach.h"
#include "pp_incdec.h"

/* PP_REPEAT(N,macro,args) runs macro(0,args macro(1,args) .. macro(N-1,args)
 */
#define	PP_REPEAT(x,...)	PP_IF(PP_NUM(x))(PP_EVAL(PP_REPEAT_(x,__VA_ARGS__)),PP_REPEAT(x,##__VA_ARGS__))
#define	PP_REPEAT_(x,y,...)	PP_IF(PP_FALSE(x))(,PP_OBSTRUCT(PP_REPEAT__)()(PP_DEC(x),y,##__VA_ARGS__)PP_OBSTRUCT(y)(PP_DEC(x),##__VA_ARGS__))
#define PP_REPEAT__()		PP_REPEAT_
PP_TEST("x \"hello world\" (0)\"hello world\" (1)\"hello world\" (2)y"	, x PP_REPEAT(3,"hello world")y)
PP_TEST("x PP_REPEAT(N,a,b)y"	, x PP_REPEAT(N,a,b)y)
PP_TEST("x a (0,b)a (1,b)y"	, x PP_REPEAT(2,a,b)y)
PP_TEST("x a (0,b)y"		, x PP_REPEAT(1,a,b)y)
PP_TEST("x y"			, x PP_REPEAT(0,a,b)y)
PP_TEST_FAIL(PP_REPEAT(1.0,a,b))

/* PP_REDUCE(check,macro,args) runs: while(check(args)) args = macro(args)
 * so the given macro must reduce/process the arguments (and return the remaining work) until check(args) returns false
 */
#define	PP_SUM(x,y,...)		x+y,##__VA_ARGS__
#define	PP_HAVE2ARGS(...)	PP_HAVE2ARGS_(PP_REST(__VA_ARGS__))
#define	PP_HAVE2ARGS_(...)	PP_HAVEARGS(__VA_ARGS__)
#define	PP_REDUCE(...)		PP_EVAL(PP_REDUCE_(__VA_ARGS__))
#define	PP_REDUCE_(x,y,...)	PP_IF(x(__VA_ARGS__))(PP_OBSTRUCT(PP_REDUCE__)()(x,y,y(__VA_ARGS__)),__VA_ARGS__)
#define PP_REDUCE__()		PP_REDUCE_
PP_TEST("x 1+2y"	, x PP_SUM(1,2)y)
PP_TEST("x 1+2,3y"	, x PP_SUM(1,2,3)y)
PP_TEST("x 0y"		, x PP_HAVE2ARGS()y)
PP_TEST("x 0y"		, x PP_HAVE2ARGS()y)
PP_TEST("x 0y"		, x PP_HAVE2ARGS(x)y)
PP_TEST("x 0y"		, x PP_HAVE2ARGS(x,)y)
PP_TEST("x 1y"		, x PP_HAVE2ARGS(x,y)y)
PP_TEST("x 1y"		, x PP_HAVE2ARGS(x,,z)y)
PP_TEST("x 1+2+3y"	, x PP_REDUCE(PP_HAVE2ARGS,PP_SUM,1,2,3)y)

#define	PP_COUNT(x,y,...)	PP_INC(x),##__VA_ARGS__
#define	PP_NARGS(...)		PP_IF(PP_HAVEARGS(__VA_ARGS__))(PP_REDUCE_(PP_HAVE2ARGS,PP_COUNT,0,##__VA_ARGS__,X),1)
PP_TEST("0"	, PP_NARGS())
PP_TEST("1"	, PP_NARGS(x))
PP_TEST("2"	, PP_NARGS(x,y))
PP_TEST("3"	, PP_NARGS(,,))
PP_TEST("4"	, PP_NARGS(a,,,))
PP_TEST("5"	, PP_NARGS(a,,,,z))

