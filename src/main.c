// Copyright 2016 - 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>

# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <errno.h>

# include <SDL/SDL.h>
# include <SDL/SDL_gfxPrimitives.h>
# include <SDL/SDL_framerate.h>

# include "physics.h"

# define U_CIRC 64 // meters
# define PX_M 10 // pixels used to represent a meter
# define WWIDTH U_CIRC * PX_M
# define WHEIGHT U_CIRC * PX_M
# define FPS 60
# define F_S (1./FPS) // seconds of the simulation for each frame
# define M2PX(m) ((m) * PX_M) // meters to pixels


int main() {
	SDL_Surface *screen;
	SDL_Event event;
	FPSmanager fpsManager;
	s_universe u = {.circ = U_CIRC, .a = NULL, .an = 0};
	s_atom a[2] = {
		{
			.pos = {40, 30},
			.sp = {10, 10},
		},
		{
			.pos = {50, 35},
			.sp = {-10, 0},
		},
	};

	if ((u.a = malloc(sizeof(s_atom) * 2)) == NULL) {perror(NULL); exit(EXIT_FAILURE);}
	memcpy(u.a, a, sizeof(s_atom) *2);
	u.an = 2;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_initFramerate(&fpsManager);
	SDL_WM_SetCaption("Simulacron v1", "Simulacron v1");
	screen = SDL_SetVideoMode(WWIDTH, WHEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_setFramerate(&fpsManager, FPS);

	for(;;) {
		if (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				goto quit;

		SDL_FillRect(screen, NULL, 0x000000);
		for (register unsigned i = 0; i < u.an; i++)
			filledCircleRGBA(screen, M2PX(u.a[i].pos[0]), M2PX(u.a[i].pos[1]), M2PX(ATOM_RADIUS), 0xff, 0, 0, 0xff);

		SDL_framerateDelay(&fpsManager);
		SDL_Flip(screen);
		futureWithCollisions(u.a, u.an, F_S, u.circ);
	}

	quit: SDL_Quit();
	return 0;
}
