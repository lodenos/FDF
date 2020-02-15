#ifndef RGBA_H
#define RGBA_H

#include "_stdint.h"

typedef union rgba8 rgba8;

union rgba8 {
  u32 color;
  struct {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpa;
  };
};

#endif
