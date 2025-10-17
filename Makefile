CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -ftest-coverage -fprofile-arcs
LDFLAGS = -pthread
SRC = backup.cpp testa_backup.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = testa_backup

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

run: all
	./$(TARGET)

coverage: all
	./$(TARGET)
	gcov backup.cpp

clean:
	rm -f *.o *.gc* $(TARGET)
