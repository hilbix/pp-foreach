/* This Works is placed under the terms of the Copyright Less License,
 * see file COPYRIGHT.CLL.  USE AT OWN RISK, ABSOLUTELY NO WARRANTY.
 * Read: Free as in free beer, free speech and free baby
 *
 * This needs a CPP with ",## __VA_ARGS__" expanding to ""
 * (the empty argument list is based on the , beeing eaten on empty arguments)
 *
 * This was assembled from ideas presented elsewhere.
 * Ideas cannot be copyrighted in the legislation I live in.
 * Obvious wording ideas were taken over, as these cannot be copyrighted as well.
 * Hence I was able to remove all copyrights, if there were any.
 *
 * See also:
 * - https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms
 * - https://gist.github.com/Enelar/f17479cab879a04739c4feb794907741
 * - and numerous other findings via Google,
 * - plus things I found out myself.
 */

/* test macros
 *
 * For this just remove the first / of the comments after the macro definitions
 * and run this as: cpp pp_foreach.h
 */
#define PP_
#define PP_C	PP_PROBE(@)
#define	PP_N	X,N,
#define	PP_P	()
#define PP0	0
#define PP1	1
#define PP2	2

/* see tests.c	*/
#ifndef	PP_TEST
#define	PP_TEST(...)
#define	PP_TEST_FAIL(...)
#endif

/* PP_CAT(a,b,...) combine a##b into a single token, leave rest as-is.
 * Usually used with only 2 arguments
 */
#define	PP_CAT2(x,y)	PP_CAT(x,y)
#define PP_CAT(x,...)	PP_CAT_(x, __VA_ARGS__)
#define PP_CAT_(x,...)	PP_CAT__(x ## __VA_ARGS__)
#define	PP_CAT__(x)	x

/* PP_CHECK(x) checks for x expanded to PP_PROBE()
 * Notes:
 * - The argument to PP_PROBE() is arbitrary
 */
#define PP_PROBE(x)	x, 1,
#define PP_CHECK(...)	PP_SECOND(__VA_ARGS__, 0,)
#define PP_SECOND(x,y,...) y
PP_TEST("0"	, PP_CHECK())
PP_TEST("0"	, PP_CHECK(PP0))
PP_TEST("0"	, PP_CHECK(PP1))
PP_TEST("0"	, PP_CHECK(PP2))
PP_TEST("0"	, PP_CHECK(PP_))
PP_TEST("1"	, PP_CHECK(PP_C))
PP_TEST("1"	, PP_CHECK(PP_PROBE(@)))
PP_TEST("0"	, PP_CHECK(PP_PROBE))
PP_TEST("N"	, PP_CHECK(PP_N))
PP_TEST("N"	, PP_CHECK(,N))
PP_TEST("0"	, PP_CHECK(PP_P))
PP_TEST("0"	, PP_CHECK(()))

/* PP_PAREN(x) checks for x being a properly paired parenthese
 */
#define PP_PAREN(x)	PP_CHECK(PP_PAREN_ x)
#define PP_PAREN_(...)	PP_PROBE(@)
PP_TEST("0"	, PP_PAREN())
PP_TEST("0"	, PP_PAREN(PP0))
PP_TEST("0"	, PP_PAREN(PP1))
PP_TEST("0"	, PP_PAREN(PP2))
PP_TEST("0"	, PP_PAREN(PP_))
PP_TEST("1"	, PP_PAREN(PP_C))
PP_TEST("0"	, PP_PAREN(PP_PROBE))
PP_TEST("1"	, PP_PAREN(PP_PROBE(@)))
PP_TEST("N"	, PP_PAREN(PP_N))
PP_TEST("1"	, PP_PAREN(PP_P))
PP_TEST("1"	, PP_PAREN(()))
PP_TEST("1"	, PP_PAREN((something)))
PP_TEST_FAIL(	, PP_PAREN(,))

/* PP_TRUE(x) test x for being 1
 */
