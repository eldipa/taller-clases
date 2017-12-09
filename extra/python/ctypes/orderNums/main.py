#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from radix import cRadix, pyRadix
import sys
import time

'''
El archivo randomfile posee lineas con 4 dígitos cada una
Se ordenaran con distintos algoritmos y se comparará la eficiencia
de los mismos
'''

if len(sys.argv) < 2:
    print("Debe proveer un nombre de archivo")
    exit(1)

filepath = sys.argv[1]

# Descomentar para correr con kernprof
#@profile
def runTest():
    # Leo binario para mayor velocidad al interactuar con C
    with open(filepath, "rb" ) as randomfile: 
        print ("Leyendo números")
        nums = randomfile.readlines()
    print("Ordenando con python")
    #pySorted = pyRadix.sort(nums)
    print("Ordenando con C")
    cSorted = cRadix.sort(nums)
    print (cSorted)
    print("Ordenando nativo")
    #pythonNativeSorted = list(nums)
    
runTest()
