#include <stdio.h>

float roundf(float x)
{
  int signbit;
  typedef union {
        unsigned u;
        float f;
    } ufloat;
  ufloat uf;
  uf.f = x;
  unsigned w = uf.u;
  /* Most significant word, least significant word. */
  int exponent_less_127;

  /* Extract sign bit. */
  signbit = w & 0x80000000;

  /* Extract exponent field. */
  exponent_less_127 = (int)((w & 0x7f800000) >> 23) - 127;

  if (exponent_less_127 < 23)
    {
      if (exponent_less_127 < 0)
        {
          w &= 0x80000000;
          if (exponent_less_127 == -1)
            /* Result is +1.0 or -1.0. */
            w |= ((unsigned)127 << 23);
        }
      else
        {
          unsigned int exponent_mask = 0x007fffff >> exponent_less_127;
          if ((w & exponent_mask) == 0)
            /* x has an integral value. */
            return x;

          w += 0x00400000 >> exponent_less_127;
          w &= ~exponent_mask;
        }
    }
  else
    {
      if (exponent_less_127 == 128)
        /* x is NaN or infinite. */
        return x + x;
      else
        return x;
    }
  return x;
}


int main() {
  float x = 1.5;
  printf("%f\n", roundf(x));
}