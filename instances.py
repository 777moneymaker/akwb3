#!/usr/bin/python3
'''
Script for making instances for restriction mapping.
Just change the rand_map list to any map you want, and script will make an instance for you.
'''
import random

VALID_SIZES = [i for i in range(1, 120) for n in range(1, 120) if i == (n+1)*(n+2) // 2]

rand_map, lst = [1, 2, 2, 4, 6], []

for i in range(len(rand_map)):

	assembly = rand_map[i]
	lst.append(assembly)
	
	for j in range(i+1, len(rand_map)):
		num = assembly + rand_map[j]
		assembly += rand_map[j]
		lst.append(num)
print(len(lst))

with open('instance.txt', 'w+') as fh:
	fh.write(' '.join(str(num) for num in sorted(lst)))