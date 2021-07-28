cmp = g++
flags = -std=c++11 -pthread

All : Client.o Server.o run

run:
	./Server

Client.o:
	$(cmp) -o Client $(flags) Client.cpp

Server.o:
	$(cmp) -o Server $(flags) Server.cpp
