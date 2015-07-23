CXX = g++
CXXFLAGS = -std=c++11 -O2

SRC =corner.cpp corner_orientation.cpp corner_permutation.cpp edge_orientation.cpp edge_permutation.cpp group.cpp indexing.cpp optimal_solver.cpp test.cpp
OBJ = $(SRC:%.cpp=%.o)
BIN = test
DEPENDFILE = .depend

all: test

test: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)

dep: $(SRC)
	$(CXX) $(CXXFLAGS) -MM $(SRC) > $(DEPENDFILE)

-include $(DEPENDFILE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm $(BIN) $(OBJ) $(DEPENDFILE)
