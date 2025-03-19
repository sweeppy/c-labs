# -c указывает компилятору не выполнять линковку.
# То есть, компилятор создаст объектный файл (.o),
# но не будет пытаться создать исполняемый файл.

objects = build/string.o build/file.o build/file2.o build/coder.o

flags = -g -Wall -Wextra -Wpedantic -Werror


# * Component builds

build/string.o: src/string.cpp src/string.hpp
	clang++ $(flags) -c -o build/string.o src/string.cpp
	
build/file.o: src/file.cpp src/file.hpp
	clang++ $(flags) -c -o build/file.o src/file.cpp
	
build/file2.o: src/file2.cpp src/file2.hpp
	clang++ $(flags) -c -o build/file2.o src/file2.cpp

build/coder.o: src/coder.cpp src/coder.hpp
	clang++ $(flags) -c -o build/coder.o src/coder.cpp

# * Debug build
# build/debug.out: $(objects) src/main.cpp
# 	clang++ $(flags) -o build/debug.out src/main.cpp $(objects)

# * Leaks build
build/leaks.out: $(objects) src/main.cpp build/folders src/Ifile.hpp
	clang++ $(flags) -o build/leaks.out src/main.cpp $(objects)

# * Folders target
build/folders:
	mkdir -p txt_files
	mkdir -p txt_files/testDerivedClasses
	mkdir -p txt_files/numbers1
	mkdir -p txt_files/numbers2
	mkdir -p txt_files/destructors
	mkdir -p txt_files/array
	mkdir -p txt_files/wrongArray
	mkdir -p txt_files/composition


leaks: build/leaks.out
	leaks --atExit -- build/leaks.out

clean:
	rm -rf build/*
	rm -rf txt_files/*