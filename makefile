CPP_SRC = PositionOthello.cpp Move.cpp MovesList.cpp main.cpp 

CXX=g++
CFLAGS=-g -O0 -Wall -Wextra 

othello: $(CPP_SRC) $(wildcard *.h) $(wildcard *.tpp)
	$(CXX) $(CPP_SRC) $(CFLAGS) -o $@

clean:
	-$(RM) *.o othello
