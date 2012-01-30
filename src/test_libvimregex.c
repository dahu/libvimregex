#include <tap.h>
/*#include <string.h>*/
#include "oniguruma.h"
#include "libvimregex.h"

int main(void) {
  OnigRegion oreg;
  plan_tests(6);
  ok(vimreo_match("abc", "abc", &oreg) == 0, "ordinary char atoms match");
  ok(oreg.beg[0] == 0, "beginning of ordinary match correct");
  ok(oreg.end[0] == 3, "beginning of ordinary match correct");

  ok(vimreo_match("^\\w+\\s+\\w+", "abc def", oreg) == 0, "ordinary char atoms match");
  ok(oreg.beg[0] == 0, "beginning of ordinary match correct");
  ok(oreg.end[0] == 7, "beginning of ordinary match correct");
  /* FAIL! */
  printf("%d\n", oreg.end[0]);
  return exit_status();
}
