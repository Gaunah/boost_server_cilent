CFLAGS=-std=c++11 -Wall
LIBS=-lboost_system -lboost_thread

echo_server: sync_echo/echo_server.cpp
	mkdir -p bin
	g++ $(CFLAGS) $(LIBS) $< -o bin/$@

clean:
	rm -rf bin 
