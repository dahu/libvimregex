#include "oniguruma.h"

int vimre_match(unsigned char *pattern, unsigned char *string, OnigRegion *region);
int vimre_omatch(unsigned char *pattern, unsigned char *string, OnigRegion *region);
