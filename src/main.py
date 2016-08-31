#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#  Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.

import pygame
from physics import *


screen_width=700
screen_height=400
fps = 60
pixel_m = 10 # quanti pixel usare per rappresentare un metro


pygame.init()
screen = pygame.display.set_mode([screen_width, screen_height])
clock = pygame.time.Clock()
u = Universe(
	[
		Atom(radius=1, x=30, y=20, speed_x=10, speed_y=0),
		Atom(radius=1, x=41, y=16, speed_x=1, speed_y=8),
		Atom(radius=1, x=23, y=23, speed_x=35, speed_y=27),
		Atom(radius=1, x=56, y=31, speed_x=8, speed_y=41),
		Atom(radius=1, x=62, y=25, speed_x=23, speed_y=36)
	],
	max_x=70, max_y=40)

# WARNING I valori in metri devono essere moltiplicati per pixel_m prima di essere visualizzati
while True:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			exit(0)

	screen.fill((0, 0, 0))
	
	for atom in u.atoms:
		pygame.draw.circle(screen, (0xff, 00, 00), (int(atom.x) * pixel_m, int(atom.y) * pixel_m), atom.radius * pixel_m)
	
	u = calc_future(u, 1./fps)

	pygame.display.flip()
	clock.tick(fps)
