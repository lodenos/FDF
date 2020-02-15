#include "fdf.h"
#include <_string.h>
#include <stdio.h>

#include "_ctype.h"
#include "_stdlib.h"

#define BASE10 (u8 *)"0123456789"
#define BASEHEXA (u8 *)"0123456789ABCDEF"
#define LEN_MAX_HEXA 6

static inline i32 token_decimal(u8 *data, u32 *index) {
  i32 value = 0;
  while (is_numeric(data[*index])) {
    value *= 10;
    value += data[*index] - '0';
    ++*index;
  }
  return value;
}

static inline u32 token_hexadecimal(u8 *data, u32 *idx) {
  u8 *tmp;
  u32 value;
  // for tmp malloc enough
  convert_base(&data[*idx + 2], &data[*idx + 8], tmp, BASEHEXA, BASE10);
  *idx += 8;
  value = _atoi(tmp);
  free(tmp);
  return value;
}

static void token_point(u8 *data, u32 *index) {
  i32 sign = 1;
  if (data[*index] == '-') {
    sign = -1;
    ++*index;
  } else if (data[*index] == '+')
    ++*index;
  // token_decimal(data, index) * sign;
  if (data[*index] == ',') {
    ++*index;
    token_hexadecimal(data, index);
  }
}

////////////////////////////////////////////////////////////////////////////////

static map_t *format_checker(u8 *data, u64 lenght) {
  u32 numberLine = 0;
  u32 numberPoint = 0;
  u32 i = 0;
  for (register u32 itr = 0; itr < lenght; ++itr) {
    if (data[itr] == '\n')
      ++numberLine;
  }
  for (register u32 itr = 0; itr < lenght; ++itr) {
    if (data[itr] == ' ')
      continue;
    if (data[itr] == '\n') {
      // malloc a line
      numberPoint = 0;
    }
    if (is_numeric(data[itr]) || data[itr] == '+' || data[itr] == '-') {
      while (is_numeric(data[itr])) // add a limit
        ++itr;
      if (data[itr] == ' ')
        continue;
      if (data[itr] == '\n') {
        // malloc a line
        numberPoint = 0;
      }
      //////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////
      if (data[itr] == ',') {
        if (data[++itr] != 0)
          ; // ERROR
        if (data[++itr] != 'x')
          ; // ERROR
        i = 0;
        while (i < LEN_MAX_HEXA) {
          if (data[itr] >= 'a' && data[itr] <= 'f') {
            data[itr] -= ' ';
            ++i;
            ++itr;
            continue;
          }
          if (!is_numeric(data[itr]) && !(data[itr] >= 'A' && data[itr] <= 'F'))
            ; // ERROR
          ++i;
          ++itr;
        }
        if (data[itr] != ' ' && data[itr] != '\n')
          ; // ERROR
      }
      ++numberPoint;
    }
    // ERROR
  }
  return NULL;
}

u8 *open_read_data(u8 const *const pathname) {
  u8 *data = NULL;
  i32 fd;
  u64 memorySize;
  u8 *tmp;
  struct stat statbuf;
  if ((fd = open((char *)pathname, O_RDONLY)) == -1)
    return NULL;
  if (fstat(fd, &statbuf) == -1) {
    close(fd);
    return NULL;
  }
  memorySize = sizeof(u8) * ((u64)statbuf.st_size + 1);
  if ((data = (u8 *)_memalloc(memorySize)) == NULL) {
    close(fd);
    return NULL;
  }
  if (read(fd, (void *)tmp, (u64)statbuf.st_size) == -1) {
    free(data);
    close(fd);
    return NULL;
  }
  close(fd);
  return data;
}

map_t *parcer_map(u8 const *const pathname) {
  u8 *data;
  data = open_read_data(pathname);
  format_checker(data, _strlen(data));
  // Load data
  free(data);
  return NULL;
}
