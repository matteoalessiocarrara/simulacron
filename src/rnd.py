#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>

import random
from sys import argv, stderr

def overlap(tmp, axis):
	for p in axis:
		if abs(tmp - p) < 2:
			return True
	return False

uw = float(argv[1])
atoms = int(argv[2])

x = []
y = []

if atoms > (((uw -1) / 3) ** 2):
	stderr.write("Warning: atoms is greater than (uw - 1) / 3 (%f), this can block the program\n" % ((uw -1) / 3))

for i in range(atoms):
	while True:
		tmpx = random.choice(range(1, int(uw)))
		tmpy = random.choice(range(1, int(uw)))
		if not (overlap(tmpx, x) and overlap(tmpy, y)):
			x.append(tmpx)
			y.append(tmpy)
			stderr.write("%d\n" % len(x))
			break

print(atoms)
for i in range (atoms):
	print(x[i], y[i], random.choice(range(-20, 20)), random.choice(range(-20, 20)))


