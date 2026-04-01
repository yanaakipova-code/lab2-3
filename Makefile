CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS += -DPDC_WIDE -I"C:/PDCurses-3.9"           # для PDCurses
LDFLAGS = -L"C:/PDCurses-3.9/wincon" -l:pdcurses.a     # линковка с PDCurses

TARGET = lab2_curses.exe

# Исходные файлы (добавьте main_curses.cpp вместо gui_winapi.cpp)
SOURCES = main_curses.cpp BitSequence.cpp
OBJECTS = main_curses.o BitSequence.o

# Заголовочные файлы
HEADERS = Sequence.hpp ArraySequence.hpp ArraySequence.tpp \
          DynamicArray.hpp DynamicArray.tpp \
          LinkedList.hpp LinkedList.tpp \
          ListSequence.hpp ListSequence.tpp \
          ImmutableArraySequence.hpp ImmutableArraySequence.tpp \
          ImmutableListSequence.hpp ImmutableListSequence.tpp \
          BitSequence.hpp Bit.hpp \
          Option.hpp Iterator.hpp MapReduce.hpp

# Сборка
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

# Компиляция main_curses.cpp
main_curses.o: main_curses.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция BitSequence.cpp
BitSequence.o: BitSequence.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJECTS) $(TARGET)

# Запуск
run: $(TARGET)
	./$(TARGET)

# Пересборка
rebuild: clean $(TARGET)

.PHONY: all clean rebuild run
all: $(TARGET)