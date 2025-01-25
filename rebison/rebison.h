/*
** rebison.h
** Symbolic parser
*/

#include <limits.h>
#include <stddef.h>
#include <stdarg.h>
#include <assert.h>

#ifndef rebison_h
#define rebison_h

#include DATA_HEADER

#define ARRAY_COUNT(a) ((int)(sizeof(a) / sizeof(a[0])))

/* last index into yytable */
#define YYLAST (ARRAY_COUNT(yytable) - 1)
/* total number of parser states */
#define NUM_STATES ARRAY_COUNT(yydefact)
/* total number of rules */
#define NUM_RULES ARRAY_COUNT(yyr1)
/* number of non-terminal symbols in the language */
#define NONTERMINAL_COUNT ARRAY_COUNT(yydefgoto)
/* the token to start on when iterating through all possible tokens */
#define FIRST_TOKEN TOKEN_YYerror
/* number of terminal symbols in the language */
/* adding 1 accounts for S_YYEOF in the symbol list */
#define YYNTOKENS ((LAST_TOKEN + 1 - FIRST_TOKEN) + 1)

/* constants used by the parser */
#define YYEMPTY (-2)
#define YYEOF 0

extern void (xerror) (const char *fmt, ...);
extern void *(xmalloc) (size_t n);
extern void *(xrealloc) (void *mem, size_t n);
extern char *(xstrndup) (const char *s, size_t n);
extern void (free) (void *mem);
extern int (icmp) (const char *s1, const char *s2);
extern int (incmp) (const char *s1, const char *s2, int n);

#endif /* rebison_h */
