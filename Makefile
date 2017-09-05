TARGET = expressions
SOURCE = ast/ast.cpp register_manager/register_manager.cpp parser.cpp lexer.cpp main.cpp
OBJECTS = $(SOURCE:.cpp=.o)

$(TARGET): $(OBJECTS)
	g++ -o $@ $^

parser.cpp: parser.y
	bison --defines=tokens.h -o $@ $<

lexer.cpp: lexer.l
	flex -o $@ $<

%.o: %.cpp tokens.h ast/ast.h register_manager/register_manager.h
	g++ -std=c++11 -c -o $@ $<

run: $(TARGET)
	./$(TARGET) < test.txt

clean:
	rm -f parser.cpp lexer.cpp ast/*.o register_manager/*.o *.o $(TARGET)