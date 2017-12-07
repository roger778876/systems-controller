all: controller.c
	gcc -o controller controller.c

run: all
	./controller

clean:
	rm -f *.o
	rm -f *~
	rm -f controller