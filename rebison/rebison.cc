/*
** rebison.c
** Symbolic parser
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "rebison.h"
#include "lex.hh"

const char *progname = "rebison";

/* a code returned by yylex which tells the parser to reset its state */
#define YYRESET (-100)

/* convert a command name to its enumeration value */
static int getcmdenum (const char *cmd) {
#define DEFCMD(e, _, __) if (icmp(cmd, #e) == 0) return CMD_##e;
  CMDTABLE
  return CMD_NONE;
#undef DEFCMD
}


/* command callback for :stack() */
void dumpstack (const Array<State> &array, int n) {
  const size_t an = array.count();
  if (n == -1)
    n = array.count();
  assert((size_t)n <= array.count() || n == 0);
  printf("  Symbol/State stack (%d symbol%s):\n", n, n == 1 ? "" : "s");
  if (n == 0)
    printf("\t\t%%empty\n");
  else for (; n > 0; n--) {
    const State &s = array[an-n];
    printf("\t\t%s (state %d)\n", yytname[s.sym], s.state);
  }
}

static void record_reduction (LexState *ls, int yyn) {
  int *rule;
  int yylen = yyr2[yyn];
  if (ls->rules[yyn] != NULL)
    return;
  rule = ls->rules[yyn] = (int *)xmalloc((yylen + 1) * sizeof(int));
  *rule++ = yylen;
  for (; yylen; yylen--) {
    const State &s = ls->ssa[ls->ssa.count() - yylen];
    *rule++ = s.sym;
  }
}


static void lexerror (LexState *ls, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  printf("Lex error: ");
  vprintf(fmt, ap);
  va_end(ap);
  printf("\n");
  ls->pos = NULL;
  ls->haveargs = 0;
  ls->divert.destroy();
  ls->cmd = CMD_NONE;
  ls->divertpos = 0;
}

#define cmd_reset_f(ls) return YYRESET

/* YYLEX reads commands/tokens from the user to provide input to the symbolic
   parser */
static int yylex (LexState *ls) {
  if ((size_t)ls->divertpos < ls->divert.count()) {
    int yychar = ls->divert[ls->divertpos++];
    if ((size_t)ls->divertpos == ls->divert.count()) {
      ls->divert.clear();
      ls->divertpos = 0;
    }
    return yychar;
  }
  printf("Enter the next token:\n");
  initline(ls);
  if (gettoken(ls) == NULL)
    exit(0);
  do {
    /* check for command */
    if (*ls->token.s == ':') {
      /* get command name */
      int cmd = (checktoken(ls), getcmdenum(ls->token.s));
      if (cmd == CMD_NONE) {
        lexerror(ls, "unrecognized command '%s'", ls->token.s);
        return yylex(ls);
      }
      /* check for arguments */
      ls->haveargs = lookaheadtoken(ls) && *ls->lookahead.s == '(';
      if (ls->haveargs) gettoken(ls);  /* discharge lookahead */
      switch (cmd) {
#define DEFCMD(e,_,__) case CMD_##e: cmd_##e##_f(ls); break;
        CMDTABLE
#undef DEFCMD
      }
      if (ls->haveargs) skipargs(ls); /* skip over unused arguments */
    }
    /* check for YYEOF */
    else if (TK_IS(ls, "EOF"))
      ls->divert.push(YYEOF);
    /* check for token name */
    else {
      int i;
      for (i = FIRST_TOKEN; i <= LAST_TOKEN; i++) {
        const char *name = yytname[yytranslate[i]];
#ifdef TOKEN_PREFIX
        if (strncmp(name, TOKEN_PREFIX, sizeof(TOKEN_PREFIX)-1) == 0)
          name += sizeof(TOKEN_PREFIX)-1;
#endif
        if (icmp(ls->token.s, name) == 0) {
          ls->divert.push(i);
          break;
        }
      }
      if (i > LAST_TOKEN) {
        lexerror(ls, "Unexpected token: '%s'", ls->token.s);
        return yylex(ls);
      }
    }
  } while (gettoken(ls));
  return yylex(ls);
}

/* the symbolic parser processes pure syntax, without any semantics */
static void yyparse (LexState *ls) {
  /* for each state, start at that state and parse the current combination of
     tokens until an error or accept is reached, or until the target reduction
     occurs, given by YYLEN, YYN */
  int yystate, yytoken, yyn, yylen, yysym;
  goto yyinit;
  yyreset:
  printf("Resetting parser state.\n\n");
  yyinit:
  ls->yychar = YYEMPTY;
  yystate = 0;
  yysym = S_YYUNDEF;
  lexreset(ls);
  yynewstate:
  ls->ssa.inc();
  goto yysetstate;
  yysetstate:
  ls->ssa.gettop().state = yystate;
  ls->ssa.gettop().sym = yysym;
  goto yybackup;
  yybackup:
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;
  /* check if there is a look-ahead token ready */
  if (ls->yychar == YYEMPTY)
    ls->yychar = yylex(ls);
  if (ls->yychar == YYRESET)
    goto yyreset;
  if (ls->yychar <= YYEOF)
    ls->yychar = yytoken = YYEOF;
  else
    yytoken = yytranslate[ls->yychar];
  printf("Lookahead is %s\n", yytname[yytoken]);
  /* perform action for this token */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0) {
    if (yyn == YYTABLE_NINF)
      goto yyerrlab;
    yyn = -yyn;
    goto yyreduce;
  }
  /* discharge lookahead, shift to state YYN */
  ls->yychar = YYEMPTY;
  yystate = yyn;
  yysym = yytoken;
  printf("Shifting to state %d\n", yystate);
  printf("----\n");
  goto yynewstate;
  /* default reduction */
  yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  printf("default ");
  goto yyreduce;
  /* reduction */
  yyreduce:
  printf("reduce: rule %d (%s):\n", yyn, yytname[yyr1[yyn]]);
  yylen = yyr2[yyn];
  dumpstack(ls->ssa, yylen);
  record_reduction(ls, yyn);
  if (yystate == YYFINAL) {
    printf("Accept state reached\n\n");
    goto yyreset;
  }
  /* perform goto */
  ls->ssa.pop(yylen);
  yylen = 0;
  yysym = yyn = yyr1[yyn];
  yystate = yypgoto[yyn - YYNTOKENS] + ls->ssa.gettop().state;
  if (0 <= yystate && yystate <= YYLAST &&
      yycheck[yystate] == ls->ssa.gettop().state)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];
  printf("Going to state %d\n", yystate);
  printf("----\n");
  goto yynewstate;
  yyerrlab: {
    printf("ERROR: parse error occurred\n");
    dumpstack(ls->ssa, -1);
    goto yyreset;
  }
}

int main (int argc, const char *argv []) {
  int i;
  LexState ls = {0};
  ls.f = stdin;
  ls.include_artificial = 1;
  for (i = 1; i < argc; i++) {
    if (icmp(argv[i], "-n") == 0)
      ls.include_artificial = 0;
  }
  lexinit(&ls);
  yyparse(&ls);
  lexdestroy(&ls);
  return 0;
}
