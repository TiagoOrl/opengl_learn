CC=g++
LIBS= -lglfw -lGLU -lGL -lXrandr -lX11 -lrt -ldl
FLAGS= -pthread
INCLUDE_TAG= -I include
OBJECTS = ./build/glad.o ./build/Shader.o ./build/VAO.o

render: ${OBJECTS}
	${CC} main.cpp ${OBJECTS} $(FLAGS) -o render $(INCLUDE_TAG) $(LIBS)

./build/Shader.o: ./src/Shader.cpp
	${CC} ./src/Shader.cpp -c -o ./build/Shader.o ${INCLUDE_TAG}

./build/VAO.o: ./src/VAO.cpp
	${CC} ./src/VAO.cpp -c -o ./build/VAO.o ${INCLUDE_TAG}

./build/glad.o: glad.c	
	${CC} glad.c -c -o ./build/glad.o $(INCLUDE_TAG)


cl: 
	rm render *.o build/*.o