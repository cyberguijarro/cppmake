SOURCES=src/toolchain.cpp \
	src/node.cpp \
	src/file.cpp \
	src/object.cpp \
	src/program.cpp \
	src/staticlibrary.cpp \

OBJECTS=$(subst .cpp,.o,$(SOURCES))
CXXFLAGS=-std=c++11 -Iinclude
AR=ar
ARFLAGS=rcs
RM=rm
RMFLAGS=-f

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

build: build.cpp cppmake.a
	$(CXX) $(CXXFLAGS) $^ -o $@

cppmake.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $(OBJECTS) 

clean:
	$(RM) $(RMFLAGS) build cppmake.a $(OBJECTS)
