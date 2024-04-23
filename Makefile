CC = g++
CFLAGS =  
LDFLAGS = 
STD = -std=c++11
LIBS = -lncurses

SRC = tetris.cpp game.cpp
OBJ = $(SRC:.cpp=.o)
EXECUTABLE = tetris

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(STD) $(LDFLAGS) $(OBJ) -o $(EXECUTABLE) $(LIBS)

.cpp.o:
	$(CC) $(STD) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXECUTABLE)