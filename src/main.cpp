/*
 * Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

# include <SDL/SDL.h>
# include <SDL/SDL_gfxPrimitives.h>
# include <SDL/SDL_framerate.h>

# include "physics.hpp"


# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define FPS 60

// In metri
# define UNIVERSE_WIDTH 64
# define UNIVERSE_HEIGHT 48
# define PX_M 10 // Quanti pixel usare per rappresentare un metro
# define F_S (1./FPS) // Quanti secondi della simulazione corrispondono ad ogni frame

# define M2PX(m) ((m) * PX_M) // Converte metri in pixel


int main()
{
	universe u = {.max = {UNIVERSE_WIDTH, UNIVERSE_HEIGHT}};
	atom a[2] = {
		{
			.pos = {30, 20},
			.sp = {10, 0},
		},
		{
			.pos = {50, 20},
			.sp = {-10, 0},
		}
	};

	u.a.push_back(a[0]);
	u.a.push_back(a[1]);


	SDL_Surface *screen;
	SDL_Event event;
	FPSmanager fpsManager;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_initFramerate(&fpsManager);
	SDL_WM_SetCaption("Simulacron v1", "Simulacron v1");

	screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_setFramerate(&fpsManager, FPS);

	while (true)
	{
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				goto quit;
			}
		}

		SDL_FillRect(screen, NULL, 0x000000);

		for (const atom b: u.a)
		{
			filledCircleRGBA(screen, M2PX(b.pos[X]), M2PX(b.pos[Y]), M2PX(ATOM_RADIUS), 0xff, 0, 0, 0xff);
		}

		SDL_framerateDelay(&fpsManager);
		SDL_Flip(screen);

		calcFuture(u.a, F_S, u.max);
	}

	quit: SDL_Quit();
	return 0;
}
