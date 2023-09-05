/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2023                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "lib/contracts.h"
#include "lib/bitvector.h"

// You are welcome to define helper functions for your tests

int main() {
  // Create a few bitvectors
  bitvector a = bitvector_new();
  assert(a == 0);
  assert(!bitvector_get(a, 1));
  bitvector a1 = bitvector_flip(a, 0);
  assert(bitvector_get(a1, 0));
  assert(a1 != 0);

  bitvector b = 2147483647;
  bitvector b1 = b;
  for (int i = 0; i < 32; i++) assert(bitvector_get(b, 1));
  for (int i = 0; i < 32; i++) {
    b1 = bitvector_get(b, 1);
    assert(!bitvector_get(b1, 1));
  }

  bitvector c = (bitvector)8589934591;
  //  printf("a1: %d",c);
  bitvector c1 = c;
  for (int i = 0; i < 32; i++) assert(bitvector_get(c, i)); //fails if 33
  for (int i = 0; i < 32; i++) {
    c1 = bitvector_get(c, 1);
    assert(!bitvector_get(c1, 1));
    // a1 = bitvector_flip(c, i);
    // assert(!bitvector_get(c1, 1));
  }


  // Using them, test the functions you wrote in file bitvector.c



  printf("All tests passed!\n");
  return 0;
}
