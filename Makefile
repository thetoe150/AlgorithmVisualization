CC = g++
STATIC_EXE = NoDLLsample.exe
DYNAMIC_EXE = DLLsample.exe
DLL = DSA.dll

####### Compile flags #######
EXE_CFLAGS = -Wall -std=c++14 -g -Iinclude
DLL_CFLAGS = $(EXE_CFLAGS) -fPIC

####### Linker flags #######
#Linker flags for static exe build
EXE_LFLAGS = -Wall -std=c++14 -g
#Linker flags for dynamic exe build
EXE_LDFLAGS = $(EXE_LFLAGS) -Lbin -lDSA
#Linker flags for DLL build
DLL_LDFLAGS = -shared

####### OBJECTS #######
DLL_OBJECTS = obj/DataStructure.o obj/Algorithm.o
STATIC_EXE_OBJECTS = obj/DataStructure.o obj/Algorithm.o obj/main.o
DYNAMIC_EXE_OBJECTS = obj/main.o

####### RULES #######

####### dynamic build run #######
dbr: bin/$(DLL) bin/$(DYNAMIC_EXE)
	./bin/DLLsample.exe

####### static build run #######
sbr: bin/$(STATIC_EXE)
	./bin/NoDLLsample.exe

####### DLL build rule #######
bin/$(DLL): $(DLL_OBJECTS) | bin
	$(CC) $(DLL_LDFLAGS) $(DLL_OBJECTS) -o $@

####### dynamic EXE build rule #######
bin/$(DYNAMIC_EXE): $(DYNAMIC_EXE_OBJECTS) | bin
	$(CC) $(EXE_LDFLAGS) $(DYNAMIC_EXE_OBJECTS) -o $@

####### static EXE build rule #######
bin/$(STATIC_EXE): $(STATIC_EXE_OBJECTS) | bin
	$(CC) $(EXE_LFLAGS) $(STATIC_EXE_OBJECTS) -o $@

####### object build rule #######
obj/%.o: src/%.cpp include/%.hpp | obj
	$(CC) $(EXE_CFLAGS) -c $< -o $@

clean:
	rm obj/*.o
	rm bin/*.dll
	rm bin/*.exe	