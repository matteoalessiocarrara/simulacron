// Copyright 2016 - 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>


# include <assert.h>
# include <math.h>

# include "physics.h"


int main() {
	assert(posAfter(10, 0, 1, 15) == 10);
	assert(posAfter(16, 0, 1, 15) == 1);
	assert(posAfter(10, 0, -1, 15) == 5);

	assert(posAfterNoMax(10, 0, -1) == -10);

	assert(elCollV1(4, -6, 3, 5) == -8.5);
	assert(elCollV2(4, -6, 3, 5) == 1.5);

	return 0;
}


