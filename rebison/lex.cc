/*
** lex.c
** Lexer state
*/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rebison.h"
#include "lex.hh"

char *parsetoken (LexState *ls, Buffer *t) {
  size_t n;
  char *startpos;
  if (t->s != NULL) *t->s = 0;
  assert(ls->pos != NULL);
  while (*ls->pos && isspace(*ls->pos)) ls->pos++;
  if (*ls->pos == '\n' || *ls->pos == 0)
    return NULL;
  startpos = ls->pos;
  switch (*ls->pos) {
    case '(': case ')': case ',': case ':': ls->pos++; break;
    default:
    while (*ls->pos) {
      int c = *ls->pos;
      if (isspace(c) || c == ')' || c == '(' || c == ',' || c == ':') break;
      ls->pos++;
    }
  }
  n = ls->pos - startpos;
  if (n + 1 > t->n) {
    t->n = n + 1;
    t->s = (char *)xrealloc(t->s, t->n);
  }
  memcpy(t->s, startpos, n);
  t->s[n] = '\0';
  return t->s;
}

char *gettoken (LexState *ls) {
  if (ls->lookahead.s && *ls->lookahead.s) {
    if (ls->token.n < ls->lookahead.n) {
      ls->token.n = ls->lookahead.n;
      ls->token.s = (char *)xrealloc(ls->token.s, ls->token.n);
    }
    strcpy(ls->token.s, ls->lookahead.s);
    *ls->lookahead.s = 0;
    return ls->token.s;
  }
  return parsetoken(ls, &ls->token);
}

char *checktoken (LexState *ls) {
  char *t = gettoken(ls);
  if (t == NULL) {
    assert(0);
    xerror("unexpected end of line");
  }
  return t;
}

char *lookaheadtoken (LexState *ls) {
  return parsetoken(ls, &ls->lookahead);
}

char *initline (LexState *ls) {
  if (ls->token.s) *ls->token.s = 0;
  if (ls->lookahead.s) *ls->lookahead.s = 0;
  /* get next input line */
  ls->line.clear();
  for (;;) {
    char c = getc(ls->f);
    if (c == EOF || c == '\n') c = 0;
    ls->line.push(c);
    if (c == 0) break;
  }
  return ls->pos = &ls->line[0];
}

void lexinit (LexState *ls) {
  int i;
  ls->token.s = ls->lookahead.s = NULL;
  lexreset(ls);
  ls->f = stdin;
  for (i = 0; i < ARRAY_COUNT(ls->rules); i++)
    ls->rules[i] = NULL;
}

void lexreset (LexState *ls) {
  ls->pos = NULL;
  ls->divert.destroy();
  ls->ssa.init();
  ls->cmd = CMD_NONE;
  ls->cmdstate = 0;
  ls->yychar = YYEMPTY;
  ls->haveargs = 0;
  ls->divertpos = 0;
  ls->token.n = ls->lookahead.n = 0x100;
  ls->token.s = (char *)xrealloc(ls->token.s, ls->token.n);
  ls->lookahead.s = (char *)xrealloc(ls->lookahead.s, ls->lookahead.n);
}

void lexdestroy (LexState *ls) {
  if (ls->f != stdin)
    fclose(ls->f);
  ls->f = NULL;
  ls->pos = NULL;
  ls->line.destroy();
  ls->divert.destroy();
  ls->ssa.destroy();
  free(ls->token.s);
  free(ls->lookahead.s);
  ls->token.s = ls->lookahead.s = NULL;
  ls->token.n = ls->lookahead.n = 0;
}

void skipargs (LexState *ls) {
  while (*ls->token.s != ')') checktoken(ls);
  gettoken(ls);
}

int getargint (LexState *ls) {
  int val = 0;
  checktoken(ls);
  if (*ls->token.s != ')')
    val = atoi(ls->token.s);
  return val;
}
