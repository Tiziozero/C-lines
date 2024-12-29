all:
	cc -g -o main main.c -Wall -L./ -lraylib -lm 
	./main
