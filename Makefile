CC = g++
STATIC_EXE = SLLsample.exe
DYNAMIC_EXE = DLLsample.exe
DLL = DSA.dll

####### Compile flags #######
EXE_CFLAGS = -Wall -Wextra -std=c++14 -g -Iinclude -Iinclude/SFML
DLL_CFLAGS = $(EXE_CFLAGS) -fPIC

####### Linker flags #######
#Linker flags for static exe build
EXE_LFLAGS = -Wall -Wextra -std=c++14 -g -Llib/SFML -lsfml-graphics -lsfml-window -lsfml-system -lopengl32
#Linker flags for dynamic exe build
EXE_LDFLAGS = $(EXE_LFLAGS) -Lbin -lDSA
#Linker flags for DLL build
DLL_LDFLAGS = $(EXE_LFLAGS) -shared

#obj/DataStructure.o obj/Algorithm.o obj/main.o
####### OBJECTS #######
SRC_DIR = ./src/*
SRC_FILE = $(wildcard src/*.cpp)
DLL_OBJECTS = obj/DataStructure.o obj/Algorithm.o obj/Visualization.o
#replace src/*.cpp to obj/*.o
STATIC_EXE_OBJECTS =$(patsubst src/%, obj/%, $(patsubst %.cpp, %.o, $(SRC_FILE)))
DYNAMIC_EXE_OBJECTS = obj/main.o

list_source_file: $(SRC_FILE)
	@echo $^ 

list_object_file:
	@echo $(STATIC_EXE_OBJECTS)

####### RULES #######

####### dynamic build run #######
dbr: bin/$(DLL) bin/$(DYNAMIC_EXE)
	./bin/DLLsample.exe 6

####### static build run #######
sbr: bin/$(STATIC_EXE)
	

####### dynamic EXE link rule #######
bin/$(DYNAMIC_EXE): $(DYNAMIC_EXE_OBJECTS) | bin
	$(CC) $(DYNAMIC_EXE_OBJECTS) -o $@ $(EXE_LDFLAGS)

####### static EXE link rule #######
bin/$(STATIC_EXE): $(STATIC_EXE_OBJECTS) | bin
	$(CC) $(STATIC_EXE_OBJECTS) -o $@ $(EXE_LFLAGS)

####### DLL link rule #######
bin/$(DLL): $(DLL_OBJECTS) | bin
	$(CC) $(DLL_OBJECTS) -o $@ $(DLL_LDFLAGS)

####### compile file rule #######
obj/%.o: src/%.cpp include/%.hpp | obj
	$(CC) -c $< -o $@ $(EXE_CFLAGS)

clean:
	rm obj/*.o
	rm bin/*.dll
	rm bin/*.exe	