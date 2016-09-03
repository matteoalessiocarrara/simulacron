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

# include <math.h>
# include <string.h>
# include <malloc.h>
# include <stdbool.h>
# include <stdlib.h>

# include "physics.h"


inline float
posAfter(float s, float pos, float sp, float posMax)
{
	float p = posAfterNoMax(s, pos, sp);
	return p > 0? fmod(p, posMax) : posMax - (fmod(fabs(p), posMax));
}


inline float
posAfterNoMax(float s, float pos, float speed)
{
	return pos + (speed * s);
}


inline float
atomDist(float pos1, float pos2, float rad1, float rad2)
{
	float d = fabs(pos1 - pos2) - (rad1 + rad2);
	return (pos1 - pos2) > 0? d : -d;
}


float
cTime(float pos1, float pos2, float rad1, float rad2, float sp1, float sp2)
{
	float d = fabs(atomDist(pos1, pos2, rad1, rad2));

	if (sp1 != 0)
		return ((fabs(sp1)/(fabs(sp1) + fabs(sp2))) * d) / fabs(sp1);
	else if (sp2 != 0)
		return ((fabs(sp2)/(fabs(sp1) + fabs(sp2))) * d) / fabs(sp2);
	else
		return -1; // err
}


bool
collide(float pos1, float pos2, float rad1, float rad2, float sp1, float sp2, float maxS)
{
	float currDist = atomDist(pos1, pos2, rad1, rad2);
	float futureDist = atomDist(
				posAfterNoMax(maxS, pos1, sp1),
				posAfterNoMax(maxS, pos2, sp2),
				rad1, rad2
				);

	if (
			((currDist < 0 ) && (futureDist >= 0)) ||
			((currDist > 0 ) && (futureDist <= 0))
		)
		return true;
	else
		return false;
}


inline float
elCollV1(float v1, float v2, float m1, float m2)
{
	return ((v1 * (m1 - m2)) + (2 * m2 * v2)) / (m1 + m2);
}


inline float
elCollV2(float v1, float v2, float m1, float m2)
{
	return ((v2 * (m2 - m1)) + (2 * m1 * v1)) / (m1 + m2);
}


mrc
findMRC(const atom *av, unsigned an, float s)
{
	mrc r = {.found = false, .at = 0};

	for(unsigned i = 0; i < (an - 1); i++)
	{
		for(unsigned j = i + 1; j < an; j++)
		{
			for(short axis = 0; axis < AXES; axis++)
			{
				if(collide(av[i].pos[axis], av[j].pos[axis], av[i].rad, av[j].rad,
						   av[i].sp[axis], av[j].sp[axis], s))
				{
					float ct = cTime(av[i].pos[axis], av[j].pos[axis], av[i].rad,
										av[j].rad, av[i].sp[axis], av[j].sp[axis]);
					if((ct < r.at) || (!r.found))
					{
						r.found = true;
						r.a1 = i;
						r.a2 = j;
						r.axis = axis;
						r.at = ct;
					}
				}
			}
		}
	}

	return r;
}


atom *
calcFutureNoColl(const atom *iav, unsigned an, float s, float axMax[AXES])
{
	atom *oav = malloc(sizeof(atom) * an);
	memcpy(oav, iav, sizeof(atom) * an);

	for (unsigned i = 0; i < an; i++)
		for (short j = 0; j < AXES; j++)
			oav[i].pos[j] = posAfter(s, oav[i].pos[j], oav[i].sp[j], axMax[j]);

	return oav;
}


atom *
calcFuture(const atom *ia, unsigned an, float s, float axMax[AXES])
{
	atom *oa = malloc(sizeof(atom) * an);
	memcpy(oa, ia, sizeof(atom) * an);


	for(mrc c; (c = findMRC(ia, an, s)).found;)
	{
		oa = calcFutureNoColl(oa, an, c.at, axMax);

		if (s > 0)
			s -= c.at;

		// TODO Massa
		float tmp = oa[c.a1].sp[c.axis];
		oa[c.a1].sp[c.axis] = elCollV1(oa[c.a1].sp[c.axis], oa[c.a2].sp[c.axis],
										oa[c.a1].rad, oa[c.a2].rad);
		oa[c.a2].sp[c.axis] = elCollV2(tmp, oa[c.a2].sp[c.axis], oa[c.a1].rad, oa[c.a2].rad);
	}


	return s > 0? calcFutureNoColl(oa, an, s, axMax) : oa;
}



