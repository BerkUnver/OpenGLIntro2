# the glad header refers to glad/glad.h so we put it in nested directories: lib/glad/glad/glad.c
all:
	mkdir -p build
	gcc \
		-Wall -Werror -Wno-missing-braces \
		-std=c99 \
		-o build/CGui.exe \
		-lwinmm -lgdi32 -luser32 -lOpenGL32 -lkernel32 -lshell32 -lmsvcrt \
		-Iinclude/glfw -Iinclude/glad \
		lib/glfw/libglfw3.a lib/glad/glad.c \
		src/main.c # src/cgui.c
	build/CGui.exe

clean:
	rm -rf build
