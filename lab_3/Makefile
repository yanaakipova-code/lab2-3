CXX = g++
CXXFLAGS = -std=c++20 -g -I"C:/PDCurses-3.9" -DPDC_WIDE
LDFLAGS = -L"C:/PDCurses-3.9/wincon" -l:pdcurses.a

TARGET = lab3.exe
SOURCE = main.cpp

all:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE) $(LDFLAGS)

run: all
	$(TARGET)

clean:
	del $(TARGET) 2>nul

.PHONY: all run clean