#include "devices.h"

void device_window_present(envGlobal_t *envGlobal) {
  SDL_RenderPresent(envGlobal->renderer);
}
