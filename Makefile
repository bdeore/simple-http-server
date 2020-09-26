all:
	mkdir ./out
	g++ -o ./out/main ./src/main.cpp -std=c++17

run:
	./out/main

clean:
	rm -rf ./out/