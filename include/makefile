CC=g++
CFLAGS= -std=gnu++17 -g
DEPS = lexer.hpp ast.hpp parser.hpp
OBJ = lexer.o ast.o parser.o ast_example.o

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ast_example : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean :
	rm -f *.o
