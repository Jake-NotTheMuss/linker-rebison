/*
** cmd.cc
** command handlers
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rebison.h"
#include "lex.hh"
#include "array.hh"

extern void dumpstack (const Array<State> &array, int n);

/* in printf, provide an integer I and a plural prefix if necessary */
#define ARG_PL(i) (i), (i) == 1 ? "" : "s"

static int is_artifial (int yysym) {
  const char *name = yytname[yysym];
  return (!isalpha(*name) && *name != '_' && *name != '-');
}

/* dump all built grammar rules in yacc format */
static void dumprules (LexState *ls, const char *filename) {
  int i, lastsym = -1;
  FILE *f = filename ? fopen(filename, "w") : stdout;
  if (f == NULL)
    xerror("file '%s' cannot be opened", filename);
  for (i = 1; i < NUM_RULES; i++) {
    if (yyr1[i] == S_YYACCEPT) {
      if (ls->rules[i] != NULL)
        fprintf(f, "%%start %s\n\n", yytname[ls->rules[i][1]]);
      break;
    }
  }
  fprintf(f, "%%%%\n\n");
  for (i = 1; i < NUM_RULES; i++) {
    int sym = yyr1[i];
    int sep = sym != lastsym ? ' ' : '|';
    const char *name = yytname[sym];
    if (!ls->include_artificial && is_artifial(sym)) continue;
    if (sym == S_YYACCEPT) continue;
    /* print symbol name and ':' if this is the first rule in the group */
    if (sym != lastsym) {
      /* terminate the previous symbol if needed */
      if (lastsym != -1) fprintf(f, "  ;\n\n");
      fprintf(f, "%s:\n", name);
    }
    if (ls->rules[i] == NULL)
      fprintf(f, "  %c /* rule %d unbuilt (%d symbol%s) */\n", sep, i,
              ARG_PL(yyr2[i]));
    /* if the rule is built, print the RHS symbols */
    else {
      int n;
      fprintf(f, "  /* rule %d */\n  %c", i, sep);
      /* print rule RHS */
      for (n = 0; n < ls->rules[i][0]; n++) {
        int yysymbol = ls->rules[i][n+1];
        const char *name = yytname[yysymbol];
#ifdef TOKEN_PREFIX
        if (yysymbol < YYNTOKENS)
        if (strncmp(name, TOKEN_PREFIX, sizeof(TOKEN_PREFIX)-1) == 0)
          name += sizeof(TOKEN_PREFIX)-1;
#endif
        if (!ls->include_artificial &&
            yysymbol >= YYNTOKENS && is_artifial(yysymbol))
          continue;
        fprintf(f, " %s", name);
      }
      if (n == 0)
        fprintf(f, " %%empty");
      fprintf(f, "\n");
    }
    lastsym = sym;
  }
  if (filename) fclose(f);
}

/* :bison(FILENAME) */
void cmd_bison_f (LexState *ls) {
  char *name = NULL;
  if (ls->haveargs) {
    checktoken(ls);
    if (*ls->token.s != ')' && *ls->token.s != ',')
      name = ls->token.s;
  }
  dumprules(ls, name);
}

/* :echo(...) */
void cmd_echo_f (LexState *ls) {
  if (ls->haveargs) {
    int i = 0;
    checktoken(ls);
    while (*ls->token.s != ')') {
      if (*ls->token.s != ',') {
        if (i++) printf(" ");
        printf("%s", ls->token.s);
      }
      checktoken(ls);
    }
  }
  printf("\n");
}

/* :exit(CODE=0) */
void cmd_exit_f (LexState *ls) {
  int code = ls->haveargs ? getargint(ls) : 0;
  exit(code);
}

/* :fun(void) */
void cmd_fun_f (LexState *ls) {
#ifdef SCR_DATA
  ls->divert.push(TOKEN_FUNCTION);
  ls->divert.push(TOKEN_IDENTIFIER);
  ls->divert.push(TOKEN_LEFT_PAREN);
  ls->divert.push(TOKEN_RIGHT_PAREN);
  ls->divert.push(TOKEN_LEFT_CURLY);
#endif
}

/* :help(void) */
void cmd_help_f (LexState *ls) {
  (void)ls;
  const char *fmt = "  :%- 30s %s\n";
#define DEFCMD(e,str,str2) printf(fmt, #e str, str2);
  CMDTABLE
#undef DEFCMD
}

/* :rules(void) */
void cmd_rules_f (LexState *ls) {
  int i;
  printf("This language has %d rules and %d non-terminal symbols\n",
         NUM_RULES, NONTERMINAL_COUNT);
  for (i = 0; i < NUM_RULES; i++)
    printf("\tRule %d (%s): %d RHS symbols\n", i, yytname[yyr1[i]], yyr2[i]);
}

