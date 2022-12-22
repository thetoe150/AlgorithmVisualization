CC = g++
STATIC_EXE = NoDLLsample.exe
DYNAMIC_EXE = DLLsample.exe
DLL = DSA.dll

#Compiler flags
EXE_CFLAGS = -Wall -std=c++14 -g -Iinclude
DLL_CFLAGS = $(EXE_CFLAGS) -D ADD_EXPORTS

#Linker flags
EXE_LFLAGS = -Wall -std=c++14 -g
EXE_LDFLAGS = $(EXE_LFLAGS) -Lbin -lDSA
DLL_LDFLAGS = -shared

DLL_OBJECTS = obj/DataStructure.o obj/Algorithm.o
STATIC_EXE_OBJECTS = obj/DataStructure.o obj/Algorithm.o obj/main.o
DYNAMIC_EXE_OBJECTS = obj/main.o
BIN = main


all: bin/$(DLL) bin/$(DYNAMIC_EXE) bin/$(STATIC_EXE)
	./bin/DLLsample.exe

bin/$(DLL): $(DLL_OBJECTS) | bin
	$(CC) $(DLL_LDFLAGS) $(DLL_OBJECTS) -o $@

bin/$(DYNAMIC_EXE): $(DYNAMIC_EXE_OBJECTS) | bin
	$(CC) $(EXE_LDFLAGS) $(DYNAMIC_EXE_OBJECTS) -o $@

bin/$(STATIC_EXE): $(STATIC_EXE_OBJECTS) | bin
	$(CC) $(EXE_LFLAGS) $(STATIC_EXE_OBJECTS) -o $@

obj/%.o: src/%.cpp include/%.hpp | obj
	$(CC) $(EXE_CFLAGS) -c $< -o $@

clean:
	rm obj/*.o
	rm bin/*.dll
	rm bin/*.exe	