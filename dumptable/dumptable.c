/*
** dumptable.c
** dump bison tables from linker_modtools.exe
*/

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern int icmp (const char *s1, const char *s2);

#ifndef OUTDIR
#define OUTDIR ""
#endif

static void FS_CreatePath (const char *OSPath) {
  void *base = GetModuleHandle(NULL);
  void (*fn) (const char *);
  __asm__("leaq %c1(%2), %0" : "=rm" (fn) : "i" (0x300e10), "r" (base) : );
  (*fn)(OSPath);
}

#define dumptable(dir, name, offset, tabsize, T, fmt) do { \
  uintptr_t base = (uintptr_t)GetModuleHandle(NULL); \
  T const *yytable = (void *)(base + offset); \
  int i; FILE *f, *f2; \
  const char *filename = OUTDIR "/" dir "/" name ".c"; \
  const char *header = OUTDIR "/" dir "/tables.h"; \
  FS_CreatePath(filename); \
  f = fopen(filename, "w"); \
  if (currdir == NULL || strcmp(currdir, dir) != 0) \
    f2 = fopen(header, "w"); \
  else \
    f2 = fopen(header, "a"); \
  currdir = dir; \
  if (f == NULL) { \
    fprintf(stderr, "cannot open file '%s'\n", filename); \
    return; \
  } \
  if (f2 == NULL) { \
    fprintf(stderr, "cannot open file '%s'\n", header); \
    return; \
  } \
  fprintf(f2, "extern \"C\" " #T " const %s [%d];\n", name, tabsize); \
  fprintf(f, "extern \"C\" {\n" #T " %s [%d] = {", name, tabsize); \
  for (i = 0; i < tabsize; i++) { \
    if (i > 0) fprintf(f, ","); \
    if (i % 10 == 0) fprintf(f, "\n  "); \
    else fprintf(f, " "); \
    fprintf(f, fmt, yytable[i]); \
  } \
  fprintf(f, "\n};\n}\n"); \
  fclose(f); \
  fclose(f2); \
} while (0)

#define dumptable_i(dir, name, offset, tabsize, T, fmt) \
  dumptable(dir, name, offset, tabsize, T, "% 4" fmt)

static void dumptables (void) {
  const char *currdir = NULL;
  dumptable_i("sproc", "yytable", 0xac4a68, 27, signed char, "d");
  dumptable_i("sproc", "yycheck", 0xac4a88, 27, signed char, "d");
  dumptable_i("sproc", "yypact", 0xac4a40, 32, signed char, "d");
  dumptable_i("sproc", "yydefact", 0xac4a18, 32, signed char, "d");
  dumptable_i("sproc", "yypgoto", 0xac4a60, 8, signed char, "d");
  dumptable_i("sproc", "yydefgoto", 0xac4a38, 8, signed char, "d");
  dumptable_i("sproc", "yytranslate",0xac47e0, 275, unsigned char, "d");
  dumptable_i("sproc", "yyr1", 0xac49e8, 22, unsigned char, "d");
  dumptable_i("sproc", "yyr2", 0xac4a00, 22, unsigned char, "d");
  dumptable  ("sproc", "yytname", 0xac4900, 28, const char *, "\"%s\"");

  dumptable_i("scr", "yytable", 0xaf5920, 1928, short, "hd");
  dumptable_i("scr", "yycheck", 0xaf6830, 1928, short, "hd");
  dumptable_i("scr", "yypact", 0xaf55b0, 385, short, "hd");
  dumptable_i("scr", "yydefact", 0xaf53c0, 385, unsigned char, "d");
  dumptable_i("scr", "yypgoto", 0xaf58c0, 42, short, "hd");
  dumptable_i("scr", "yydefgoto", 0xaf5550, 42, short, "hd");
  dumptable_i("scr", "yytranslate",0xaf78d0, 375, unsigned char, "d");
  dumptable_i("scr", "yyr1", 0xaf5240, 180, unsigned char, "d");
  dumptable_i("scr", "yyr2", 0xaf5300, 180, unsigned char, "d");
  dumptable  ("scr", "yytname", 0xaf7a50, 0xa2, const char *, "\"%s\"");

  dumptable_i("scr_sym", "yytable", 0xafb518, 36, signed char, "d");
  dumptable_i("scr_sym", "yycheck", 0xafb540, 36, signed char, "d");
  dumptable_i("scr_sym", "yypact", 0xafb4e0, 40, signed char, "d");
  dumptable_i("scr_sym", "yydefact", 0xafb4a8, 40, unsigned char, "d");
  dumptable_i("scr_sym", "yypgoto", 0xafb508, 10, signed char, "d");
  dumptable_i("scr_sym", "yydefgoto", 0xafb4d0, 10, signed char, "d");
  dumptable_i("scr_sym", "yytranslate", 0xafb290, 271, unsigned char, "d");
  dumptable_i("scr_sym", "yyr1", 0xafb478, 21, unsigned char, "d");
  dumptable_i("scr_sym", "yyr2", 0xafb490, 21, unsigned char, "d");
  dumptable  ("scr_sym", "yytname", 0xafb3a0, 26, const char *, "\"%s\"");
}

#ifdef __cplusplus
#define REMOTE_LOGGER_EXPORT extern "C" __declspec(dllexport) __fastcall
#else  /* __cplusplus */
#define REMOTE_LOGGER_EXPORT __declspec(dllexport) __fastcall
#endif /* __cplusplus */

REMOTE_LOGGER_EXPORT void RemoteLogger_Start(const char *program,
                                             const char *version,
                                             const char *buildmachine,
                                             const char *buildtype)
{
  (void)version; (void)buildmachine; (void)buildtype;
  if (icmp(program, "linker") == 0) {
    dumptables();
    ExitProcess(0);
  }
}
