# the glad header refers to glad/glad.h so we put it in nested directories: lib/glad/glad/glad.c
APP := OpenGLIntro2.exe
all:
	mkdir -p build
	gcc \
		-static \
		-Wall -Werror -Wno-missing-braces \
		-std=c99 \
		-o build/${APP} \
		-Iinclude/glfw -Iinclude/glad \
		src/main.c src/draw.c src/draw_gl.c src/math.c src/log.c\
		lib/glfw/libglfw3.a lib/glad/glad.c \
		-lwinmm -lgdi32 -luser32 -lOpenGL32 -lkernel32 -lshell32 -lmsvcrt
	build/${APP}

clean:
	rm -rf build
