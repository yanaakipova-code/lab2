CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -g -I"C:/PDCurses-3.9" -DPDC_WIDE -Ilibs/PDCurses
LDFLAGS = -Llibs/PDCurses/wincon -lpdcurses
TARGET = curses_program.exe
SOURCE = main_curses.cpp

all: lib curses

lib:
	cd libs/PDCurses/wincon && $(MAKE) -f Makefile
	cd libs/PDCurses/wincon && copy pdcurses.a libpdcurses.a

curses:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

run: curses
	$(TARGET)

clean:
	del $(TARGET) 2>nul

.PHONY: all lib curses run clean