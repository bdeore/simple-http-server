all:
	mkdir ./out
	g++ -g -o ./out/server ./src/server.cpp ./src/logger.cpp ./src/response.cpp -std=c++17 -Wall -Wextra -lstdc++fs -pthread

run:
	./out/server

clean:
	rm -rf ./out/

start: all run

restart: clean start run