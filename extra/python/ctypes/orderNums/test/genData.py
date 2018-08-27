#!/usr/bin/env python3

import sys
from random import randint

if len(sys.argv) < 2:
    print("Debe proveer un nombre de archivo")
    exit(1)

filepath = sys.argv[1]

with open(filepath, "w" ) as randomfile: 

    numsRandom = int(input('Ingrese cantidad de números aleatorios: '))

    for i in range(numsRandom):
        line = str(randint(0, 9999)).zfill(4)
        randomfile.write(line)
        randomfile.write('\n')
