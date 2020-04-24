#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <libnet.h>

#include "simple_bmp.h"

#define  SIZE_K 42

uint64_t rdtsc ();
void kernel_setup (uint16_t **kern, int16_t ksize);
int main ()
{
  uint16_t **kernel = calloc (SIZE_K, sizeof (int *));
  for (int k = 0; k < SIZE_K; k++)
    kernel[k] = calloc (SIZE_K, sizeof (uint16_t));
  kernel_setup (kernel, SIZE_K);

}



uint64_t rdtsc ()
{
  unsigned int lo, hi;
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t) hi << 32) | lo;
}

void kernel_setup (uint16_t **kern, int16_t ksize)
{
  uint16_t st_val = 1;
  for (int j = 0; j < ksize; j++)
          kern[0][j] = st_val;

  for (int i = 1; i < ksize / 2 + 1; i++)
    {
      for (int j = 0; j < ksize; j++)
        {
          if (j >= i && j < (ksize - i))
            kern[i][j] = (uint16_t) (kern[i - 1][j] + (uint16_t) 1);
          else
            kern[i][j] = kern[i - 1][j];
        }

    }
  for (int i = 1; i < ksize / 2; i++)
    {
      for (int j = 0; j < ksize; j++)
        {
          kern[i + ksize / 2][j] = kern[ksize / 2 - i][j];
        }

    }

  for (int i = 0; i < ksize; i++)
    {
      for (int j = 0; j < ksize; j++)
        {
          printf ("%3hu ", kern[i][j]);
        }
      printf ("\n");
    }
}
