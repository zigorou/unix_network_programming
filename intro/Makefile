VPATH = ../lib
CC = gcc
CPPFLAGS = -I../lib
TARGET = daytimetcpcli daytimetcpsrv
OBJECTS = error.o daytimetcpcli.o daytimetcpsrv.o

all: daytimetcpcli daytimetcpsrv

clean:
	$(RM) $(OBJECTS)
	$(RM) $(TARGET)

error.o: error.h

daytimetcpcli: daytimetcpcli.o error.o
daytimetcpcli.o: error.h

daytimetcpsrv: daytimetcpsrv.o error.o
daytimetcpsrv.o: error.h

