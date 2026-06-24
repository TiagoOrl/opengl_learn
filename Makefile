CC=g++
FLAGS= -pthread -std=c++23 -I./include -L./lib -lglfw -lassimp -Wl,-rpath,'$ORIGIN/lib'
OBJECTS = ./build/stb.o ./build/glad.o ./build/mesh.o ./build/shader.o ./build/vbo.o ./build/vao.o ./build/ebo.o ./build/texture.o ./build/transform.o ./build/camera.o ./build/model.o

main: ${OBJECTS}
	${CC} ./src/main.cpp ${OBJECTS} ${FLAGS} -o main -g


./build/vbo.o: ./src/vbo/vbo.cpp
	${CC} ./src/vbo/vbo.cpp -c -o ./build/vbo.o ${FLAGS} -g

./build/vao.o: ./src/vao/vao.cpp
	${CC} ./src/vao/vao.cpp -c -o ./build/vao.o ${FLAGS} -g

./build/ebo.o: ./src/ebo/ebo.cpp
	${CC} ./src/ebo/ebo.cpp -c -o ./build/ebo.o ${FLAGS} -g

./build/texture.o: ./src/texture/texture.cpp
	${CC} ./src/texture/texture.cpp -c -o ./build/texture.o ${FLAGS} -g

./build/transform.o: ./src/transform/transform.cpp
	${CC} ./src/transform/transform.cpp -c -o ./build/transform.o ${FLAGS} -g

./build/camera.o: ./src/camera/camera.cpp
	${CC} ./src/camera/camera.cpp -c -o ./build/camera.o ${FLAGS} -g

./build/shader.o: ./src/shader/shader.cpp
	${CC} ./src/shader/shader.cpp -c -o ./build/shader.o ${FLAGS} -g

./build/mesh.o: ./src/model/mesh.cpp
	${CC} ./src/model/mesh.cpp -c -o ./build/mesh.o ${FLAGS} -g

./build/model.o: ./src/model/model.cpp
	${CC} ./src/model/model.cpp -c -o ./build/model.o ${FLAGS} -g

./build/glad.o: ./src/glad/glad.c	
	${CC} ./src/glad/glad.c -c -o ./build/glad.o $(FLAGS) -g

./build/stb.o : ./src/stb/stb.cpp
	${CC} ./src/stb/stb.cpp -c -o ./build/stb.o ${FLAGS} -g


cl: 
	rm render main build/*.o