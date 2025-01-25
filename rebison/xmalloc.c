/*
** $Id: hkscmalloc.c $
** xmalloc
** See Copyright Notice in lua.h
*/

#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void (xerror) (const char *fmt, ...);
extern void *(xmalloc) (size_t n);
extern void *(xrealloc) (void *mem, size_t n);
extern char *(xstrndup) (const char *s, size_t n);

extern const char *progname;

void xerror (const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "%s: ", progname);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  fputc('\n', stderr);
  abort();
}

void *xmalloc (size_t n) {
  return xrealloc(NULL, n);
}

void *xrealloc (void *mem, size_t n) {
  mem = realloc(mem, n);
  if (mem == NULL) {
    xerror("cannot allocate %lu: (%s)", (unsigned long)n, strerror(errno));
  }
  return mem;
}

char *xstrndup (const char *s, size_t n) {
  char *s1;
  size_t len = strlen(s);
  if (len < n)
    n = len;
  s1 = (char *)xmalloc(n + 1);
  memcpy(s1, s, n);
  s1[n] = '\0';
  return s1;
}
