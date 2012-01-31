/*
 * libvimregex.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oniguruma.h"
#include "libvimregex.h"


/* crude */
int copied_pattern = 0;
unsigned char *vim_pattern = NULL;
unsigned char *onig_pattern = NULL;
unsigned char o_pattern[1024];
int o_pos = -1;

void add_to_pattern(unsigned char *s) {
  size_t len = strlen(s);
  if (o_pos == -1) {
    o_pattern[0] = '\0';
  }
  strncat(o_pattern, s, len);
  o_pos += len;
}

#define YY_INPUT(buf, result, max)          \
{                                           \
  if (!copied_pattern) {                    \
    result= strlen(vim_pattern);            \
    memcpy(buf, vim_pattern, result + 1);   \
    copied_pattern = 1;                     \
  }                                         \
}

/*#define YY_DEBUG*/
#include "libvimregexparser.c"


int vimre_vmatch(unsigned char *pattern, unsigned char *string, OnigRegion *region) {
  copied_pattern = 0;
  vim_pattern = pattern;
  while (yyparse())
    ;
  /* should collect resulting onig_pattern from previous parse */
  /* for now, fudge to the original */
  /*onig_pattern = pattern;*/
  onig_pattern = o_pattern;
  return vimre_omatch(onig_pattern, string, region);
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
