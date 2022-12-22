CC = g++
CFLAGS = -Wall -std=c++11 -g

SLL_OBJECTS = DataStructure.o Algorithm.o
DLL_OBJECT = DataStructure.dll Algorithm.dll
BIN = main

DSA_SLL: %(SLL_OBJECTS) main.o
	$(CC) $(CFLAGS) $^ -o $@

DSA_DLL: $(DLL_OBJECTS) main.o
	$(CC) $(CFLAGS) -Wl,-rpath=. -L . -lDataStructure -lAlgorithm -o main

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -fPIC -c $<      

%.dll: %.o
	$(CC) $(CFLAGS) -shared $^ -o $@

clean:
	rm *.o *.so