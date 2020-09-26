all:
	g++ -o main main.cpp -std=c++17

run:
	./main

clean:
	rm -f main