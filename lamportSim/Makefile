#------------------------------------------------------------------------------
# Makefile for building code for CSCI503 Project 4
# Author: Boakye Dankwa
# Course: CSCI 537 Distributed System
# Date: September 2016
#------------------------------------------------------------------------------
SRCDIR = ./src/

OBJDIR  = ./obj/

INCDIR = ./src/

OBJ   = $(OBJDIR)lamportSim.o $(OBJDIR)Event.o \
	   $(OBJDIR)InternalEvent.o $(OBJDIR)LogicalClock.o $(OBJDIR)Mailbox.o \
	   $(OBJDIR)Message.o $(OBJDIR)Process.o $(OBJDIR)ReceiveEvent.o \
	   $(OBJDIR)SendEvent.o 

TARGET = lmptSim


INCLUDES = -I$(INCDIR)
LIBRARIES =.
CPP = g++
CFLAGS = -Wall -c
LFLAGS = -lpthread
#------------------------------------------------------------------------------


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CPP) $(OBJ) $(LFLAGS) -o $(TARGET)	

$(OBJDIR)lamportSim.o : $(SRCDIR)lamportSim.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) $(SRCDIR)lamportSim.cpp -o $(OBJDIR)lamportSim.o

$(OBJDIR)Event.o : $(SRCDIR)Event.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) $(SRCDIR)Event.cpp -o $(OBJDIR)Event.o

$(OBJDIR)InternalEvent.o : $(SRCDIR)InternalEvent.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) $(SRCDIR)InternalEvent.cpp -o $(OBJDIR)InternalEvent.o
		
$(OBJDIR)LogicalClock.o : $(SRCDIR)LogicalClock.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) $(SRCDIR)LogicalClock.cpp -o $(OBJDIR)LogicalClock.o

$(OBJDIR)Mailbox.o : $(SRCDIR)Mailbox.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) $(SRCDIR)Mailbox.cpp -o $(OBJDIR)Mailbox.o

$(OBJDIR)Message.o : $(SRCDIR)Message.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) $(SRCDIR)Message.cpp -o $(OBJDIR)Message.o
	
$(OBJDIR)Process.o : $(SRCDIR)Process.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) $(SRCDIR)Process.cpp -o $(OBJDIR)Process.o

$(OBJDIR)ReceiveEvent.o : $(SRCDIR)ReceiveEvent.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) $(SRCDIR)ReceiveEvent.cpp -o $(OBJDIR)ReceiveEvent.o

$(OBJDIR)SendEvent.o : $(SRCDIR)SendEvent.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) $(SRCDIR)SendEvent.cpp -o $(OBJDIR)SendEvent.o
	

clean:

	rm -f $(OBJ) $(TARGET)
