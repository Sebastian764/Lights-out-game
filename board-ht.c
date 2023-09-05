#include "board-ht.h"
#include "lib/contracts.h"
#include "lib/hdict.h"

hdict_key entry_key(hdict_entry e)
{
  return &(((struct board_data *)e)->board);
}

bool key_equal(hdict_key k1, hdict_key k2)
{
  return bitvector_equal(*(bitvector*)k1, *(bitvector*)k2);
}

size_t key_hash(hdict_key k) 
{
  size_t var = 0;
  bitvector test = bitvector_new();
  
  for (uint8_t i = 0; i < BITVECTOR_LIMIT; i+= 2) {
    bitvector_flip(test, i);
  }

  for (uint8_t i = 0; i < BITVECTOR_LIMIT; i++) {
    if (bitvector_get(*((bitvector*)k), i)) var++;
    if (bitvector_equal(*((bitvector*)k), test)) var++;
  }

  // deterministic random number generator found csrc.nist.gov
  // (1103515245 * var + 12345) % 4294967296)
  return (size_t)abs((105145 * (int)var + 12345) % 4294966);
}

void entry_free(hdict_entry e)
{
  free(e);
}

hdict_t ht_new(size_t capacity)
{
  REQUIRES(0 < capacity);
  hdict_t result = hdict_new(capacity, &entry_key,
                  &key_equal,
                  &key_hash,
                  &entry_free);
  ENSURES(result != NULL);
  return result;
}

struct board_data *ht_lookup(hdict_t H, bitvector B)
{
  REQUIRES( H != NULL);
  hdict_key key = &B;
  return hdict_lookup(H, (void*)key);;
}

void ht_insert(hdict_t H, struct board_data *DAT)
{
  REQUIRES( H != NULL);
  REQUIRES(ht_lookup(H, DAT->board) == NULL);
  hdict_insert(H, (void*)(DAT));
  // hdict_insert(H, (void *)&(DAT->board));
  // free(DAT);
}
