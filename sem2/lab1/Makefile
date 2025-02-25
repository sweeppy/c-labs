# -c указывает компилятору не выполнять линковку.
# То есть, компилятор создаст объектный файл (.o),
# но не будет пытаться создать исполняемый файл.

objects = build/rect.o build/matrix.o build/string.o build/barrel.o build/wrapper.o

test_rect_objects = build/rect.o build/tests

all_rect_tests = test_rect_basic_methods test_rect_properties test_rect_operations test_bounding_rect

flags = -g -Wall -Wextra -Wpedantic -Werror


# * Component builds
build/rect.o: src/rect.cpp src/rect.hpp
	clang++ $(flags) -c -o build/rect.o src/rect.cpp

build/matrix.o: src/matrix.cpp src/matrix.hpp
	clang++ $(flags) -c -o build/matrix.o src/matrix.cpp

build/string.o: src/string.cpp src/string.hpp
	clang++ $(flags) -c -o build/string.o src/string.cpp

build/barrel.o: src/barrel.cpp src/barrel.hpp
	clang++ $(flags) -c -o build/barrel.o src/barrel.cpp

build/wrapper.o: src/wrapper.cpp src/wrapper.hpp
	clang++ $(flags) -c -o build/wrapper.o src/wrapper.cpp

build/debug.out: $(objects) src/main.cpp
	clang++ $(flags) -o build/debug.out src/main.cpp $(objects)



# * Leaks build
build/leaks.out: $(objects) src/main.cpp
	clang++ $(flags) -o build/leaks.out src/main.cpp $(objects)

# * Test folder target
build/tests:
	mkdir -p build/tests

# * Tests builds
build/test_rect_basic_methods.out: tests/test_rect_basic_methods.cpp $(test_rect_objects)
	clang++ $(flags) -o build/tests/test_rect_basic_methods.out tests/test_rect_basic_methods.cpp build/rect.o

build/test_rect_properties.out: tests/test_rect_properties.cpp $(test_rect_objects)
	clang++ $(flags) -o build/tests/test_rect_properties.out tests/test_rect_properties.cpp build/rect.o

build/test_rect_operations.out: tests/test_rect_operations.cpp $(test_rect_objects)
	clang++ $(flags) -o build/tests/test_rect_operations.out tests/test_rect_operations.cpp build/rect.o

build/test_bounding_rect.out: tests/test_bounding_rect.cpp $(test_rect_objects)
	clang++ $(flags) -o build/tests/test_bounding_rect.out tests/test_bounding_rect.cpp build/rect.o


# * Run builds
debug: build/debug.out
	lldb build/debug.out

leaks: build/leaks.out
	leaks --atExit -- build/leaks.out < src/input.txt

# * Run rect tests
test_rect_basic_methods: build/test_rect_basic_methods.out
	leaks --atExit -- build/tests/test_rect_basic_methods.out

test_rect_properties: build/test_rect_properties.out
	leaks --atExit -- build/tests/test_rect_properties.out

test_rect_operations: build/test_rect_operations.out
	leaks --atExit -- build/tests/test_rect_operations.out

test_bounding_rect: build/test_bounding_rect.out
	leaks --atExit -- build/tests/test_bounding_rect.out

test: $(all_rect_tests)
	

clean:
	rm -rf build/*