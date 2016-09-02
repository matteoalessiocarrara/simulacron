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

# include <vector>
# include <array>


using std::vector;
using std::array;


class Atom
{
	public:
		Atom(float _radius = 1, array<float, 2> _pos = {0, 0}, array<float, 2> _speed = {0, 0},
				array<float, 3> _color = {1, 0, 0});

		float radius;
		array<float, 2> pos; // x y
		array<float, 2> speed; // x y
		array<float, 3> color; // rgb, percentuale (max 1.0, min 0.0)

		float axisAfter(float s, short i, float axisMax);
		// Consente valori negativi per gli assi
		float axisAfterNoMod(float s, short i);

		static float dist(Atom a, Atom b, short i);
		static float dist(Atom a, Atom b, float aX, float bX); // aX e bX sono la posizione di a e b
		// Quando due atomi saranno a contatto
		// WARNING prima di usare questa funzione assicurarsi che si scontrino
		static float collisionTime(Atom a, Atom b, short i);
		static bool collide(Atom a, Atom b, short i, float maxS, float axisMax);
};


class Universe
{
	public:
		Universe(array<float, 2> _max, vector<Atom> _atoms = {});
		Universe calcFuture(float s);

		vector<Atom> atoms;
		array<float, 2> max; // x y

	private:
		struct mrc
		{
			bool found;
			float after;
			unsigned atomIndex1;
			unsigned atomIndex2;
			short axis;
		};

		static Universe __calcFutureWithoutCollisions(Universe u, float s);
		static struct mrc __mostRecentCollision(Universe u, float maxS);



};