#define	PP_TRUE(x)	PP_CHECK(PP_CAT_(PP_TRUE_,x))
#define	PP_TRUE_1	PP_PROBE(@)
PP_TEST("0"	, PP_TRUE())
PP_TEST("0"	, PP_TRUE(0))
PP_TEST("1"	, PP_TRUE(1))
PP_TEST("0"	, PP_TRUE(2))
PP_TEST("0"	, PP_TRUE(PP0))
PP_TEST("1"	, PP_TRUE(PP1))
PP_TEST("0"	, PP_TRUE(PP2))
PP_TEST("0"	, PP_TRUE(PP_))
PP_TEST_FAIL(	, PP_TRUE(PP_C))
PP_TEST_FAIL(	, PP_TRUE(PP_N))
PP_TEST_FAIL(	, PP_TRUE(PP_P))
PP_TEST_FAIL(	, PP_TRUE(()))

/* PP_FALSE(x) tests x for being 0
 */
#define	PP_FALSE(x)	PP_CHECK(PP_CAT_(PP_FALSE_,x))
#define	PP_FALSE_0	PP_PROBE(@)
PP_TEST("0"	, PP_FALSE())
PP_TEST("1"	, PP_FALSE(0))
PP_TEST("0"	, PP_FALSE(1))
PP_TEST("0"	, PP_FALSE(2))
PP_TEST("1"	, PP_FALSE(PP0))
PP_TEST("0"	, PP_FALSE(PP1))
PP_TEST("0"	, PP_FALSE(PP2))
PP_TEST("0"	, PP_FALSE(PP_))
PP_TEST_FAIL(	, PP_FALSE(PP_C))
PP_TEST_FAIL(	, PP_FALSE(PP_N))
PP_TEST_FAIL(	, PP_FALSE(PP_P))
PP_TEST_FAIL(	, PP_FALSE(()))

/* PP_COMPL(x) inverts bool (for 0 or 1 only)
 */
#define PP_COMPL(x)	PP_CAT_(PP_COMPL_, x)
#define PP_COMPL_0	1
#define PP_COMPL_1	0
PP_TEST("PP_COMPL_"	, PP_COMPL())
PP_TEST("1"		, PP_COMPL(0))
PP_TEST("0"		, PP_COMPL(1))
PP_TEST("1"		, PP_COMPL(PP0))
PP_TEST("0"		, PP_COMPL(PP1))
PP_TEST("PP_COMPL_2"	, PP_COMPL(PP2))
PP_TEST("PP_COMPL_"	, PP_COMPL(PP_))
PP_TEST_FAIL(		, PP_COMPL(PP_C))
PP_TEST_FAIL(		, PP_COMPL(PP_N))
PP_TEST_FAIL(		, PP_COMPL(PP_P))
PP_TEST_FAIL(		, PP_COMPL(()))

/* PP_IIF(x)(y,...z) exand to y if x expands to 1, ...z if x expands to 0 else buggs
 */
#define PP_IIF(x) PP_CAT_(PP_IIF_, x)
#define PP_IIF_0(x, ...) __VA_ARGS__
#define PP_IIF_1(x, ...) x
PP_TEST("PP_IIF_(x,y)"	, PP_IIF()(x,y))
PP_TEST("y"		, PP_IIF(0)(x,y))
PP_TEST("x"		, PP_IIF(1)(x,y))
PP_TEST("y"		, PP_IIF(PP0)(x,y))
PP_TEST("x"		, PP_IIF(PP1)(x,y))
PP_TEST("PP_IIF_2(x,y)"	, PP_IIF(PP2)(x,y))
PP_TEST("PP_IIF_(x,y)"	, PP_IIF(PP_)(x,y))
PP_TEST_FAIL(		, PP_IIF(PP_C)(x,y))
PP_TEST_FAIL(		, PP_IIF(PP_N)(x,y))
PP_TEST_FAIL(		, PP_IIF(PP_P)(x,y))
PP_TEST_FAIL(		, PP_IIF(())(x,y))

