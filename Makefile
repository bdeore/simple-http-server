all:
	mkdir ./out
	g++ -g -o ./out/server ./src/server.cpp ./src/logger.cpp ./src/response.cpp -std=c++17 -Wall -Wextra -pedantic

run:
	./out/server

clean:
	rm -rf ./out/

start: all run

restart: clean start run