#include "catch.hpp"
#include "../DynamicArray.hpp"

TEST_CASE("Динамический массив 1.1: Get - получение элемента по индексу"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);

    REQUIRE(array.Get(0) == 2);
    REQUIRE(array.Get(1) == 3);
    REQUIRE(array.Get(2) == 4);
    REQUIRE(array.Get(3) == 5);
    REQUIRE(array.Get(4) == 6);
    REQUIRE(array.Get(5) == 7);
}

TEST_CASE("Динамический массив 1.2: Get - отрицательный индекс и индекс за пределами"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);

    REQUIRE_THROWS_AS(array.Get(-1), std::out_of_range);
    REQUIRE_THROWS_AS(array.Get(6), std::out_of_range);
    REQUIRE_THROWS_AS(array.Get(100), std::out_of_range);
}

TEST_CASE("Динамический массив 2.1: GetSize - непустой массив"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);

    REQUIRE(array.GetSize() == 6);
}

TEST_CASE("Динамический массив 2.2: GetSize - пустой массив"){
    DynamicArray<int> array;

    REQUIRE(array.GetSize() == 0);
}

TEST_CASE("Динамический массив 2.3: GetSize - после изменения размера"){
    int temp[] = {1, 2, 3};
    DynamicArray<int> array(temp, 3);
    
    array.Resize(10);
    REQUIRE(array.GetSize() == 10);
    
    array.Resize(2);
    REQUIRE(array.GetSize() == 2);
}

TEST_CASE("Динамический массив 3.1: Set - изменение элемента"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);
    
    array.Set(2, 5);
    REQUIRE(array.Get(2) == 5);
}

TEST_CASE("Динамический массив 3.2: Set - изменение первого и последнего"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);
    
    array.Set(0, 100);
    array.Set(5, 200);
    
    REQUIRE(array.Get(0) == 100);
    REQUIRE(array.Get(5) == 200);
}

TEST_CASE("Динамический массив 3.3: Set - исключение при неверном индексе"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);
    
    REQUIRE_THROWS_AS(array.Set(6, 100), std::out_of_range);
    REQUIRE_THROWS_AS(array.Set(-1, 100), std::out_of_range);
    REQUIRE_THROWS_AS(array.Set(100, 100), std::out_of_range);
}

TEST_CASE("Динамический массив 4.1: Resize - увеличение размера"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);
    
    array.Resize(10);
    
    REQUIRE(array.GetSize() == 10);
    REQUIRE(array.Get(6) == 0);
    REQUIRE(array.Get(9) == 0);
}

TEST_CASE("Динамический массив 4.2: Resize - уменьшение размера"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);
   
    array.Resize(3);
    
    REQUIRE(array.GetSize() == 3);
    REQUIRE(array.Get(0) == 2);
    REQUIRE(array.Get(1) == 3);
    REQUIRE(array.Get(2) == 4);
    REQUIRE_THROWS_AS(array.Get(3), std::out_of_range);
}

TEST_CASE("Динамический массив 4.3: Resize - тот же размер"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);
    
    array.Resize(6);
    
    REQUIRE(array.GetSize() == 6);
    REQUIRE(array.Get(0) == 2);
    REQUIRE(array.Get(5) == 7);
}

TEST_CASE("Динамический массив 4.4: Resize - размер 0"){
    int temp[] = {2, 3, 4, 5, 6, 7};
    DynamicArray<int> array(temp, 6);
    
    array.Resize(0);
    
    REQUIRE(array.GetSize() == 0);
    REQUIRE_THROWS_AS(array.Get(0), std::out_of_range);
}

TEST_CASE("Динамический массив 4.5: Resize - увеличение пустого массива"){
    DynamicArray<int> array;
    
    array.Resize(5);
    
    REQUIRE(array.GetSize() == 5);
    for (size_t i = 0; i < 5; i++) {
        REQUIRE(array.Get(i) == 0);
    }
}

TEST_CASE("Динамический массив 5.1: Конструктор по умолчанию"){
    DynamicArray<int> array;
    
    REQUIRE(array.GetSize() == 0);
}

TEST_CASE("Динамический массив 5.2: Конструктор с размером"){
    DynamicArray<int> array(5);
    
    REQUIRE(array.GetSize() == 5);
    for (size_t i = 0; i < 5; i++) {
        REQUIRE(array.Get(i) == 0);
    }
}

TEST_CASE("Динамический массив 5.3: Конструктор копирования"){
    int temp[] = {1, 2, 3, 4, 5};
    DynamicArray<int> original(temp, 5);
    
    DynamicArray<int> copy(original);
    
    REQUIRE(copy.GetSize() == 5);
    REQUIRE(copy.Get(0) == 1);
    REQUIRE(copy.Get(4) == 5);
    
    original.Set(0, 999);
    REQUIRE(copy.Get(0) == 1);
}

TEST_CASE("Динамический массив 6.1: получение элемента"){
    int temp[] = {10, 20, 30, 40};
    DynamicArray<int> array(temp, 4);
    
    REQUIRE(array.Get(0) == 10);
    REQUIRE(array.Get(1) == 20);
    REQUIRE(array.Get(2) == 30);
    REQUIRE(array.Get(3) == 40);
}

TEST_CASE("Динамический массив 6.2: изменение элемента"){
    int temp[] = {1, 2, 3};
    DynamicArray<int> array(temp, 3);
    
    array.Set(1, 100);
    
    REQUIRE(array.Get(1) == 100);
}