CC=g++
LIBS= -lglfw -lGLU -lGL -lXrandr -lX11 -lrt -ldl
FLAGS= -pthread
INCLUDE_TAG= -I include
OBJECTS = ./build/stb.o ./build/glad.o ./build/Shader.o ./build/VAO.o ./build/EBO.o ./build/Texture.o

render: ${OBJECTS}
	${CC} main.cpp ${OBJECTS} $(FLAGS) -o render $(INCLUDE_TAG) $(LIBS) -g

./build/Shader.o: ./src/Shader.cpp
	${CC} ./src/Shader.cpp -c -o ./build/Shader.o ${INCLUDE_TAG} -g

./build/VAO.o: ./src/VAO.cpp
	${CC} ./src/VAO.cpp -c -o ./build/VAO.o ${INCLUDE_TAG} -g

./build/EBO.o: ./src/EBO.cpp
	${CC} ./src/EBO.cpp -c -o ./build/EBO.o ${INCLUDE_TAG} -g

./build/Texture.o: ./src/Texture.cpp
	${CC} ./src/Texture.cpp -c -o ./build/Texture.o ${INCLUDE_TAG} -g

./build/glad.o: glad.c	
	${CC} glad.c -c -o ./build/glad.o $(INCLUDE_TAG) -g

./build/stb.o : stb.cpp
	${CC} stb.cpp -c -o ./build/stb.o ${INCLUDE_TAG} -g


cl: 
	rm render *.o build/*.o