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


class Atom:
	def __init__(self, radius = 0, x = 0, y = 0, speed_x = 0, speed_y = 0):
		"""
		radius = m
		x = m
		y = m
		speed_x = m/s
		speed_y = m/s
		"""
		self.radius = radius
		self.x = x
		self.y = y
		self.speed_x = speed_x
		self.speed_y = speed_y


class Universe:
	def __init__(self, atoms = [], max_x = 0, max_y = 0):
		"""
		max_x = m
		max_y = m
		"""
		self.atoms = atoms
		self.max_x = max_x
		self.max_y = max_y


def calc_collisions(universe):
	pass
	

def calc_future(universe, offset_s):
	"""Calcola il futuro dopo `after_s` secondi"""
	
	for i in range(len(universe.atoms)):
		atom = universe.atoms[i]
		
		atom.x += (atom.speed_x * offset_s)
		atom.y += (atom.speed_y * offset_s)
		
		if (atom.x > universe.max_x):
			atom.x = atom.x % universe.max_x - 1
		if (atom.y > universe.max_y):
			atom.y = atom.y % universe.max_y - 1
		
		universe.atoms[i] = atom
	
	return universe
		
	
	
