CFLAGS=-g -Wall -std=gnu11

all:mpadech1_phone_directory.out

mpadech1_phone_directory.out:mpadech1_phone_directory.c
	gcc $(CFLAGS) mpadech1_phone_directory.c -o mpadech1_phone_directory.out

checkmem:mpadech1_phone_directory
	valgrind ./mpadech1_phone_directory.out

clean:
	rm mpadech1_phone_directory.out

run:
	./mpadech1_phone_directory.out input_2.txt
