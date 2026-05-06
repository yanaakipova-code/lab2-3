CXX = g++
CXXFLAGS = -std=c++20 -Wall -g -I..

TESTS = test_Complex.exe test_Matrix.exe test_Quete.exe test_Set.exe test_Shooting.exe

.PHONY: all clean run

all: $(TESTS)

test_Shooting.exe: Shooting_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

test_Complex.exe: Complex_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

test_Matrix.exe: Matrix_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

test_Quete.exe: Quete_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

test_Set.exe: Set_test.cpp
	$(CXX) $(CXXFLAGS) -D CATCH_CONFIG_MAIN $< -o $@

run: $(TESTS)
	./test_Complex.exe
	./test_Matrix.exe
	./test_Quete.exe
	./test_Set.exe
	./test_Shooting.exe

clean:
	del *.exe 2> nul

.PHONY: all clean run