/*
 * regex.h : External defs for Ozan Yigit's regex functions, for systems
 *	that don't have them builtin. See regex.c for copyright and other
 *	details.
 *
 * Note that this file can be included even if we're linking against the
 * system routines, since the interface is (deliberately) identical.
 *
 * George Ferguson, ferguson@cs.rochester.edu, 11 Sep 1991.
 */

#if defined(_AUX_SOURCE) || defined(USG)
/* Let them use ours if they wish.  */

#ifndef HAVE_RE_COMP
extern char *regcmp();
extern char *regex();
#define re_comp regcmp
#define re_exec regex
#endif

#else
#ifndef GENERATE_LIBRARY_PROTOS
#undef P
#define P(x)    ()
#endif /* GENERATE_LIBRARY_PROTOS */
extern char *re_comp P((const char *));
extern int   re_exec P((const char *));

#endif
