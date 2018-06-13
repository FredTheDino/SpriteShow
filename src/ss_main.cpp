#include <SDL2/SDL.h>
#include <math.h>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 400

// Types
typedef char	s8;
typedef short	s16;
typedef int		s32;
typedef long	s64;

typedef unsigned char	u8;
typedef unsigned short	u16;
typedef unsigned int	u32;
typedef unsigned long	u64;

typedef float f32;
typedef double f64;

bool running;

#ifdef WINDOWS
#include <windows.h>
int WinMain(
		HINSTANCE instance,
		HINSTANCE prevInstance,
		LPSTR cmdLine,
		int cmdShow)
#else
int main(s32 narg, char *varg[])
#endif
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow(
			"Hello!",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH,
			WINDOW_HEIGHT,
			0);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);

	SDL_ShowWindow(window);
	running = true;
	u64 current_tick, last_tick = SDL_GetTicks();
	f32 delta;
	f32 t;
	bool going_up = false;
	while (running)
	{
		current_tick = SDL_GetTicks();
		delta = (current_tick - last_tick) / 1000.0f;
		last_tick = current_tick;
		t = (current_tick / 1000.0f);
		
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
		SDL_RenderFillRect(renderer, &rect);

		int y_offset = sin(t) * 100;
		int x_offset = cos(t) * 100;
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		rect = {(WINDOW_WIDTH - 100) / 2 - x_offset, (WINDOW_HEIGHT - 100) / 2 - y_offset, 100, 100};
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return 0;
}

