#include "events.h"

void events_manager(envGlobal_t *envGlobal) {
  envGlobal->loopEventsManager = true;
  while (envGlobal->loopEventsManager) {
    if (SDL_PollEvent(&envGlobal->event)) {
      if (envGlobal->event.type == SDL_QUIT) {
        exit(0);
      }
    }
  }
}
