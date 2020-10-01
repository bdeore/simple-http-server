all:
	mkdir ./out
	g++ -o ./out/server ./src/server.cpp ./src/logger.cpp -std=c++17

run:
	./out/server

clean:
	rm -rf ./out/