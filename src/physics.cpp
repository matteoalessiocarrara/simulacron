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

# include <cmath>
# include <iostream>
# include <cstdlib>
# include <malloc.h>
# include <vector>

# include "physics.hpp"


using std::vector;





inline float
posAfter(const float s, const float start, const float speed, const float axisMax)
{
	const register float p = posAfterNoMax(s, start, speed);
	return p > 0? fmod(p, axisMax) : axisMax - (fmod(fabs(p), axisMax));
}


inline float
posAfterNoMax(const float s, const float start, const float speed)
{
	return start + (speed * s);
}


float
atomDist(const float pos1, const float pos2)
{
	if (fabs(pos1 - pos2) < (ATOM_RADIUS * 2))
		//throw AtomOverlappingException(pos1, pos2);
		return 0;

	const register float d = fabs(pos1 - pos2) - (ATOM_RADIUS * 2);
	return (pos1 - pos2) > 0? d : -d;
}


// WARNING Attenzione al calcolo della posizione con posAfter
inline bool
collide(const float start1, const float end1, const float start2, const float end2)
{
	const float currDist = atomDist(start1, start2), futureDist = atomDist(end1, end2);

	//if ((currDist == 0) and (futureDist == 0))
		//throw InvalidCollisionException("");
	if (currDist == 0)
		return (end1 > end2)? (futureDist <= 0) : (futureDist >= 0);
	else
		return (currDist > 0)? (currDist + futureDist) <= currDist : (currDist + futureDist) >= currDist;
}


float
pointCTime(const float dist, const float sp1, const float sp2)
{
	if (dist == 0)
		return 0;
	if ((sp1 == sp2) || (! (sp1 || sp2)))
		throw PointNeverCollideException("");
	if (sp1 != 0)
		return ((fabs(sp1) / (fabs(sp1) + fabs(sp2))) * dist) / fabs(sp1);
	else // sp2 != 0
		return ((fabs(sp2) / (fabs(sp1) + fabs(sp2))) * dist) / fabs(sp2);
}


// Il momento in cui due atomi si troveranno affiancati su un asse (distanza 0)
inline float
atomCTime(const float pos1, const float pos2, const float sp1, const float sp2)
{
	try
	{
		return pointCTime(fabs(atomDist(pos1, pos2)), sp1, sp2);
	}
	catch(AtomOverlappingException &e)
	{
		return 0;
	}
}


// Collisione elastica, velocità risultante per il primo e secondo oggetto


inline float
elCollV1(float sp1, float sp2, float m1, float m2)
{
	return ((sp1 * (m1 - m2)) + (2 * m2 * sp2)) / (m1 + m2);
}


inline float
elCollV2(float sp1, float sp2, float m1, float m2)
{
	return ((sp2 * (m2 - m1)) + (2 * m1 * sp1)) / (m1 + m2);
}


/*

// Il momento in cui due atomi sono affiancati, i momenti successivi saranno in
// sovrapposizione
# define overlapStart cTime


// Tutti gli istanti successivi non saranno sovrapposti
inline float
overlapEnd(float pos1, float pos2, float rad1, float rad2, float sp1, float sp2)
{
	return overlapStart(pos1, pos2, rad1, rad2, sp1, sp2) + pointCTime(fabs(pos1 - pos2) + (rad1 + rad2), sp1, sp2);
}


inline bool
overlap(float pos1, float pos2, float rad1, float rad2, float sp1, float sp2, float maxS)
{
	return cTime(pos1, pos2, rad1, rad2, sp1, sp2) < maxS;
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
calcFuture(const atom *ia, unsigned an, float s, float axMax[AXES])
{
	atom *oa = (atom*) malloc(sizeof(atom) * an);
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
*/


inline vector<atom>
linearFuture(const vector<atom> &iav, const float s, const float axisMax[AXES])
{
	vector<atom> oav = iav;

	for (atom &a: oav)
		for (short axis = 0; axis < AXES; axis++)
			a.pos[axis] = posAfter(s, a.pos[axis], a.sp[axis], axisMax[axis]);

	return oav;
}


// FIXME Il calcolo del futuro non funziona se si superano i limiti del piano
vector<atom>
futureWithCollisions(const vector<atom> &iav, const float s, const float axisMax[AXES])
{
	vector<atom> oav = linearFuture(iav, s, axisMax);
	mrc m = {.found = false};

	// Troviamo la collisione più recente
	// Controlla se ogni atomo collide con uno dei successivi
	for(size_t a1 = 0; a1 < (iav.size() - 1); a1++)
	{
		for(size_t a2 = a1 + 1; a2 < iav.size(); a2++)
		{
			// Perché collida deve avere un punto in comune su tutti gli assi
			bool c = true;
			for(short axis = 0; axis < AXES; axis++)
				c &= collide(iav[a1].pos[axis], oav[a1].pos[axis], iav[a2].pos[axis], oav[a2].pos[axis]);

			// ... nello steso momento
			float time;
			if (c)
			{
				time = atomCTime(iav[a1].pos[0], iav[a2].pos[0], iav[a1].sp[0], iav[a2].sp[0]);
				for(short axis = 1; axis < AXES; axis++)
					c &= (atomCTime(iav[a1].pos[axis], iav[a2].pos[axis], iav[a1].sp[axis], iav[a2].sp[axis]) == time);
			}

			// Vediamo ora se è quella più recente
			if (c)
			{
				if ((not m.found) || ((time < m.time) && (time < s)))
				{
					m.found = true;
					m.time = time;
					m.index = {a1, a2};
				}
			}
		}
	}

	if (m.found)
	{
		// Calcoliamo il futuro in modo lineare fino alla collisione
		oav = linearFuture(iav, m.time, axisMax);

		// Calcoliamo la collisione
		atom &a1 = oav[m.index.first];
		atom &a2 = oav[m.index.second];
		atom tmp = a1;
		for(short axis = 0; axis < AXES; axis++)
		{
			a1.sp[axis] = elCollV1(a1.sp[axis], a2.sp[axis], ATOM_MASS, ATOM_MASS);
			a2.sp[axis] = elCollV2(tmp.sp[axis], a2.sp[axis], ATOM_MASS, ATOM_MASS);
		}

		// Proseguiamo con la ricerca di collisioni

		oav = futureWithCollisions(oav, s - m.time, axisMax);
	}

	return oav;
}
