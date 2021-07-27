all: main.c cacheutils.h
	@gcc main.c -Os -Wall -o histogram
	
solve: solution/main.c cacheutils.h
	@gcc solution/main.c -I. -Os -Wall -o histogram

clean:
	@rm -rf histogram
	@rm -rf histogram.csv
