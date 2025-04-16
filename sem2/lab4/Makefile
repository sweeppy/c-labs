# -c указывает компилятору не выполнять линковку.
# То есть, компилятор создаст объектный файл (.o),
# но не будет пытаться создать исполняемый файл.

objects = build/Circle.o build/List.o build/Pointer.o

flags = -g -Wall -Wextra -Wpedantic -Werror


# * Component builds

build/Circle.o: src/Circle.cpp src/Circle.hpp
	clang++ $(flags) -c -o build/Circle.o src/Circle.cpp
build/List.o: src/List.cpp src/List.hpp
	clang++ $(flags) -c -o build/List.o src/List.cpp
build/Pointer.o: src/Pointer.cpp src/Pointer.hpp
	clang++ $(flags) -c -o build/Pointer.o src/Pointer.cpp

# * Leaks build
build/leaks.out: $(objects) src/main.cpp src/colors.hpp build/folders 
	clang++ $(flags) -o build/leaks.out src/main.cpp $(objects)

# * Folders target
build/folders:
	mkdir -p txt_files

leaks: build/leaks.out
	leaks --atExit -- build/leaks.out

clean:
	rm -rf build/*
	rm -rf txt_files/*