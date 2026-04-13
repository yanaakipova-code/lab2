CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -g -I"C:/PDCurses-3.9"
CXXFLAGS += -DPDC_WIDE

PD_DIR = libs/PDCurses
PD_BUILD = $(PD_DIR)/wincon
PD_LIB = $(PD_BUILD)/libpdcurses.a

$(PD_LIB):
	cd $(PD_BUILD) && $(MAKE) -f Makefile
	cd $(PD_BUILD) && copy pdcurses.a libpdcurses.a

CXXFLAGS += -I$(PD_DIR)
LDFLAGS = -L$(PD_BUILD) -lpdcurses

TARGET = curses_program.exe
SOURCES = main_curses.cpp BitSequence.cpp
OBJECTS = main_curses.o BitSequence.o

all: $(PD_LIB) $(TARGET)

$(TARGET): $(OBJECTS) $(PD_LIB)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run: $(TARGET)
	$(TARGET)

clean:
	del $(TARGET) $(OBJECTS) 2>nul

.PHONY: all run clean