/*
 * libvimregex.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oniguruma.h"
#include "libvimregex.h"
#include "libvimregexparser.c"

/* for initial framework tests, original oniguruma regexes used here */
int vimre_vmatch(unsigned char *pattern, unsigned char *string, OnigRegion *region) {
  return vimre_omatch(pattern, string, region);
}

int vimre_omatch(unsigned char *pattern, unsigned char *string, OnigRegion *region) {
  int r;
  unsigned char *start, *range, *end;
  regex_t* reg;
  OnigErrorInfo einfo;
  OnigRegion *oreg;

   UChar* opattern = (UChar* )pattern;
   UChar* str      = (UChar* )string;

  r = onig_new(&reg, opattern, opattern + strlen((char* )opattern),
        ONIG_OPTION_DEFAULT, ONIG_ENCODING_ASCII, ONIG_SYNTAX_DEFAULT, &einfo);
  if (r != ONIG_NORMAL) {
    char s[ONIG_MAX_ERROR_MESSAGE_LEN];
    onig_error_code_to_str(s, r, &einfo);
    fprintf(stderr, "ERROR: %s\n", s);
    return -1;
  }

  oreg = onig_region_new();

  end   = str + strlen((char* )str);
  start = str;
  range = end;
  r = onig_search(reg, str, end, start, range, region, ONIG_OPTION_NONE);
  if (r >= 0) {
    /* so not the right way... */
    region = oreg;
    return r;
    /*int i;*/
    /*fprintf(stderr, "match at %d\n", r);*/
    /*for (i = 0; i < region->num_regs; i++) {*/
      /*fprintf(stderr, "%d: (%d-%d)\n", i, region->beg[i], region->end[i]);*/
    /*}*/
  }
  else if (r == ONIG_MISMATCH) {
    fprintf(stderr, "search fail\n");
    return -1;
  }

  else { /* error */
    char s[ONIG_MAX_ERROR_MESSAGE_LEN];
    onig_error_code_to_str
      (s, r);
    fprintf(stderr, "ERROR: %s\n", s);
    return -2;
  }

  if (r < 0) {
    onig_region_free(oreg, 1 /* 1:free self, 0:free contents only */);
  }
  onig_free(reg);
  onig_end();
}
