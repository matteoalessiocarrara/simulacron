// Copyright 2016 - 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <malloc.h>
# include <stdbool.h>
# include <stdint.h>

# include "physics.h"

inline float posAfter(float s, float start, float speed, float axisMax) {
	register const float p = posAfterNoMax(s, start, speed);
	return p > 0? fmod(p, axisMax) : axisMax - (fmod(fabs(p), axisMax));
}

inline float posAfterNoMax(float s, float start, float speed) {
	return start + speed * s;
}

s_fpair atomDist(float pos1, float pos2, float u_circ) {
	register const float d1 = fabs(pos2 - pos1), d2 = u_circ - d1;
	s_fpair r = (pos2 > pos1)? (s_fpair){d1, d2} : (s_fpair) {d2, d1};
	r.a = (r.a > (ATOM_RADIUS * 2))? r.a - ATOM_RADIUS * 2 : 0;
	r.b = (r.b > (ATOM_RADIUS * 2))? r.b - ATOM_RADIUS * 2 : 0;
	return r;
}

inline bool colliding(float pos1, float pos2, float u_circ) {
	register const s_fpair d = atomDist(pos1, pos2, u_circ);
	return ((d.a == 0) || (d.b == 0));
}

// -1 = never collide
inline float atomCTime(float pos1, float pos2, float sp1, float sp2, float u_circ) {
	if (sp2 == sp1) return colliding(pos1, pos2, u_circ)? 0 : -1;
	register const s_fpair d = atomDist(pos1, pos2, u_circ);
	return  fabs(((sp2 - sp1) < 0? d.a : d.b) / (sp2 - sp1));
}

inline bool atomCollide(float sp1, float sp2, float pos1, float pos2, float u_circ) {
	return (sp1 != sp2) || colliding(pos1, pos2, u_circ);
}

inline float elCollV1(float sp1, float sp2, float m1, float m2) {
	return ((sp1 * (m1 - m2)) + (2 * m2 * sp2)) / (m1 + m2);
}

inline float elCollV2(float sp1, float sp2, float m1, float m2) {
	return ((sp2 * (m2 - m1)) + (2 * m1 * sp1)) / (m1 + m2);
}

void linearFuture(s_atom *a, unsigned an, float s, float u_circ) {
	while(an--)
		for (register uint8_t axis = 0; axis < AXES; axis++)
			a[an].pos[axis] = posAfter(s, a[an].pos[axis], a[an].sp[axis], u_circ);
}

void futureWithCollisions(s_atom *a, unsigned an, float s, float u_circ) {
	struct s_mrc {
		bool found;
		float time;
		unsigned aindex[2];
	} mrc = {.found = false};

	// Finds the most recent collision
	// Checks whether each atom collides with one of the following
	for(unsigned a1 = 0; a1 < (an - 1); a1++) {
		for(unsigned a2 = a1 + 1; a2 < an; a2++) {
			// There must be a collision on all axes
			bool c = true;
			for(register uint8_t axis = 0; axis < AXES; axis++)
				c &= atomCollide(a[a1].sp[axis], a[a2].sp[axis], a[a1].pos[axis], a[a2].pos[axis], u_circ);

			// ... at the same time
			float time;
			if (c) {
				time = atomCTime(a[a1].pos[0], a[a2].pos[0], a[a1].sp[0], a[a2].sp[0], u_circ);
				float time1;
				for(register uint8_t axis = 1; axis < AXES; axis++) {
					time1 = atomCTime(a[a1].pos[axis], a[a2].pos[axis], a[a1].sp[axis], a[a2].sp[axis], u_circ);
					c &= ((time1 == time) || (time1 == 0));
				}
			}

			// Now let's see if it is the most recent
			if (c)
				if ((!mrc.found) || (time < mrc.time))
					if (time < s)
						mrc = (struct s_mrc) {.found = true, .time = time, .aindex = {a1, a2}};
		}
	}

	if (mrc.found) {
		// Calculate the future linearly up to the collision
		linearFuture(a, an, mrc.time, u_circ);

		// Calculate the collision
		s_atom *a1 = &a[mrc.aindex[0]], *a2 = &a[mrc.aindex[1]], tmp = *a1;
		for(register uint8_t axis = 0; axis < AXES; axis++) {
			a1->sp[axis] = elCollV1(a1->sp[axis], a2->sp[axis], 1, 1);
			a2->sp[axis] = elCollV2(tmp.sp[axis], a2->sp[axis], 1, 1);
		}

		// Continue to look for collisions
		futureWithCollisions(a, an, s - mrc.time, u_circ);
	}
	else linearFuture(a, an, s, u_circ);
}
