#include "devices.h"

void device_window_init(envGlobal_t *envGlobal) {
  register i32 retValue;
  retValue = SDL_CreateWindowAndRenderer(
      960, 540, SDL_WINDOW_RESIZABLE, &envGlobal->window, &envGlobal->renderer);
  if (retValue == -1) {
    put_string((u8 *)"SDL Error > ");
    put_string((u8 *)SDL_GetError());
    put_character('\n');
    exit(-1);
  }
  SDL_RenderClear(envGlobal->renderer);
}
