# -c указывает компилятору не выполнять линковку.
# То есть, компилятор создаст объектный файл (.o),
# но не будет пытаться создать исполняемый файл.

objects = build/string.o build/matrix.o build/shortArray.o build/workerDb.o build/file.o build/boolArray.o

flags = -g -std=c++17 -Wall -Wextra -Wpedantic -Werror


# * Component builds

build/string.o: src/string.cpp src/string.hpp
	clang++ $(flags) -c -o build/string.o src/string.cpp

build/matrix.o: src/matrix.cpp src/matrix.hpp
	clang++ $(flags) -c -o build/matrix.o src/matrix.cpp

build/shortArray.o: src/shortArray.cpp src/shortArray.hpp
	clang++ $(flags) -c -o build/shortArray.o src/shortArray.cpp

build/workerDb.o: src/workerDb.cpp src/workerDb.hpp
	clang++ $(flags) -c -o build/workerDb.o src/workerDb.cpp
	
build/file.o: src/file.cpp src/file.hpp
	clang++ $(flags) -c -o build/file.o src/file.cpp

build/boolArray.o: src/boolArray.cpp src/boolArray.hpp
	clang++ $(flags) -c -o build/boolArray.o src/boolArray.cpp

# * Debug build
# build/debug.out: $(objects) src/main.cpp
# 	clang++ $(flags) -o build/debug.out src/main.cpp $(objects)

# * Leaks build
build/leaks.out: $(objects) src/main.cpp
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