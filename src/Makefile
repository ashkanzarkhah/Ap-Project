cmp = g++
flags = -std=c++11 -pthread

All : Client.o Server.o
Allnrun : Client.o Server.o run

run:
	./Server

Client.o:
	$(cmp) Client.cpp -o Client $(flags)

Server.o:
	$(cmp) Server.cpp -o Server $(flags)
