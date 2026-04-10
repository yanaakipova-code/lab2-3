CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -mwindows -g

TARGET = lab_GUI.exe
SOURCES = main_gui.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

clean:
	del $(TARGET) 2>nul

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run