cmp = g++
flags = -std=c++11 -pthread

All : Client.o Server.o

Client.o: httplib.h
	$(cmp) -o Client $(flags) Client.cpp

Server.o: httplib.h
	$(cmp) -o Server $(flags) Server.cpp
