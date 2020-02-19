include /usr/local/include/cantera/Cantera.mak

CC=gcc
CXX=g++
RM=rm -f
CXXFLAGS=-pthread -O3 -Wno-inline -g -std=c++0x
CPPFLAGS=$(CANTERA_INCLUDES)
LDFLAGS=
LDLIBS=$(CANTERA_LIBS)

SRCS=integrator.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: integrator

clean:
	$(RM) $(OBJS) integrator

dist-clean: clean
	$(RM) *~ 
