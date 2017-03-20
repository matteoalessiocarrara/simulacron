// Copyright 2016 - 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>

# include <stdbool.h>

# define AXES 2
# define ATOM_RADIUS 1

typedef struct {
	float pos[AXES];
	float sp[AXES];
} s_atom;

typedef struct {
	float circ;
	s_atom *a;
	unsigned an;
} s_universe;

typedef struct {
	float a;
	float b;
} s_fpair;

void futureWithCollisions(s_atom *a, unsigned an, float s, float u_circ);
void linearFuture(s_atom *a, unsigned an, float s, float u_circ);
float elCollV2(float sp1, float sp2, float m1, float m2);
float elCollV1(float sp1, float sp2, float m1, float m2);
bool colliding(float pos1, float pos2, float u_circ);
bool atomCollide(float sp1, float sp2, float pos1, float pos2, float u_circ);
float atomCTime(float pos1, float pos2, float sp1, float sp2, float u_circ);
float pointCTime(float pos1, float pos2, float sp1, float sp2, float u_circ);
s_fpair atomDist(float pos1, float pos2, float u_circ);
float posAfterNoMax(float s, float start, float speed);
float posAfter(float s, float start, float speed, float axisMax);













