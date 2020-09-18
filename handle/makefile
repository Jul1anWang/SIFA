out: intervalue.o ctrl.o aes.o
	cc -o out intervalue.o ctrl.o aes.o

intervalue.o : intervalue.c ../ctrl.h ../aes.h
	cc -c intervalue.c

ctrl.o : ../ctrl.c ../aes.h
	cc -c ../ctrl.c

aes.o : ../aes.c
	cc -c ../aes.c

clean:
	rm intervalue.o ctrl.o aes.o out data/data.txt