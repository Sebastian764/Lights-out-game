/**************************************************************************/
/*              COPYRIGHT Carnegie Mellon University 2023                 */
/* Do not post this file or any derivative on a public site or repository */
/**************************************************************************/
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "lib/contracts.h"
#include "lib/xalloc.h"
#include "lib/bitvector.h"
#include "board-ht.h"

// You are welcome to define helper functions for your tests

int main() {
  // Create a few struct board_data
  hdict_t a = ht_new(5);
  bitvector a1 = bitvector_new();
  struct board_data *entry = calloc(1, sizeof(struct board_data));
  entry->board = a1;
  // entry.test = 1;
  // entry.col = 1;
  // entry.row = 1;
  ht_insert(a, entry);
  struct board_data *atest = ht_lookup(a, a1);
  ASSERT(atest != NULL);

  // for (int i = 0; i < BITVECTOR_LIMIT; i++) {
  //   entry->board = bitvector_flip(a1, i);
  //   ht_insert(a, entry);
  // }

  // bitvector b = bitvector_new();
  // bitvector_flip(b, 10);
  // atest = ht_lookup(a, b);
  // ASSERT(atest != NULL);
  // bitvector_flip(b, 10);
  // bitvector_flip(b, 24);

  // for (int i = 0; i < BITVECTOR_LIMIT; i+= 2) {
  //   entry->board = bitvector_flip(a1, i);
  //   ht_insert(a, entry);
  // } //around 40

  // for (int i = BITVECTOR_LIMIT - 1; i <= 0; i--) {
  //   entry->board = bitvector_flip(a1, i);
  //   ht_insert(a, entry);
  // } //around 65

  // for (int i = BITVECTOR_LIMIT - 1; i <= 0; i-=2) {
  //   entry->board = bitvector_flip(a1, i);
  //   ht_insert(a, entry);
  // } //around 70

  //   entry->board = (bitvector)50;
  //   ht_insert(a, entry);


  // for (int i = 1; i < 50; i++) {
  //   entry->board = (bitvector)i;
  //   ht_insert(a, entry);
  // }
  // entry->board = (bitvector)40;
  // // printf("val: %d", entry->board);
  // // printf("val: %d", a1);
  // ht_insert(a, entry);

  // atest = ht_lookup(a, (bitvector)40);
  // ASSERT(atest != NULL);



  
  hdict_free(a);
  // free(entry);
  

  // Using them, test the functions you wrote in file board-ht.c



  printf("All tests passed!\n");
  return 0;
}
