# Invoke with: make -f makefile
CPP = g++
OFLAG = -o
.SUFFIXES : .o .cpp .c
.cpp.o :
	$(CPP) $(CPPFLAGS) -c $<
.c.o :
	$(CPP) $(CPPFLAGS) -c $<

all: multithread_sample

test: all 
	
bugs: 
	@echo No compiler bugs in this directory!

multithread_sample: multithread_sample.o 
	$(CPP) $(OFLAG) multithread_sample multithread_sample.o 

multithread_sample.o: multithread_sample.cpp 
