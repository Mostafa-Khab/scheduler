main: main.cpp schedule.hpp
	mkdir -p build
	g++ main.cpp -o build/main
	./build/main
	
