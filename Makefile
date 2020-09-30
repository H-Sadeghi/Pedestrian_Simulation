TARGET = bin

CXX  = g++
COMP = -c
INC = -I
INC_LIB = inc


OBJ = main.o \
      parameter.o \
	  pedestrian.o\
	  queue.o \

bin/scheck.exe : main.o parameter.o pedestrian.o queue.o
	g++ bin/main.o bin/parameter.o bin/pedestrian.o bin/queue.o -o bin/pedSim.exe

default: $(OBJ)
	$(CXX) $(INC) -o bin/main.o bin/parameter.o bin/pedestrian.o bin/queue.o

main.o: src/main.cpp
	$(CXX) $(INC) $(INC_LIB) $(COMP) src/main.cpp -o bin/main.o

parameter.o: src/parameterReader.cpp
	$(CXX) $(INC) $(INC_LIB) $(COMP) src/parameterReader.cpp -o bin/parameter.o

pedestrian.o: src/pedestrian.cpp
	$(CXX) $(INC) $(INC_LIB) $(COMP) src/pedestrian.cpp -o bin/pedestrian.o

queue.o: src/queue.cpp
	$(CXX) $(INC) $(INC_LIB) $(COMP) src/queue.cpp -o bin/queue.o


clean:
	@echo "Clean..."
	@$(RM) waveguide *.o *.txt
