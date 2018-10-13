TARGET = GeomExpert
PREFIX = /usr/local/bin
CC = g++

CFLAGS = -O3 -c -Wall -std=c++11 


all: $(TARGET)

$(TARGET): geomlist.o figure3d.o main.o
	$(CC) main.o figure3d.o  geomlist.o  -o $(TARGET)

geomlist.o: geomlist.cpp geomlist.h
	$(CC) $(CFLAGS) geomlist.cpp

figure3d.o: figure3d.cpp figure3d.h
	$(CC) $(CFLAGS) figure3d.cpp

main.o: main.cpp figure3d.h geomlist.h 
	$(CC) $(CFLAGS) main.cpp

install:
	install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TAGRET)

clean:
	rm -rf *.o $(TARGET)


