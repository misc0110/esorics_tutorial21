all: signal

signal: signal.c
	gcc signal.c -Wall -static -o signal 

solve: solution/signal.c
	gcc solution/signal.c -I. -Wall -static -o signal
	
clean:
	@rm -f signal
	