/* PP_IF(x)(y,...z) same as PP_IIF, but x is converted to bool first
 */
#define PP_IF(x) PP_IIF(PP_TRUE(x))
PP_TEST("false"	, PP_IF()(true,false))
PP_TEST("false"	, PP_IF(0)(true,false))
PP_TEST("true"	, PP_IF(1)(true,false))
PP_TEST("false"	, PP_IF(PP0)(true,false))
PP_TEST("true"	, PP_IF(PP1)(true,false))
PP_TEST("false"	, PP_IF(PP2)(true,false))
PP_TEST("false"	, PP_IF(PP_)(true,false))
PP_TEST_FAIL(	, PP_IF(PP_C)(true,false))
PP_TEST_FAIL(	, PP_IF(PP_N)(true,false))
PP_TEST_FAIL(	, PP_IF(PP_P)(true,false))
PP_TEST_FAIL(	, PP_IF(())(true,false))

/* PP_WHEN(x)(...y) expand to nothing if x===0 else ...y
 */
#define PP_EAT(...)
#define PP_EXPAND(...) __VA_ARGS__
#define PP_WHEN(x) PP_IF(x)(PP_EXPAND, PP_EAT)
PP_TEST("z"	, PP_WHEN()(x,y)z)
PP_TEST("z"	, PP_WHEN(0)(x,y)z)
PP_TEST("x,yz"	, PP_WHEN(1)(x,y)z)
PP_TEST("z"	, PP_WHEN(2)(x,y)z)
PP_TEST("z"	, PP_WHEN(PP0)(x,y)z)
PP_TEST("x,yz"	, PP_WHEN(PP1)(x,y)z)
PP_TEST("z"	, PP_WHEN(PP2)(x,y)z)
PP_TEST("z"	, PP_WHEN(PP_)(x,y)z)
PP_TEST_FAIL(	, PP_WHEN(PP_C)(x,y)z)
PP_TEST_FAIL(	, PP_WHEN(PP_N)(x,y)z)
PP_TEST_FAIL(	, PP_WHEN(PP_P)(x,y)z)
PP_TEST_FAIL(	, PP_WHEN(())(x,y)z)

/* Helpers to prevent or enable expansion
 * such that things are passed to PP_EVAL() below
 */
#define PP_EMPTY()
#define PP_DEFER(x) x PP_EMPTY()
#define PP_OBSTRUCT(x) x PP_DEFER(PP_EMPTY)()

#define PP_EVAL(...)  PP_EVAL1(PP_EVAL1(PP_EVAL1(__VA_ARGS__)))
#define PP_EVAL1(...) PP_EVAL2(PP_EVAL2(PP_EVAL2(__VA_ARGS__)))
#define PP_EVAL2(...) PP_EVAL3(PP_EVAL3(PP_EVAL3(__VA_ARGS__)))
#define PP_EVAL3(...) PP_EVAL4(PP_EVAL4(PP_EVAL4(__VA_ARGS__)))
#define PP_EVAL4(...) PP_EVAL5(PP_EVAL5(PP_EVAL5(__VA_ARGS__)))
#define PP_EVAL5(...) PP_EVAL6(PP_EVAL6(PP_EVAL6(__VA_ARGS__)))
#define PP_EVAL6(...) PP_EVAL7(PP_EVAL7(PP_EVAL7(__VA_ARGS__)))
#define PP_EVAL7(...) PP_EVAL8(PP_EVAL8(PP_EVAL8(__VA_ARGS__)))
#define PP_EVAL8(...) PP_EVAL9(PP_EVAL9(PP_EVAL9(__VA_ARGS__)))
#define PP_EVAL9(...) __VA_ARGS__

/* PP_ISEMPTY(x) is true if the first argument is empty
 */
