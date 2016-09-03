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


# include <stdbool.h>

# define AXES 2

enum Axis
{
	X = 0,
	Y = 1
};


enum Color
{
	R = 0,
	G = 1,
	B = 2
};

typedef struct _atom
{
	float rad;
	float pos[AXES]; // xy
	float sp[AXES]; // xy
	float color[3]; // rgb, percentuale (max 1.0, min 0.0)
} atom;


typedef struct _universe
{
	float max[AXES]; // xy
	atom *a;
	unsigned an;
} universe;


typedef struct _mrc
{
	bool found;
	float at;
	unsigned a1; // atom index
	unsigned a2;
	short axis;
} mrc;



float posAfterNoMax(float s, float pos, float speed);
float posAfter(float s, float pos, float sp, float posMax);
float atomDist(float pos1, float pos2, float rad1, float rad2);
float cTime(float pos1, float pos2, float rad1, float rad2, float sp1, float sp2);
bool collide(float pos1, float pos2, float rad1, float rad2, float sp1, float sp2, float maxS);
mrc findMRC(const atom *av, unsigned an, float s);
atom * calcFutureNoColl(const atom *iav, unsigned an, float s, float axMax[AXES]);
atom * calcFuture(const atom *iav, unsigned an, float s, float axMax[AXES]);
float elCollV1(float v1, float v2, float m1, float m2); // elastic collision
float elCollV2(float v1, float v2, float m1, float m2);
