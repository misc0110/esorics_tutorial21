all: zombieload victim

solve: zombieload_solution victim

zombieload: zombieload.c
	gcc zombieload.c -Os -o zombieload 

zombieload_solution: solution/zombieload.c
	gcc solution/zombieload.c -Os -o zombieload -I.

victim: victim.c
	gcc victim.c -O3 -o victim
	
clean:
	rm -f zombieload victim
	
