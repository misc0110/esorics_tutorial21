all: main.c
	gcc main.c -std=gnu11 -Os  -o spectre
	
solve: solution/main.c
	gcc solution/main.c -std=gnu11 -Os -I. -o spectre

clean:
	@rm -rf spectre
