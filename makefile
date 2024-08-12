.PHONY: exe01 exe02

exe01:
	gcc exe01/bresenham.c -o main -lGL -lGLU -lglut -lm
	./main

exe02:
	g++ exe02/flor_de_abril.cpp -o main -lGL -lGLU -lglut -lm
	./main