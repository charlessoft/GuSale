CXXSOURCES=../../src/IParseJson.cpp 
SOURCES=$(CXXSOURCES)
GXX=g++ -Wall -g
CPPFLAGS=
LDFLAGS=
LIBS=
target:
	$(GXX) $(CPPFLAGS) $(LDFLAGS) -c $(SOURCES) $(LIBS)
	ar -crs libgusale.a *.o
	ranlib libgusale.a
