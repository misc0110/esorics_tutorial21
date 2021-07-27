all: receive send transfer

solve: receive_solution send_solution transfer

receive: receive.c
	gcc receive.c -O3 -o receive  -lm

receive_solution: solution/receive.c
	gcc solution/receive.c -O3 -o receive -I. -lm

send: send.c
	gcc send.c -O3 -o send -lm -lpthread 

send_solution: solution/send.c
	gcc solution/send.c -O3 -o send -lm -lpthread -I.

transfer:
	dd if=/dev/zero of=transfer bs=4096 count=256
	
clean:
	rm -f send receive