/* :stack(void) */
void cmd_stack_f (LexState *ls) {
  dumpstack(ls->ssa, -1);
}

/* return true if reducing rule YYN on state YYSTATE will cause an unavoidable
   error state after reduction */
static int reduce_then_error (LexState *ls, int yyn, int yytoken, int yystate){
  int yynewstate, yylen = yyr2[yyn];
  /* if the rule is empty, the top state is still YYSTATE after popping */
  if (yylen)
    yystate = ls->ssa[ls->ssa.count() - yylen].state;
  yyn = yyr1[yyn];
  yynewstate = yypgoto[yyn - YYNTOKENS] + yystate;
  if (0 <= yynewstate && yynewstate <= YYLAST &&
      yycheck[yynewstate] == yystate)
    yynewstate = yytable[yynewstate];
  else
    yynewstate = yydefgoto[yyn - YYNTOKENS];
  if (yypact[yynewstate] == YYPACT_NINF)
    return (yydefact[yynewstate] == 0);
  else {
    yyn = yypact[yynewstate] + yytoken;
    if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yytoken)
      return (yydefact[yynewstate] == 0);
    else
      return (yytable[yyn] == 0 || yytable[yyn] == YYTABLE_NINF);
  }
}

/* print information about a parser state YYSTATE, what actions are done on
   encountering each token */
void stateinfo (LexState *ls, int yystate) {
  int sa [YYNTOKENS], ra [YYNTOKENS], ea [YYNTOKENS], exa [YYNTOKENS];
  int sn = 0, rn = 0, en = 0, exn = 0;
  int i, yychar, iscurrstate = yystate < 0;
  if (iscurrstate)
    yystate = ls->ssa.gettop().state;
  printf("Information for state %d:\n", yystate);
  if (yypact[yystate] == YYPACT_NINF)
    printf("  State has only reductions\n");
  else {
    for (yychar = FIRST_TOKEN; yychar <= LAST_TOKEN; yychar++) {
      int yytoken = yytranslate[yychar];
      int yyn = yypact[yystate] + yytoken;
      if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yytoken) {
        yyn = yydefact[yystate];
        if (yyn == 0)
          ea[en++] = yytoken;
        else if (iscurrstate && reduce_then_error(ls, yyn, yytoken, yystate))
          exa[exn++] = yytoken;
        else
          ra[rn++] = yytoken;
      }
      else {
        yyn = yytable[yyn];
        if (yyn == 0 || yyn == YYTABLE_NINF)
          ea[en++] = yytoken;
        else if (yyn < 0)
          ra[rn++] = yytoken;
        else
          sa[sn++] = yytoken;
      }
    }
#define PRINTA(s,x) \
  if (x##n) { printf("  Tokens which cause " s ":\n"); \
  for (i = 0; i < x##n; i++) printf("\t%s\n", yytname[x##a[i]]); }
    PRINTA("reduction", r);
    PRINTA("shift", s);
    PRINTA("syntax error", e);
    PRINTA("reduction then immediate error", ex);
  }
#undef PRINTA
}

/* :state(STATE) */
void cmd_state_f (LexState *ls) {
  int yystate = ls->haveargs ? getargint(ls) : -1;
  stateinfo(ls, yystate);
}

/* :tokens(void) */
void cmd_tokens_f (LexState *ls) {
  int i;
  printf("Valid tokens:\n\tEOF\n");
  for (i = FIRST_TOKEN + 2; i <= LAST_TOKEN; i++) {
    const char *name = yytname[yytranslate[i]];
#ifdef TOKEN_PREFIX
    if (strncmp(name, TOKEN_PREFIX, sizeof(TOKEN_PREFIX)-1) == 0)
      name += sizeof(TOKEN_PREFIX)-1;
#endif
    printf("\t%s\n", name);
  }
}

/* :unbuilt(void) */
void cmd_unbuilt_f (LexState *ls) {
  int unbuilt [NUM_RULES] = {0};
  int i, n = 0;
  for (i = 1; i < NUM_RULES; i++)
    if (ls->rules[i] == NULL) unbuilt[n++] = i;
  printf("%d/%d rule%s built\n", (NUM_RULES - 1 - n), ARG_PL(NUM_RULES - 1));
  if (n) {
    printf("Unbulit rules:\n");
    for (i = 0; i < n; i++)
      printf("\tRule %d (%s)\n", unbuilt[i], yytname[yyr1[unbuilt[i]]]);
  }
}
