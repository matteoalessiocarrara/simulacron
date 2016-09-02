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

# include <stdexcept>
# include <array>
# include <cmath>


# include "physics.h"


using std::array;
using std::fmod;
using std::abs;




Atom::Atom(float _radius, array<float, 2> _pos, array<float, 2> _speed, array<float, 3> _color)
{
	radius = _radius;
	pos = _pos;
	speed = _speed;
	color = _color;

}


float Atom::axisAfter(float s, short i, float axisMax)
{
	float p = pos[i] + (speed[i] * s);
	return p < 0? axisMax - (fmod(abs(p), axisMax)) : fmod(p, axisMax);
}


float Atom::axisAfterNoMod(float s, short i)
{
	return pos[i] + (speed[i] * s);
}



float Atom::dist(Atom a, Atom b, short i)
{
	return dist(a, b, a.pos[i], b.pos[i]);
}


float Atom::dist(Atom a, Atom b, float aX, float bX)
{
	float d = abs(aX - bX) - (a.radius + b.radius);
	return (aX - bX) > 0? d : -d;
}


float Atom::collisionTime(Atom a, Atom b, short i)
{
	float v1 = abs(a.speed[i]), v2 = abs(b.speed[i]), d = abs(dist(a, b, i));
	
	if (v1 != 0)
		return ((v1/(v1 + v2)) * d) / v1;
	else if(v2 != 0)
		return ((v2/(v1 + v2)) * d) / v2;
	else throw std::runtime_error("La collisione non avverrà mai");


}


bool Atom::collide(Atom a, Atom b, short i, float maxS, float axisMax)
{
	float currDist = dist(a, b, i);
	float futureDist = dist(a, b, a.axisAfterNoMod(maxS, i), b.axisAfterNoMod(maxS, i));

	return (
				((currDist < 0 ) and (futureDist > 0)) or
				((currDist > 0 ) and (futureDist < 0))
			);
}


Universe::Universe(array<float, 2> _max, vector<Atom> _atoms)
{
	max = _max;
	atoms = _atoms;
}


struct Universe::mrc
Universe::__mostRecentCollision(Universe u, float maxS)
{
	struct mrc m;
	m.found = false;
	m.after = 0;

	for(vector<Atom>::iterator a1 = u.atoms.begin(); a1 < (u.atoms.end() - 1); a1++)
	{
		for(vector<Atom>::iterator a2 = a1 + 1; a2 < u.atoms.end(); a2++)
		{
			for(short axis = 0; axis < 2; axis++)
			{
				if(Atom::collide(*a1, *a2, axis, maxS, u.max[axis]))
				{
					if((Atom::collisionTime(*a1, *a2, axis) < m.after) or (not m.found))
					{
						m.found = true;
						m.atomIndex1 = a1 - u.atoms.begin();
						m.atomIndex2 = a2 - u.atoms.begin();
						m.axis = axis;
						m.after = Atom::collisionTime(*a1, *a2, axis);
					}
				}
			}
		}
	}

	return m;
}


Universe
Universe::__calcFutureWithoutCollisions(Universe u, float s)
{
	for(Atom &a: u.atoms)
	{
		for(unsigned short i = 0; i < a.pos.size(); i++)
		{
			a.pos[i] = a.axisAfter(s, i, u.max[i]);
		}
	}

	return u;
}


Universe
Universe::calcFuture(float s)
{
	Universe r = *this;


	for(struct mrc m; (m = __mostRecentCollision(r, s)).found;)
	{
		r = __calcFutureWithoutCollisions(r, m.after);

		if (s)
			s -= m.after;

		Atom *a1 = r.atoms.data() + m.atomIndex1, *a2 = r.atoms.data() + m.atomIndex2;
		float tmp = a1->speed[m.axis];
		// TODO Massa
		a1->speed[m.axis] = (((a2->radius - a1->radius) * a1->speed[m.axis]) + (2 * a2->radius * a2->speed[m.axis])) / (a1->radius + a2->radius);
		a2->speed[m.axis] = ((2 * a1->radius * tmp) + ((a2->radius - a1->radius) * a2->speed[m.axis])) / (a1->radius + a2->radius);
	}


	return s? __calcFutureWithoutCollisions(r, s) : r;
}








