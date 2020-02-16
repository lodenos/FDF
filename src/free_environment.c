#include "fdf.h"

void free_environment(envGlobal_t *envGlobal) {
  SDL_DestroyRenderer(envGlobal->renderer);
  SDL_DestroyWindow(envGlobal->window);
}
