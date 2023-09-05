#include "lib/queue.h"
#include "lib/hdict.h"
#include "lib/xalloc.h"
#include "lib/contracts.h"
#include "lib/bitvector.h"
#include "lib/boardutil.h"
// #include "lib/queue-safe.o"
// #include "lib/hdict-safe.o"
#include "board-ht.h"
#include <stdlib.h>

bool zero_lights(bitvector bit) 
{
  bitvector a = bitvector_new();
  return bitvector_equal(a, bit);
}

bitvector press_button(bitvector bit, uint8_t row, uint8_t col, uint8_t width, uint8_t height) 
{
  REQUIRES(is_valid_boardsize(width,height));
  REQUIRES(is_valid_pos(row, col, width, height));

  // printf("INITIAL: \n");
  // print_board(bit, width,height);

  uint8_t center = get_index(row, col, width, height);

  bit = bitvector_flip(bit, center);
    // print_board(bit, width,height);

  
  // if (is_valid_pos(row, col, width, height)) {

  // }
  // printf("CENTER: \n");
  // print_board(bit, width,height);
  // printf("\nYour boolean variable is: %s\n",is_valid_pos(row + 1, col, width, height) ? "true" : "false");
  if (is_valid_pos(row - 1, col, width, height)) {
    uint8_t above = get_index(row - 1, col, width, height);
    bit = bitvector_flip(bit, above);
  }
  // printf("TOP: \n");
  // print_board(bit, width,height);


  if (is_valid_pos(row + 1, col, width, height)) {
    uint8_t below = get_index(row + 1, col, width, height);
    bit = bitvector_flip(bit, below);
  }
    // printf("BOTTOM: \n");
  // print_board(bit, width,height);

  
  if (is_valid_pos(row, col + 1, width, height)) {
    uint8_t right = get_index(row, col + 1, width, height);
    bit = bitvector_flip(bit, right);
  }
    // printf("RIGHT: \n");
  // print_board(bit, width,height);

  
  if (is_valid_pos(row, col - 1, width, height)) {
    uint8_t left = get_index(row, col - 1, width, height);
    bit = bitvector_flip(bit, left);
  }
    // printf("LEFT: \n");
  // print_board(bit, width,height);

      // print_board(bit, width,height);

  return bit;
}

void print_sol(hdict_t dict, bitvector org, bitvector new, uint8_t row, uint8_t col, uint8_t width, uint8_t height)
{
  // printf("Solution: \n");
  (void)col;
  (void)row;
  // print_board(org, width, height);
  // printf("new: \n");
  // print_board(new, width, height);
  // printf("\nYour boolean variable is: %s\n", bitvector_equal(org, new) ? "true" : "false");
  while (!bitvector_equal(org, new)) {
    struct board_data *a = ht_lookup(dict, new);
    ASSERT(a != NULL);
    fprintf(stdout, "%d:%d \n", (int)a->row, (int)a->col);
    new = press_button(a->board, a->row, a->col, width, height);
    // free(a);
  }
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "Usage: lightsout <board name>\n");
    return EXIT_FAILURE; // see below for what this means 
  }
  char *board_filename = argv[1]; //board info should be here

  bitvector bit = bitvector_new();
  uint8_t width = 0;
  uint8_t height = 0;
  // uint8_t *width = &width;
  // uint8_t *height = &height;

  if(!file_read(board_filename, &bit, &width, &height)) {
    fprintf(stderr, "invalid board");
    return EXIT_FAILURE;
  }
  
  ASSERT(is_valid_boardsize(width,height));
  if (zero_lights(bit)) {
    fprintf(stderr, "\nalready solved \n");
    return EXIT_SUCCESS;
  }
  // uint8_t size = (width) * (height);
  hdict_t dict = ht_new(10);

  // width = *width;
  // height = *height;
  // printf("w: %d h: %d", (int)width, (int)height);

  queue_t queue = queue_new();
  enq(queue, (void*)&bit);

   while (!queue_empty(queue)) {
    // Find a board that we haven’t looked at yet from the queue 
    bitvector B = *(bitvector*)deq(queue);
    
    for (uint8_t row = 0; row < height; row++) { 
      for (uint8_t col = 0; col < width; col++) {
        // uint8_t i = get_index(row, col, width, height);
        bitvector newboard = press_button(B, row, col, width, height);
    
        if (zero_lights(newboard)) {
          struct board_data *entry = calloc(1, sizeof(struct board_data));
          entry->board = newboard;
          entry->row = row;
          entry->col = col;
          ht_insert(dict, entry);

          print_sol(dict, bit, newboard, row, col, width, height);
          queue_free(queue, NULL);
                        // printf("end: \n");
                        // print_board(newboard, width,height);
          hdict_free(dict);
          return EXIT_SUCCESS;
        }

        if (ht_lookup(dict, newboard) == NULL) {
          struct board_data *entry = calloc(1, sizeof(struct board_data));
              // printf("RIGHT: \n");
              // print_board(newboard, width,height);
          entry->board = newboard;
          entry->row = row;
          entry->col = col;
          ht_insert(dict, entry);
          enq(queue, (void*)&entry->board);
          // free(entry->board);

        }
      }
    }
  }
  queue_free(queue, NULL);
  hdict_free(dict);
  fprintf(stderr, "\nno solution\n");
  return EXIT_FAILURE;
}


  /* Find way to get height and width of board try:
  get first 3 char of filename, ignore index 1. convert char to ascii, subtract 48
  maybe need to separate functions for both height and col */

  /* maybe create function to count lights? try:  (lights should be true)
  if (board[index]) lights++   */

  // multiply height and width, then raise 2 by that power
  // create hash table same capacity as above
  // create hash function that hashes by % CAPACITY
  // create helpher function to solve board, takes in bitvector board, height and width

  // create queue

  /* For helper function, need to define following helper functions:
  - press_button: takes old board, button to press (current index), returns new board:
    ex:   0 0 0   ------>  # # #
          # # #   index 1  # 0 #
        Try to do this by checking if all 4 slots are valid. If not valid
        ignore. If valid, flip. 
        For one above and below subtract or add width respectively
        for one to the left and one to the right same subtract or add 1
   */  
 

  // if (width < 0 || height < 0) {
  //   fprintf(stderr, "Invalud file format\n");
  //   fclose(file);
  //   return EXIT_FAILURE; // see below for what this means 
  // }

          // struct board_data entry; //*entry = xalloc(sizeof(struct board_data), 1);
          // entry.board = newboard;
          // ht_insert(dict, &entry);
          // enq(queue, (void*)&newboard);


  // print_board(bit, width,height);
  // printf("\n");
  // bitvector newboard = press_button(bit, 0, 0, width, height);
  // printf("1 last: \n");
  // print_board(newboard, width,height);
  // printf("second try: \n");
  // newboard = press_button(newboard, 1, 1, width, height);
  // printf("last: \n");
  // print_board(newboard, width,height);

