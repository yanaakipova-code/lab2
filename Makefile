CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -I"C:/PDCurses-3.9"
LIBS = -L"C:/PDCurses-3.9/wincon" -l:pdcurses.a

SOURCES = main.cpp main_curses.cpp BitSequence.cpp
OBJECTS = main.o main_curses.o BitSequence.o
TARGET = program.exe

HEADERS = Sequence.hpp \
          ArraySequence.hpp \
          ArraySequence.tpp \
          DynamicArray.hpp \
          DynamicArray.tpp \
          LinkedList.hpp \
          LinkedList.tpp \
          ListSequence.hpp \
          ListSequence.tpp \
          ImmutableArraySequence.hpp \
          ImmutableArraySequence.tpp \
          ImmutableListSequence.hpp \
          ImmutableListSequence.tpp \
          BitSequence.hpp \
          Bit.hpp \
          Option.hpp \
          Iterator.hpp \
          MapReduce.hpp


.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	del /Q *.o *.exe 2>nul