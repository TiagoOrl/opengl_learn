CC=g++
LIBS= -lglfw -lGLU -lGL -lXrandr -lX11 -lrt -ldl
FLAGS= -pthread
INCLUDE_TAG= -I include
OBJECTS = ./build/stb.o ./build/glad.o ./build/Shader.o ./build/VAO.o ./build/EBO.o ./build/Texture.o ./build/Transform.o ./build/Camera.o

render: ${OBJECTS}
	${CC} main.cpp ${OBJECTS} $(FLAGS) -o render $(INCLUDE_TAG) $(LIBS) -g

./build/Shader.o: ./src/shader/Shader.cpp
	${CC} ./src/shader/Shader.cpp -c -o ./build/Shader.o ${INCLUDE_TAG} -g

./build/VAO.o: ./src/vao/VAO.cpp
	${CC} ./src/vao/VAO.cpp -c -o ./build/VAO.o ${INCLUDE_TAG} -g

./build/EBO.o: ./src/ebo/EBO.cpp
	${CC} ./src/ebo/EBO.cpp -c -o ./build/EBO.o ${INCLUDE_TAG} -g

./build/Texture.o: ./src/texture/Texture.cpp
	${CC} ./src/texture/Texture.cpp -c -o ./build/Texture.o ${INCLUDE_TAG} -g

./build/Transform.o: ./src/transform/Transform.cpp
	${CC} ./src/transform/Transform.cpp -c -o ./build/Transform.o ${INCLUDE_TAG} -g

./build/Camera.o: ./src/camera/Camera.cpp
	${CC} ./src/camera/Camera.cpp -c -o ./build/Camera.o ${INCLUDE_TAG} -g

./build/glad.o: glad.c	
	${CC} glad.c -c -o ./build/glad.o $(INCLUDE_TAG) -g

./build/stb.o : stb.cpp
	${CC} stb.cpp -c -o ./build/stb.o ${INCLUDE_TAG} -g


cl: 
	rm render build/*.o