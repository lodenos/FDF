#ifndef FDF_H
#define FDF_H

#include "_stdint.h"
#include "rgba.h"
#include "vector.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct map_s map_t;

struct map_s {
  f32v4 **line;
  rgba8 **color;
  u32 *sizeLine;
  u32 numberLine;
};

extern map_t *parcer_map(u8 const *restrict const pathname);

#endif
