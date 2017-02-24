#include <SDL2/SDL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
SDL_Window* window = NULL;
SDL_Surface* surface = NULL;

bool init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  } else {
    window = SDL_CreateWindow(
      "SDL test",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return false;
    } else {
      surface = SDL_GetWindowSurface(window);
      SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
      SDL_UpdateWindowSurface(window);
    }
  }
  return true;
}

SDL_Rect rect(int x, int y, int w, int h) {
  SDL_Rect result;
  result.x = x;// >= 0 ? x : 0;
  result.y = y;// >= 0 ? y : 0;
  result.w = w;
  result.h = h;
  return result;
}

int main() {
  if (!init()) {
    return 1;
  }
  bool running = true;
  int color = 0;

  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
      switch (e.type) {
        case SDL_QUIT: {
          running = false;
          break;
        }
        case SDL_MOUSEBUTTONUP: {
          SDL_MouseButtonEvent* event = (SDL_MouseButtonEvent*) &e;

          if (event->button != SDL_BUTTON_LEFT) {
            break;
          }

          SDL_Rect box = rect(event->x - 5, event->y - 5, 10, 10);
          Uint32 fcolor= SDL_MapRGB(surface->format, (color & 0xff0000) >> 16, (color & 0xff00) >> 8, color & 0xff);
          SDL_FillRect(surface, &box, fcolor);

          SDL_UpdateWindowSurface(window);
          color += 0x40;
          if (color & 0x100) {
            color += 0x4000;
          }
          if (color & 0x10000) {
            color += 0x400000;
          }
          printf("color %x\n", color);
          break;
        }
      }
    }
  }
  return 0;
}
