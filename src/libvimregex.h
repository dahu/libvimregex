#ifndef LIBVIMREGEX_H
#define LIBVIMREGEX_H

#include "oniguruma.h"

int vimre_omatch(unsigned char *pattern, unsigned char *string, OnigRegion *region);
int vimre_vmatch(unsigned char *pattern, unsigned char *string, OnigRegion *region);

#endif /* LIBVIMREGEX_H */
