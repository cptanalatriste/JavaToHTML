all: parser

OBJS = parser.o  \
       codegen.o \
       main.o    \
       tokens.o  \

clean:
	$(RM) -rf parser.cpp parser.hpp parser tokens.cpp $(OBJS)

parser.cpp: parser.y
	bison -d -o $@ $^
	
parser.hpp: parser.cpp

tokens.cpp: tokens.l parser.hpp
	flex -o $@ $^

%.o: %.cpp
	g++ -c -o $@ $<


parser: $(OBJS)
	g++ -o $@ $(OBJS)
