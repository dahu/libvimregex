#include <tap.h>
#include <string.h>
#include <stdio.h>
#include "oniguruma.h"
#include "libvimregex.h"

/* major kludge */
extern int o_pos;

int main(void) {
  OnigRegion oreg;
  plan_tests(3);
  ok(vimre_vmatch("a", "a", &oreg) == 0, "ordinary char atoms match");
  ok(oreg.beg[0] == 0, "beginning of ordinary match correct");
  ok(oreg.end[0] == 1, "end of ordinary match correct");

  o_pos = -1;   /* <-- yuck! */
  ok(vimre_vmatch("b", "b", &oreg) == 0, "ordinary char atoms match");
  ok(oreg.beg[0] == 0, "beginning of ordinary match correct");
  ok(oreg.end[0] == 1, "end of ordinary match correct");

  /*ok(vimre_vmatch("^\\w\\+\\s\\+\\w\\+", "abc def", &oreg) == 0, "character-class atoms match");*/
  /*ok(oreg.beg[0] == 0, "beginning of character-class match correct");*/
  /*ok(oreg.end[0] == 7, "end of character-class match correct");*/

  /*ok(vimre_vmatch("^\\w\\+\\s\\+(\\w\\+)", "abc def ghi", &oreg) == 0, "captured character-class atoms match");*/
  /*ok(oreg.beg[1] == 4, "beginning of captured character-class match correct");*/
  /*ok(oreg.end[1] == 7, "end of captured character-class match correct");*/
  return exit_status();
}
