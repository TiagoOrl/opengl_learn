CC=g++
LIBS= -lglfw -lGLU -lGL -lXrandr -lX11 -lrt -ldl
FLAGS= -pthread
INCLUDE_TAG= -I include
OBJECTS = ./build/stb.o ./build/glad.o ./build/Mesh.o ./build/Shader.o ./build/VBO.o ./build/VAO.o ./build/EBO.o ./build/Texture.o ./build/Transform.o ./build/Camera.o ./build/Object.o

main: ${OBJECTS}
	${CC} main.cpp ${OBJECTS} $(FLAGS) -o main $(INCLUDE_TAG) $(LIBS) -g

./build/Mesh.o: ./src/object_assimp/Mesh.cpp
	${CC} ./src/object_assimp/Mesh.cpp -c -o ./build/Mesh.o ${INCLUDE_TAG} -g

./build/VBO.o: ./src/object/vbo/VBO.cpp
	${CC} ./src/object/vbo/VBO.cpp -c -o ./build/VBO.o ${INCLUDE_TAG} -g

./build/VAO.o: ./src/object/vao/VAO.cpp
	${CC} ./src/object/vao/VAO.cpp -c -o ./build/VAO.o ${INCLUDE_TAG} -g

./build/EBO.o: ./src/object/ebo/EBO.cpp
	${CC} ./src/object/ebo/EBO.cpp -c -o ./build/EBO.o ${INCLUDE_TAG} -g

./build/Texture.o: ./src/object/texture/Texture.cpp
	${CC} ./src/object/texture/Texture.cpp -c -o ./build/Texture.o ${INCLUDE_TAG} -g

./build/Transform.o: ./src/object/transform/Transform.cpp
	${CC} ./src/object/transform/Transform.cpp -c -o ./build/Transform.o ${INCLUDE_TAG} -g

./build/Object.o: ./src/object/Object.cpp
	${CC} ./src/object/Object.cpp -c -o ./build/Object.o ${INCLUDE_TAG} -g

./build/Camera.o: ./src/camera/Camera.cpp
	${CC} ./src/camera/Camera.cpp -c -o ./build/Camera.o ${INCLUDE_TAG} -g

./build/Shader.o: ./src/object/shader/Shader.cpp
	${CC} ./src/object/shader/Shader.cpp -c -o ./build/Shader.o ${INCLUDE_TAG} -g

./build/glad.o: glad.c	
	${CC} glad.c -c -o ./build/glad.o $(INCLUDE_TAG) -g

./build/stb.o : stb.cpp
	${CC} stb.cpp -c -o ./build/stb.o ${INCLUDE_TAG} -g


cl: 
	rm render main build/*.o