#define	PP_ISEMPTY(x,...)	PP_CHECK(PP_ISEMPTY_(PP_PAREN(x),PP_PAREN(x())))
#define	PP_ISEMPTY_(...)	PP_ISEMPTY__(__VA_ARGS__)
#define	PP_ISEMPTY__(a,b)	PP_ISEMPTY_##a##b
#define	PP_ISEMPTY_01		PP_PROBE(@)
#define	PP_NOTEMPTY(...)	PP_FALSE(PP_ISEMPTY(__VA_ARGS__))
PP_TEST("1"	, PP_ISEMPTY())
PP_TEST("0"	, PP_ISEMPTY(x))
PP_TEST("0"	, PP_ISEMPTY(()))
PP_TEST("0"	, PP_ISEMPTY({}))
PP_TEST("1"	, PP_ISEMPTY(,x))
PP_TEST("0"	, PP_ISEMPTY(x))
PP_TEST("0"	, PP_ISEMPTY(x,))
PP_TEST("0"	, PP_ISEMPTY((),))
PP_TEST("0"	, PP_NOTEMPTY())
PP_TEST("1"	, PP_NOTEMPTY(x))
PP_TEST("1"	, PP_NOTEMPTY(()))
PP_TEST("1"	, PP_NOTEMPTY({}))
PP_TEST("0"	, PP_NOTEMPTY(,x))
PP_TEST("1"	, PP_NOTEMPTY(x))
PP_TEST("1"	, PP_NOTEMPTY(x,))
PP_TEST("1"	, PP_NOTEMPTY((),))

/* PP_HAVEARGS(...) checks if it has arguments
 */
#define	PP_HAVEARGS(...)	PP_ISEMPTY(,##__VA_ARGS__ X)
PP_TEST("0"	, PP_HAVEARGS())
PP_TEST("1"	, PP_HAVEARGS(x))
PP_TEST("1"	, PP_HAVEARGS(()))
PP_TEST("1"	, PP_HAVEARGS(,))

/* PP_FIRST(x,...)	x
 * PP_REST(x,...)	...
 */
#define	PP_FIRST(x,...)	x		/* same as PP_IIF_1	*/
#define	PP_REST(x,...)	__VA_ARGS__	/* same as PP_IIF_0	*/
PP_TEST("a b"		, a PP_FIRST()b)
PP_TEST("a b"		, a PP_REST()b)
PP_TEST("a xb"		, a PP_FIRST(x,y,z)b)
PP_TEST("a y,zb"	, a PP_REST(x,y,z)b)

/* PP_FOREACH(macro, ...args) applies each args to macro, one by one
 */
#define	PP_FOREACH(x,...)	PP_EVAL(PP_FOREACH2(PP_FOREACH_,x,__VA_ARGS__))
#define	PP_FOREACH_(x,a)	a(x)
#define	PP_FOREACH2(x,y,...)	PP_WHEN(PP_HAVEARGS(__VA_ARGS__))(x(PP_FIRST(__VA_ARGS__),y) PP_OBSTRUCT(PP_FOREACH2_)()(x,y,PP_REST(__VA_ARGS__)))
#define	PP_FOREACH2_()		PP_FOREACH2
PP_TEST("x y"		, x PP_FOREACH(a)y)
PP_TEST("x a(b)y"	, x PP_FOREACH(a,b)y)
PP_TEST("x a(b) a(c)y"	, x PP_FOREACH(a,b,c)y)

/* PP_APPLY((...args), ...macro) applies ...args one-by-one to the given ...macros, in sequence
 */
#define	PP_APPLY(ARGS,...)	PP_EVAL(PP_FOREACH2(PP_APPLY_, ARGS, __VA_ARGS__))
#define	PP_APPLY_(FN,ARGS)	PP_OBSTRUCT(PP_FOREACH2_)()(PP_APPLY__, FN, PP_EXPAND ARGS)
#define	PP_APPLY__(ARG,FN)	PP_IF(PP_PAREN(ARG))(FN ARG, FN(ARG))
PP_TEST("a(hello) a(world) a(!) b(hello) b(world) b(!)x",	PP_APPLY((hello,world,!),a,b)x)

