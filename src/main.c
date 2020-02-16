#include "fdf.h"

static void __attribute__((constructor)) __create_environment();
static void __attribute__((destructor)) __destroy_environment();

static envGlobal_t *__get_environment(void) {
  static envGlobal_t envGlobal = {0};
  return &envGlobal;
}

static void __create_environment(void) {
  envGlobal_t *tmp;
  tmp = __get_environment();
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    put_string((u8 *)SDL_GetError());
    put_character('\n');
    exit(-1);
  }
}

static void __destroy_environment(void) {
  free_environment(__get_environment());
  SDL_Quit();
}

int main(int argc, char **argv) {
  envGlobal_t *envGlobal;
  envGlobal = __get_environment();
  command_line_arguments(argc, argv);
  device_window_init(envGlobal);
  device_window_present(envGlobal);
  engine_FDF(envGlobal);
  events_manager(envGlobal);
  return 0;
}
