CC=g++
LIBS= -lglfw -lGLU -lGL -lXrandr -lX11 -lrt -ldl
FLAGS= -pthread
INCLUDE_TAG=include

render: glad.o
	${CC} main.cpp glad.o $(FLAGS) -o render -I $(INCLUDE_TAG) $(LIBS)

glad.o: glad.c	
	${CC} glad.c -c -o glad.o -I $(INCLUDE_TAG)


cl: 
	rm *.o