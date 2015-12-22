cc = g++

testlexer: testlexer.o lexer.o string_table.o
    $(cc) testlexer.o lexer.o string_table.o -o testlexer.exe
string_table.o: ../string_table.h ../string_table.cpp
    $(cc) -std=c++11 -c ../string_table.cpp 
lexer.o: ../lexer.cpp ../lexer.h
    $(cc) -std=c++11 -c ../lexer.cpp -o lexer.o 
testlexer.o: ../input.h testlexer.cpp lexer.o
    $(cc) -std=c++11 -c testlexer.cpp -o testlexer.o

clean:
    rm *.o *.exe
    