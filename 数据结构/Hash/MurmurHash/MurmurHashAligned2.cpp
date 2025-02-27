//-----------------------------------------------------------------------------
// MurmurHashAligned2, by Austin Appleby

// Same algorithm as MurmurHash2, but only does aligned reads - should be safer
// on certain platforms.

// Performance will be lower than MurmurHash2

#define MIX(h, k, m)                                                                                                                                           \
  {                                                                                                                                                            \
    k *= m;                                                                                                                                                    \
    k ^= k >> r;                                                                                                                                               \
    k *= m;                                                                                                                                                    \
    h *= m;                                                                                                                                                    \
    h ^= k;                                                                                                                                                    \
  }

unsigned int MurmurHashAligned2(const void *key, int len, unsigned int seed)
{
  const unsigned int m = 0x5bd1e995;
  const int r = 24;

  const unsigned char *data = (const unsigned char *)key;

  unsigned int h = seed ^ len;

  int align = (int)data & 3;

  if (align && (len >= 4))
  {
    // Pre-load the temp registers

    unsigned int t = 0, d = 0;

    switch (align)
    {
      case 1:
        t |= data[2] << 16;
      case 2:
        t |= data[1] << 8;
      case 3:
        t |= data[0];
    }

    t <<= (8 * align);

    data += 4 - align;
    len -= 4 - align;

    int sl = 8 * (4 - align);
    int sr = 8 * align;

    // Mix

    while (len >= 4)
    {
      d = *(unsigned int *)data;
      t = (t >> sr) | (d << sl);

      unsigned int k = t;

      MIX(h, k, m);

      t = d;

      data += 4;
      len -= 4;
    }

    // Handle leftover data in temp registers

    d = 0;

    if (len >= align)
    {
      switch (align)
      {
        case 3:
          d |= data[2] << 16;
        case 2:
          d |= data[1] << 8;
        case 1:
          d |= data[0];
      }

      unsigned int k = (t >> sr) | (d << sl);
      MIX(h, k, m);

      data += align;
      len -= align;

      //----------
      // Handle tail bytes

      switch (len)
      {
        case 3:
          h ^= data[2] << 16;
        case 2:
          h ^= data[1] << 8;
        case 1:
          h ^= data[0];
          h *= m;
      };
    }
    else
    {
      switch (len)
      {
        case 3:
          d |= data[2] << 16;
        case 2:
          d |= data[1] << 8;
        case 1:
          d |= data[0];
        case 0:
          h ^= (t >> sr) | (d << sl);
          h *= m;
      }
    }

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
  }
  else
  {
    while (len >= 4)
    {
      unsigned int k = *(unsigned int *)data;

      MIX(h, k, m);

      data += 4;
      len -= 4;
    }

    //----------
    // Handle tail bytes

    switch (len)
    {
      case 3:
        h ^= data[2] << 16;
      case 2:
        h ^= data[1] << 8;
      case 1:
        h ^= data[0];
        h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
  }
}
