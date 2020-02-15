#ifndef VECTOR_H
#define VECTOR_H

#include "_stdint.h"

typedef union f32v4 f32v4;

union f32v4 {
  f32 vector[4];
  struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
  };
};

#endif
