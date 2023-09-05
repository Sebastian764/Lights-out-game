#include "lib/bitvector.h"
#include "lib/contracts.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#if (BITVECTOR_LIMIT <= 8)
#define BITLIMIT uint8_t

#elif (BITVECTOR_LIMIT <= 16) 
#define BITLIMIT uint8_t

#elif (BITVECTOR_LIMIT <= 32) 
#define BITLIMIT uint32_t

#else
#define BITLIMIT uint64_t
#endif

bitvector bitvector_new()
{
  return 0;
}

bool bitvector_get(bitvector B, uint8_t i)
{
  REQUIRES(i < BITVECTOR_LIMIT);
  bitvector copy = B;
  int new_val = copy & ((BITLIMIT)1 << (BITLIMIT)i); //changed from uint64_t to BITLIMIT
  return new_val != 0;
}
bitvector bitvector_flip(bitvector B, uint8_t i)
{
  REQUIRES(i < BITVECTOR_LIMIT);
  bitvector copy = B;
  return copy ^ ((BITLIMIT)1 << (BITLIMIT)i); 
}

bool bitvector_equal(bitvector B1, bitvector B2)
{
  return B1 == B2;
}
