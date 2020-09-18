main : main.o ctrl.o  aes.o
	cc -o main main.o ctrl.o aes.o

main.o : main.c ctrl.h 
	cc -c main.c

ctrl.o : ctrl.c 
	cc -c ctrl.c 

aes.o : aes.c 
	cc -c aes.c

clean:
	rm plain.txt cipher.txt key.txt main main.o ctrl.o aes.o