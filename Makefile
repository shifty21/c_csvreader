all: main.c 
	gcc -g -Wall -o converter main.c
clean:
	rm -rf converter.dSYM/
	rm -r converter