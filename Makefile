run: clean generate execute
	
generate:
	g++ src/sequential.cpp src/calculations.cpp -o build/sequential.o

clean:
	rm -rf build/*
	rm -rf test/*

execute:
	./build/sequential.o

test: clean buildTests executeTests

buildTests:
	g++ src/calculations.cpp src/calculations.spec.cpp -o test/unit.o

executeTests:
	./test/unit.o