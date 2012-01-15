VPATH = ../lib
CC = gcc
CPPFLAGS = -I../lib
TARGET = daytimetcpcli daytimetcpsrv \
	byteorder daytimetcpsrv1
OBJECTS = error.o daytimetcpcli.o daytimetcpsrv.o \
	byteorder.o daytimetcpsrv1.o

all: daytimetcpcli daytimetcpsrv \
     byteorder daytimetcpsrv1

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

daytimetcpsrv1: daytimetcpsrv1.o error.o
daytimetcpsrv1.o: error.h
