/*
** icmp.c
** caseless strcmp and strncmp
*/

#include <ctype.h>

int icmp (const char *s1, const char *s2) {
  for (; *s1 && *s2; s1++, s2++) {
    if (tolower(*s1) != tolower(*s2))
      return tolower(*s1) < tolower(*s2) ? -1 : 1;
  }
  return
  (tolower(*s1) == tolower(*s2) ? 0 :
   (tolower(*s1) < tolower(*s2) ? -1 : 1));
}

int incmp (const char *s1, const char *s2, int n) {
  for (; *s1 && *s2; s1++, s2++, n--) {
    if (n == 0) return 0;
    if (tolower(*s1) != tolower(*s2))
      return tolower(*s1) < tolower(*s2) ? -1 : 1;
  }
  return
  ((n == 0 || tolower(*s1) == tolower(*s2)) ? 0 :
   (tolower(*s1) < tolower(*s2) ? -1 : 1));
}
