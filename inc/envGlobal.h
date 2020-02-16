#ifndef ENVGLOBAL_H
#define ENVGLOBAL_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct envGlobal_s envGlobal_t;

struct envGlobal_s {
  SDL_Event event;
  SDL_Renderer *renderer;
  SDL_Thread *threadEvent;
  SDL_Window *window;
  bool loopEventsManager;
};

#endif
