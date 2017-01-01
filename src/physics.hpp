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
# include <string>
# include <utility>
# include <stdexcept>

# define AXES 2
# define ATOM_RADIUS 1
# define ATOM_MASS 1


using std::vector;
using std::to_string;
using std::pair;


enum Axis
{
	X = 0,
	Y = 1
};


typedef struct _atom
{
	float pos[AXES];
	float sp[AXES];
} atom;


typedef struct _universe
{
	float max[AXES];
	vector<atom> a;
} universe;


typedef struct _mrc
{
	bool found;
	float time;
	pair<size_t, size_t> index;
} mrc;


float posAfterNoMax(const float s, const float start, const float speed);
float posAfter(const float s, const float start, const float speed, const float axisMax);
float atomDist(const float pos1, const float pos2);
vector<atom> futureWithCollisions(const vector<atom> &iav, const float s, const float axisMax[AXES]);

/*float cTime(float pos1, float pos2, float rad1, float rad2, float sp1, float sp2);
bool collide(float pos1, float pos2, float rad1, float rad2, float sp1, float sp2, float maxS);
mrc findMRC(const atom *av, unsigned an, float s);
atom * calcFutureNoColl(const atom *iav, unsigned an, float s, float axMax[AXES]);
atom * calcFuture(const atom *iav, unsigned an, float s, float axMax[AXES]);
float elCollV1(float v1, float v2, float m1, float m2); // elastic collision
float elCollV2(float v1, float v2, float m1, float m2);
*/

class AtomOverlappingException: public std::invalid_argument
{
	public:
		AtomOverlappingException(float pos1, float pos2):
			std::invalid_argument(to_string(pos1) + "," + to_string(pos2) + ",") {}
};
class PointNeverCollideException: public std::runtime_error
{
	public:
		PointNeverCollideException(const std::string &msg): std::runtime_error(msg) {}
};
class InvalidCollisionException: public std::invalid_argument
{
	public:
		InvalidCollisionException(const std::string &msg): std::invalid_argument(msg) {}
};












