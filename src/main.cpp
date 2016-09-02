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

# include <array>
# include <ctime>
# include <iostream>

# include <SDL/SDL.h>
# include <SDL/SDL_gfxPrimitives.h>
# include <SDL/SDL_framerate.h>

# include "physics.h"


using std::array;
using std::time_t;


# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define FPS 60

# define UNIVERSE_WIDTH 64
# define UNIVERSE_HEIGHT 48
# define PX_M 10 // Quanti pixel usare per rappresentare un metro
# define F_S (1./FPS) // Quanti secondi della simulazione corrispondono ad ogni frame

# define M2PX(m) ((m) * PX_M) // Converte metri in pixel


int main()
{
	Universe u(
				{UNIVERSE_WIDTH, UNIVERSE_HEIGHT},
				{
					Atom(1, {5, 20}, {-10, 0}, {1, 0, 0}),
					Atom(1, {50, 20}, {0, 0}, {0, 1, 0}),
					Atom(1, {60, 20}, {-5, 0}, {0, 1, 1}),
					Atom(1, {10, 20}, {10, 0}, {1, 1, 0})
				}
				);

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

		for(Atom &a: u.atoms)
		{
			filledCircleRGBA(screen, M2PX(a.pos[0]), M2PX(a.pos[1]), M2PX(a.radius), a.color[0] * 0xff, a.color[1] * 0xff, a.color[2] * 0xff, 0xff);
		}

		SDL_framerateDelay(&fpsManager);
		SDL_Flip(screen);

		u = u.calcFuture(F_S);
	}

	quit: SDL_Quit();
	return 0;
}
