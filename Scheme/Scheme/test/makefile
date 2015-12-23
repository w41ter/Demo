cc = g++
other = -std=c++11  -g 

testparser : testparser.o lexer.o string_table.o parser.o
    $(cc) $(other) testparser.o lexer.o string_table.o parser.o -o testparser.exe
    
testlexer : testlexer.o lexer.o string_table.o
    $(cc) $(other) testlexer.o lexer.o string_table.o -o testlexer.exe
    
testparser.o: testparser.cpp 
    $(cc) $(other) -c testparser.cpp 
    
parser.o : ../parser.cpp ../parser.h
    $(cc) $(other) -c ../parser.cpp -o parser.o
    
string_table.o : ../string_table.h ../string_table.cpp
    $(cc) $(other) -c ../string_table.cpp 
    
lexer.o : ../lexer.cpp ../lexer.h
    $(cc) $(other) -c ../lexer.cpp -o lexer.o 
    
testlexer.o: ../input.h testlexer.cpp lexer.o
    $(cc) $(other) -c testlexer.cpp -o testlexer.o

clean:
    rm *.o *.exe
    