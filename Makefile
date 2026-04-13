CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -g -I"C:/PDCurses-3.9" -mwindows
LDFLAGS = -L"C:/PDCurses-3.9/wincon" -l:pdcurses.a

TARGET = curses_program.exe
SOURCES = main_curses.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

run: $(TARGET)
	$(TARGET)

clean:
	del $(TARGET) 2>nul

.PHONY: all run clean