/* PP_APPLY3((...args), macroa, macrob, .., macroz) as before
 * but:
 * - first runs macroa1(allargs) a single time
 * - then runs for each arg macroa2(arg)
 * - then runs  macroa3(allargs) a single time
 * - Then repeats with macrob and so on
 *
 * So the expansion looks like this:
 *
 * macroa1(args)
 * macroa2(firstarg)
 * macroa2(secondarg)
 * ..
 * macroa2(lastarg)
 * macroa3(args)
 * macrob1(args)
 * macrob2(firstarg)
 * macrob2(secondarg)
 * ..
 * macrob2(lastarg)
 * macrob3(args)
 * macroc1(args)
 * ..
 * macroy3(args)
 * macroz1(args)
 * macroz2(firstarg)
 * macroz2(secondarg)
 * ..
 * macroz2(lastarg)
 * macroz3(args)
 *
 * This way you can create enums, functions, structures, and so on as you like,
 * see example.c
 */
#define	PP_APPLY3(ARGS,...)	PP_EVAL(PP_FOREACH2(PP_APPLY3_, ARGS, __VA_ARGS__))
#define	PP_APPLY3_(FN,ARGS)	PP_APPLY3_1(FN,ARGS)PP_OBSTRUCT(PP_FOREACH2_)()(PP_APPLY3_2, FN, PP_EXPAND ARGS)PP_APPLY3_3(FN, ARGS)
#define	PP_APPLY3_1(FN,ARGS)	FN##1 ARGS
#define	PP_APPLY3_2(ARG,FN)	PP_IF(PP_PAREN(ARG))(FN##2 ARG, FN##2(ARG))
#define	PP_APPLY3_3(FN,ARGS)	FN##3 ARGS
PP_TEST("a1 (x,y,z)a2(x) a2(y) a2(z) a3 (x,y,z) b1 (x,y,z)b2(x) b2(y) b2(z) b3 (x,y,z) c1 (x,y,z)c2(x) c2(y) c2(z) c3 (x,y,z)!",	PP_APPLY3((x,y,z),a,b,c)!)
PP_TEST("a1 ((x,x),(y,y),(z,z))a2 (x,x) a2 (y,y) a2 (z,z) a3 ((x,x),(y,y),(z,z)) b1 ((x,x),(y,y),(z,z))b2 (x,x) b2 (y,y) b2 (z,z) b3 ((x,x),(y,y),(z,z)) c1 ((x,x),(y,y),(z,z))c2 (x,x) c2 (y,y) c2 (z,z) c3 ((x,x),(y,y),(z,z))!",	PP_APPLY3(((x,x),(y,y),(z,z)),a,b,c)!)

/* Same as PP_APPLY3, but the "after" function is not called.
 */
#define	PP_APPLY2(ARGS,...)	PP_EVAL(PP_FOREACH2(PP_APPLY2_, ARGS, __VA_ARGS__))
#define	PP_APPLY2_(FN,ARGS)	PP_APPLY2_1(FN,ARGS)PP_OBSTRUCT(PP_FOREACH2_)()(PP_APPLY2_2, FN, PP_EXPAND ARGS)
#define	PP_APPLY2_1(FN,ARGS)	FN##1 ARGS
#define	PP_APPLY2_2(ARG,FN)	PP_IF(PP_PAREN(ARG))(FN##2 ARG, FN##2(ARG))
PP_TEST("a1 (x,y,z)a2(x) a2(y) a2(z) b1 (x,y,z)b2(x) b2(y) b2(z) c1 (x,y,z)c2(x) c2(y) c2(z)!",	PP_APPLY2((x,y,z),a,b,c)!)
PP_TEST("a1 ((x,x),(y,y),(z,z))a2 (x,x) a2 (y,y) a2 (z,z) b1 ((x,x),(y,y),(z,z))b2 (x,x) b2 (y,y) b2 (z,z) c1 ((x,x),(y,y),(z,z))c2 (x,x) c2 (y,y) c2 (z,z)!",	PP_APPLY2(((x,x),(y,y),(z,z)),a,b,c)!)

