#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright 2017 Matteo Alessio Carrara <sw.matteoac@gmail.com>

import random
from sys import argv, stderr

def genpos(axis):
	try:
		tmp = None
		while True:
			tmp = random.choice(range(1, int(uw)))
			retry = False
			for p in axis:
				if abs(tmp - p) < 2:
					retry = True
					break
			if not retry:
				break
		return tmp
	except KeyboardInterrupt:
		axis.sort()
		exit(axis)

uw = float(argv[1])
atoms = int(argv[2])

x = []
y = []

if atoms > ((uw -1) / 3):
	stderr.write("Warning: atoms is greater than (uw - 1) / 3 (%f), this can block the program\n" % ((uw -1) / 3))

for i in range(atoms):
	x.append(genpos(x))
	y.append(genpos(y))

print(atoms)
for i in range (atoms):
	print(x[i], y[i], random.choice(range(-20, 20)), random.choice(range(-20, 20)))


