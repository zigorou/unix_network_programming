VPATH = ../lib
CC = gcc
CPPFLAGS = -Wall -I../lib
TARGETS = daytimetcpcli daytimetcpsrv \
	byteorder daytimetcpsrv1
OBJECTS = error.o daytimetcpcli.o daytimetcpsrv.o \
	byteorder.o daytimetcpsrv1.o

all: $(TARGETS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(TARGETS)

error.o: error.h

daytimetcpcli: daytimetcpcli.o error.o
daytimetcpcli.o: error.h

daytimetcpsrv: daytimetcpsrv.o error.o
daytimetcpsrv.o: error.h

byteorder: byteorder.o error.o
byteorder.o: error.h

daytimetcpsrv1: daytimetcpsrv1.o error.o
daytimetcpsrv1.o: error.h
