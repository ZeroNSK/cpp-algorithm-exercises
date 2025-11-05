CXX = clang++
CXXFLAGS = -std=c++17 -Wall
OBJS = main.o stack_game.o set_atd.o turtles.o histogram.o bst_branches.o substring_unique.o lfu_cache.o AvlTree.o


program: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o program

%.o: %.cpp functions.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o program
