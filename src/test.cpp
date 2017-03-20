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

# include <assert.h>
# include <math.h>

# include "physics.hpp"


int main()
{
	assert(posAfter(10, 0, 1, 15) == 10);
	assert(posAfter(16, 0, 1, 15) == 1);
	assert(posAfter(10, 0, -1, 15) == 5);

	assert(posAfterNoMax(10, 0, -1) == -10);
/*
	assert(fabs(atomDist(0, 10)) == 6);

	assert(cTime(0, 10, 1, 1, 2, -2) == 2);

	assert(collide(0, 10, 1, 1, 2, -2, 3));
	assert(!collide(0, 10, 1, 1, 2, -2, 1));

	assert(elCollV1(4, -6, 3, 5) == -8.5);
	assert(elCollV2(4, -6, 3, 5) == 1.5);
*/
	return 0;
}


