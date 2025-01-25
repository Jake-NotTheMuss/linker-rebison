/*
** lex.h
** Lexer state
*/

#ifndef lex_h
#define lex_h

#include "rebison.h"
#include "array.hh"

/* to create a new command, add it to this table and add a function
   void cmd_<command name>_f (LexState *ls) to cmd.cc */
#define CMDTABLE \
  DEFCMD(bison,   "(FILENAME=NULL)", \
         "Print the built grammar rules in bison format") \
  DEFCMD(echo,    "(...)",    "Print text") \
  DEFCMD(exit,    "(CODE=0)", "Exit the program") \
  DEFCMD(fun,     "",         "Enter a function definition context") \
  DEFCMD(help,    "",         "Display information about commands") \
  DEFCMD(reset,   "",         "Reset the parser to its initial state") \
  DEFCMD(rules,   "",         "Display information about each grammar rule") \
  DEFCMD(stack,   "", \
        "List the contents of the parser state/symbol stack") \
  DEFCMD(state,   "(STATE=-1)", \
         "Display information about a given parser state")\
  DEFCMD(tokens,  "",         "List the valid tokens of the language")

#define DEFCMD(e, _, __) CMD_##e,
enum {
  CMD_NONE,
  CMDTABLE
  CMD_COUNT
};
#undef DEFCMD

typedef struct {
  char *s;
  size_t n;
} Buffer;

typedef struct {
  int state, sym;
} State;

typedef struct LexState {
  FILE *f;  /* input file */
  Array<char> line;  /* current input line */
  char *pos;
  Buffer token, lookahead;
  int cmd;  /* current command being executed */
  int cmdstate;  /* state of current command execution */
  int divertpos;
  int yychar;
  int haveargs;  /* have arguments for the current command */
  Array<int> divert;  /* diversion array for buffering input tokens */
  Array<State> ssa;  /* state/symbol stack for yyparse */
  int *rules [NUM_RULES];
} LexState;

#define DEFCMD(e,_,__) extern void (cmd_##e##_f) (LexState *ls);
CMDTABLE
#undef DEFCMD

#define TK_IS(ls,str) (icmp(ls->token.s, str) == 0)

extern char *parsetoken (LexState *ls, Buffer *t);
extern char *gettoken (LexState *ls);
extern char *checktoken (LexState *ls);
extern char *lookaheadtoken (LexState *ls);
extern char *initline (LexState *ls);
extern void lexinit (LexState *ls);
extern void lexreset (LexState *ls);
extern void lexdestroy (LexState *ls);
extern void skipargs (LexState *ls);
extern int getargint (LexState *ls);

#endif /* lex_h */
