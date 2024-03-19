CXXFLAGS = -std=c++20 -O2 -Wall -fPIC
CPPFLAGS = -DNDEBUG -I../include -I../include/muParser
LDFLAGS = -L../lib -Wl,-R../lib
LIBS = -lmuparser

SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

.PHONY: all clean distclean

all: minimize

minimize: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o minimize $(LIBS)

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $<

clean:
	$(RM) *.o 

distclean: clean
	$(RM) minimize