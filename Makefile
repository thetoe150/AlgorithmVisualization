CC = g++
CFLAGS = -Wall -std=c++11 -g

OBJECTS = DataStructure.o Algorithm.o
DLL_OBJECTS = DataStructure.dll Algorithm.dll
BIN = main

DSA_SLL: $(OBJECTS) main.o
	$(CC) $(CFLAGS) $^ -o $@

DSA_DLL: $(DLL_OBJECTS) main.o
	$(CC) $(CFLAGS) -Wl,-rpath=. -L . -lDataStructure -lAlgorithm -o main

%.dll: %.o
	$(CC) $(CFLAGS) -shared $^ -o $@

%.o: %.cpp %.hpp
	$(CC) $(CFLAGS) -fPIC -c $<      

clean:
	rm *.o *.dll *.exe