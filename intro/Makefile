VPATH = ../lib
CC = gcc
CPPFLAGS = -I../lib
TARGET = daytimetcpcli daytimetcpsrv \
	byteorder
OBJECTS = error.o daytimetcpcli.o daytimetcpsrv.o \
	byteorder.o

all: daytimetcpcli daytimetcpsrv byteorder

clean:
	$(RM) $(OBJECTS)
	$(RM) $(TARGET)

error.o: error.h

daytimetcpcli: daytimetcpcli.o error.o
daytimetcpcli.o: error.h

daytimetcpsrv: daytimetcpsrv.o error.o
daytimetcpsrv.o: error.h

byteorder: byteorder.o error.o
byteorder.o: error.h
