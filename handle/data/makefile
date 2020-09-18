out : testdec.o ctrl.o aes.o
	cc -o out testdec.o ctrl.o aes.o

testdec.o : testdec.c ../../aes.h ../../ctrl.h
	cc -c testdec.c

ctrl.o : ../../ctrl.c ../../aes.h
	cc -c ../../ctrl.c

aes.o : ../../aes.c
	cc -c ../../aes.c

clean:
	rm ctrl.o aes.o testdec.o out