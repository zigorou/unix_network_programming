VPATH = ../lib
CC = gcc
CPPFLAGS = -Wall -I../lib
TARGETS = tcpserv01
OBJECTS = error.o readwrite.o tcpserv01.o

all: $(TARGET)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(TARGETS)

error.o: error.h
readwrite.o: readwrite.h

tcpserv01: tcpserv01.o error.o readwrite.o
tcpserv01.o: error.h
