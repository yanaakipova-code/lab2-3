#include "catch.hpp"
#include "../../Error.hpp"
#include "../Set.hpp"
#include "../ArraySequence.hpp"
#include "../ListSequence.hpp"
#include <string>

int DoubleValue(const int& x) {
    return x * 2;
}

bool EvenNumber(const int& x){
    return (x % 2 == 0);
}

TEST_CASE("Set: конструктор по умолчанию") {
    Set<int, ArraySequence> set;
    
    REQUIRE(set.GetSize() == 0);
}

TEST_CASE("Set: конструктор копирования") {
    Set<int, ArraySequence> original;
    original.Add(1);
    original.Add(2);
    original.Add(3);
    
    Set<int, ArraySequence> copy(original);
    
    REQUIRE(copy.GetSize() == 3);
    REQUIRE(copy.Contains(1));
    REQUIRE(copy.Contains(2));
    REQUIRE(copy.Contains(3));

    copy.Add(4);
    REQUIRE(copy.GetSize() == 4);
    REQUIRE(original.GetSize() == 3);
}

TEST_CASE("Set: конструктор от Container") {
    ArraySequence<int> seq;
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(2);
    
    Set<int, ArraySequence> set(seq);
    
    REQUIRE(set.GetSize() == 3);
    REQUIRE(set.Contains(1));
    REQUIRE(set.Contains(2));
    REQUIRE(set.Contains(3));
}

TEST_CASE("Set: Add - добавление элементов") {
    Set<int, ArraySequence> set;
    
    set.Add(10);
    REQUIRE(set.GetSize() == 1);
    REQUIRE(set.Contains(10));
    
    set.Add(20);
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains(20));
    
    set.Add(30);
    REQUIRE(set.GetSize() == 3);
    REQUIRE(set.Contains(30));
}

TEST_CASE("Set: Add - дубликаты не добавляются") {
    Set<int, ArraySequence> set;
    
    set.Add(5);
    set.Add(5);
    set.Add(5);
    
    REQUIRE(set.GetSize() == 1);
    REQUIRE(set.Contains(5));
}

TEST_CASE("Set: Add - отрицательные числа") {
    Set<int, ArraySequence> set;
    
    set.Add(-1);
    set.Add(-2);
    set.Add(-3);
    
    REQUIRE(set.GetSize() == 3);
    REQUIRE(set.Contains(-1));
    REQUIRE(set.Contains(-2));
    REQUIRE(set.Contains(-3));
}

TEST_CASE("Set: Add - ноль") {
    Set<int, ArraySequence> set;
    
    set.Add(0);
    
    REQUIRE(set.GetSize() == 1);
    REQUIRE(set.Contains(0));
}

TEST_CASE("Set: Add - пустая строка") {
    Set<std::string, ArraySequence> set;
    
    set.Add("");
    
    REQUIRE(set.GetSize() == 1);
    REQUIRE(set.Contains(""));
}

TEST_CASE("Set: Add - длинная строка") {
    Set<std::string, ArraySequence> set;
    
    std::string long_str(1000, 'a');
    set.Add(long_str);
    
    REQUIRE(set.GetSize() == 1);
    REQUIRE(set.Contains(long_str));
}


TEST_CASE("Set: Remove по индексу - удаление из начала") {
    Set<int, ArraySequence> set;
    set.Add(10);
    set.Add(20);
    set.Add(30);
    
    set.RemoveByIndex(0);
    
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains(20));
    REQUIRE(set.Contains(30));
}

TEST_CASE("Set: Remove по индексу - удаление из середины") {
    Set<int, ArraySequence> set;
    set.Add(10);
    set.Add(20);
    set.Add(30);
    
    set.RemoveByIndex(1);
    
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains(10));
    REQUIRE(set.Contains(30));
}

TEST_CASE("Set: Remove по индексу - удаление из конца") {
    Set<int, ArraySequence> set;
    set.Add(10);
    set.Add(20);
    set.Add(30);
    
    set.RemoveByIndex(2);
    
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains(10));
    REQUIRE(set.Contains(20));
}

TEST_CASE("Set: Remove по индексу - единственный элемент") {
    Set<int, ArraySequence> set;
    set.Add(42);
    
    set.RemoveByIndex(0);
    
    REQUIRE(set.GetSize() == 0);
}

TEST_CASE("Set: Remove по индексу - отрицательный индекс") {
    Set<int, ArraySequence> set;
    set.Add(1);
    set.Add(2);
    
    REQUIRE_THROWS_AS(set.RemoveByIndex(-1), OutOfRangeException);
}

TEST_CASE("Set: Remove по индексу - индекс равен размеру") {
    Set<int, ArraySequence> set;
    set.Add(1);
    set.Add(2);
    
    REQUIRE_THROWS_AS(set.RemoveByIndex(2), OutOfRangeException);
}

TEST_CASE("Set: Remove по индексу - индекс больше размера") {
    Set<int, ArraySequence> set;
    set.Add(1);
    set.Add(2);
    
    REQUIRE_THROWS_AS(set.RemoveByIndex(10), OutOfRangeException);
}

TEST_CASE("Set: Remove по индексу - пустое множество") {
    Set<int, ArraySequence> set;
    
    REQUIRE_THROWS_AS(set.RemoveByIndex(0), OutOfRangeException);
}

TEST_CASE("Set: Remove по значению - существующий элемент") {
    Set<int, ArraySequence> set;
    set.Add(10);
    set.Add(20);
    set.Add(30);
    
    set.RemoveByValue(20);
    
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains(10));
    REQUIRE(set.Contains(30));
}

TEST_CASE("Set: Remove по значению - элемент в начале") {
    Set<int, ArraySequence> set;
    set.Add(10);
    set.Add(20);
    set.Add(30);
    
    set.RemoveByValue(10);
    
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains(20));
    REQUIRE(set.Contains(30));
}

TEST_CASE("Set: Remove по значению - элемент в конце") {
    Set<int, ArraySequence> set;
    set.Add(10);
    set.Add(20);
    set.Add(30);
    
    set.RemoveByValue(30);
    
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains(10));
    REQUIRE(set.Contains(20));
}

TEST_CASE("Set: Remove по значению - несуществующий элемент") {
    Set<int, ArraySequence> set;
    set.Add(1);
    set.Add(2);
    set.Add(3);
    
    REQUIRE_THROWS_AS(set.RemoveByValue(99), NotSetElemException);
}

TEST_CASE("Set: Remove по значению - пустое множество") {
    Set<int, ArraySequence> set;
    
    REQUIRE_THROWS_AS(set.RemoveByValue(1), NotSetElemException);
}

TEST_CASE("Set: Remove по значению - отрицательное число") {
    Set<int, ArraySequence> set;
    set.Add(-5);
    set.Add(-10);
    
    set.RemoveByValue(-5);
    
    REQUIRE(set.GetSize() == 1);
    REQUIRE(set.Contains(-10));
}

TEST_CASE("Set: Remove по значению - ноль") {
    Set<int, ArraySequence> set;
    set.Add(0);
    set.Add(1);
    
    set.RemoveByValue(0);
    
    REQUIRE(set.GetSize() == 1);
    REQUIRE(set.Contains(1));
}


TEST_CASE("Set: Contains - существующий элемент") {
    Set<int, ArraySequence> set;
    set.Add(100);
    set.Add(200);
    
    REQUIRE(set.Contains(100));
    REQUIRE(set.Contains(200));
}

TEST_CASE("Set: Contains - несуществующий элемент") {
    Set<int, ArraySequence> set;
    set.Add(1);
    set.Add(2);
    
    REQUIRE_FALSE(set.Contains(3));
    REQUIRE_FALSE(set.Contains(0));
}

TEST_CASE("Set: Contains - пустое множество") {
    Set<int, ArraySequence> set;
    
    REQUIRE_FALSE(set.Contains(42));
}

TEST_CASE("Set: Contains - после удаления") {
    Set<int, ArraySequence> set;
    set.Add(10);
    set.Add(20);
    set.Add(30);
    
    set.RemoveByValue(20);
    
    REQUIRE(set.Contains(10));
    REQUIRE_FALSE(set.Contains(20));
    REQUIRE(set.Contains(30));
}

TEST_CASE("Set: GetData - корректный индекс") {
    Set<int, ArraySequence> set;
    set.Add(100);
    set.Add(200);
    set.Add(300);
    
    int val0 = set.GetData(0);
    int val1 = set.GetData(1);
    int val2 = set.GetData(2);
    
    REQUIRE((val0 == 100 || val0 == 200 || val0 == 300));
    REQUIRE((val1 == 100 || val1 == 200 || val1 == 300));
    REQUIRE((val2 == 100 || val2 == 200 || val2 == 300));
    
    REQUIRE(val0 != val1);
    REQUIRE(val0 != val2);
    REQUIRE(val1 != val2);
}

TEST_CASE("Set: GetData - неверный индекс") {
    Set<int, ArraySequence> set;
    set.Add(1);
    
    REQUIRE_THROWS_AS(set.GetData(1), OutOfRangeException);
    REQUIRE_THROWS_AS(set.GetData(5), OutOfRangeException);
    REQUIRE_THROWS_AS(set.GetData(-1), OutOfRangeException);
}

TEST_CASE("Set: GetData - пустое множество") {
    Set<int, ArraySequence> set;
    
    REQUIRE_THROWS_AS(set.GetData(0), OutOfRangeException);
}

TEST_CASE("Set: GetSize - после операций") {
    Set<int, ArraySequence> set;
    
    REQUIRE(set.GetSize() == 0);
    
    set.Add(1);
    REQUIRE(set.GetSize() == 1);
    
    set.Add(2);
    REQUIRE(set.GetSize() == 2);
    
    set.Add(1);
    REQUIRE(set.GetSize() == 2);
    
    set.RemoveByValue(1);
    REQUIRE(set.GetSize() == 1);
    
    set.RemoveByValue(2);
    REQUIRE(set.GetSize() == 0);
}

TEST_CASE("Set: Map - удвоение") {
    Set<int, ArraySequence> set;
    set.Add(1);
    set.Add(2);
    set.Add(3);
    
    auto result = set.Map<int>(DoubleValue);
    
    REQUIRE(result.GetSize() == 3);
    REQUIRE(result.Contains(2));
    REQUIRE(result.Contains(4));
    REQUIRE(result.Contains(6));
}

TEST_CASE("Set: Map - пустое множество") {
    Set<int, ArraySequence> set;
    
    auto result = set.Map<int>(DoubleValue);
    
    REQUIRE(result.GetSize() == 0);
}

TEST_CASE("Set: Map - отрицательные числа") {
    Set<int, ArraySequence> set;
    set.Add(-1);
    set.Add(-2);
    set.Add(-3);
    
    auto result = set.Map<int>(DoubleValue);
    
    REQUIRE(result.GetSize() == 3);
    REQUIRE(result.Contains(-2));
    REQUIRE(result.Contains(-4));
    REQUIRE(result.Contains(-6));
}


TEST_CASE("Set: Where - фильтрация чётных чисел") {
    Set<int, ArraySequence> set;
    for (int i = 1; i <= 10; i++) {
        set.Add(i);
    }
    
    auto result = set.Where(EvenNumber);
    
    REQUIRE(result.GetSize() == 5);
    REQUIRE(result.Contains(2));
    REQUIRE(result.Contains(4));
    REQUIRE(result.Contains(6));
    REQUIRE(result.Contains(8));
    REQUIRE(result.Contains(10));
}

TEST_CASE("Set: Where - фильтрация чисел больше порога") {
    Set<int, ArraySequence> set;
    set.Add(5);
    set.Add(10);
    set.Add(15);
    set.Add(20);
    
    auto result = set.Where(EvenNumber);
    
    REQUIRE(result.GetSize() == 2);
    REQUIRE(result.Contains(10));
    REQUIRE(result.Contains(20));
}

TEST_CASE("Set: Where - пустое множество") {
    Set<int, ArraySequence> set;
    
    auto result = set.Where(EvenNumber);
    
    REQUIRE(result.GetSize() == 0);
}

TEST_CASE("Set: Where - все элементы подходят") {
    Set<int, ArraySequence> set;
    set.Add(2);
    set.Add(4);
    set.Add(8);
    
    auto result = set.Where(EvenNumber);
    
    REQUIRE(result.GetSize() == 3);
}

TEST_CASE("Set: Where - ни один элемент не подходит") {
    Set<int, ArraySequence> set;
    set.Add(1);
    set.Add(3);
    set.Add(5);
    
    auto result = set.Where(EvenNumber);
    
    REQUIRE(result.GetSize() == 0);
}

TEST_CASE("Set: Unification - непересекающиеся множества") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    
    Set<int, ArraySequence> set2;
    set2.Add(4);
    set2.Add(5);
    set2.Add(6);
    
    Set<int, ArraySequence> result = set1.Unification(set2);
    
    REQUIRE(result.GetSize() == 6);
    for (int i = 1; i <= 6; i++) {
        REQUIRE(result.Contains(i));
    }
}

TEST_CASE("Set: Unification - пересекающиеся множества") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    
    Set<int, ArraySequence> set2;
    set2.Add(2);
    set2.Add(3);
    set2.Add(4);
    
    Set<int, ArraySequence> result = set1.Unification(set2);
    
    REQUIRE(result.GetSize() == 4);
    REQUIRE(result.Contains(1));
    REQUIRE(result.Contains(2));
    REQUIRE(result.Contains(3));
    REQUIRE(result.Contains(4));
}

TEST_CASE("Set: Unification - одно множество пустое") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    
    Set<int, ArraySequence> set2;
    
    Set<int, ArraySequence> result = set1.Unification(set2);
    
    REQUIRE(result.GetSize() == 2);
    REQUIRE(result.Contains(1));
    REQUIRE(result.Contains(2));
}

TEST_CASE("Set: Unification - оба множества пустые") {
    Set<int, ArraySequence> set1;
    Set<int, ArraySequence> set2;
    
    Set<int, ArraySequence> result = set1.Unification(set2);
    
    REQUIRE(result.GetSize() == 0);
}

TEST_CASE("Set: Intersection - с общими элементами") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    set1.Add(4);
    
    Set<int, ArraySequence> set2;
    set2.Add(3);
    set2.Add(4);
    set2.Add(5);
    set2.Add(6);
    
    Set<int, ArraySequence> result = set1.Intersection(set2);
    
    REQUIRE(result.GetSize() == 2);
    REQUIRE(result.Contains(3));
    REQUIRE(result.Contains(4));
}

TEST_CASE("Set: Intersection - без общих элементов") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    
    Set<int, ArraySequence> set2;
    set2.Add(4);
    set2.Add(5);
    set2.Add(6);
    
    Set<int, ArraySequence> result = set1.Intersection(set2);
    
    REQUIRE(result.GetSize() == 0);
}

TEST_CASE("Set: Intersection - одно множество подмножество другого") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    set1.Add(4);
    set1.Add(5);
    
    Set<int, ArraySequence> set2;
    set2.Add(2);
    set2.Add(4);
    
    Set<int, ArraySequence> result = set1.Intersection(set2);
    
    REQUIRE(result.GetSize() == 2);
    REQUIRE(result.Contains(2));
    REQUIRE(result.Contains(4));
}

TEST_CASE("Set: Intersection - с пустым множеством") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    
    Set<int, ArraySequence> set2;
    
    Set<int, ArraySequence> result = set1.Intersection(set2);
    
    REQUIRE(result.GetSize() == 0);
}

TEST_CASE("Set: Subtraction - удаление общих элементов") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    set1.Add(4);
    
    Set<int, ArraySequence> set2;
    set2.Add(2);
    set2.Add(4);
    
    Set<int, ArraySequence> result = set1.Subtraction(set2);
    
    REQUIRE(result.GetSize() == 2);
    REQUIRE(result.Contains(1));
    REQUIRE(result.Contains(3));
    REQUIRE_FALSE(result.Contains(2));
    REQUIRE_FALSE(result.Contains(4));
}

TEST_CASE("Set: Subtraction - без общих элементов") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    
    Set<int, ArraySequence> set2;
    set2.Add(4);
    set2.Add(5);
    
    Set<int, ArraySequence> result = set1.Subtraction(set2);
    
    REQUIRE(result.GetSize() == 3);
    REQUIRE(result.Contains(1));
    REQUIRE(result.Contains(2));
    REQUIRE(result.Contains(3));
}

TEST_CASE("Set: Subtraction - все элементы удаляются") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    
    Set<int, ArraySequence> set2;
    set2.Add(1);
    set2.Add(2);
    set2.Add(3);
    
    Set<int, ArraySequence> result = set1.Subtraction(set2);
    
    REQUIRE(result.GetSize() == 0);
}

TEST_CASE("Set: Subtraction - с пустым множеством") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    
    Set<int, ArraySequence> set2;
    
    Set<int, ArraySequence> result = set1.Subtraction(set2);
    
    REQUIRE(result.GetSize() == 2);
    REQUIRE(result.Contains(1));
    REQUIRE(result.Contains(2));
}

TEST_CASE("Set: CheckSubset - корректное подмножество") {
    Set<int, ArraySequence> set1;
    for (int i = 1; i <= 10; i++) set1.Add(i);
    
    Set<int, ArraySequence> set2;
    set2.Add(2);
    set2.Add(4);
    set2.Add(6);
    
    REQUIRE(set1.CheckSubset(set2));
}

TEST_CASE("Set: CheckSubset - пустое множество - подмножество") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    
    Set<int, ArraySequence> set2;
    
    REQUIRE(set1.CheckSubset(set2));
}

TEST_CASE("Set: CheckSubset - множество не является подмножеством") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    
    Set<int, ArraySequence> set2;
    set2.Add(2);
    set2.Add(4);
    
    REQUIRE_FALSE(set1.CheckSubset(set2));
}

TEST_CASE("Set: CheckSubset - одинаковые множества") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    
    Set<int, ArraySequence> set2;
    set2.Add(1);
    set2.Add(2);
    set2.Add(3);
    
    REQUIRE(set1.CheckSubset(set2));
}

TEST_CASE("Set: Сomparison - одинаковые множества") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    
    Set<int, ArraySequence> set2;
    set2.Add(3);
    set2.Add(2);
    set2.Add(1);
    
    REQUIRE(set1.Сomparison(set2));
}

TEST_CASE("Set: Сomparison - разные размеры") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    
    Set<int, ArraySequence> set2;
    set2.Add(1);
    set2.Add(2);
    set2.Add(3);
    
    REQUIRE_FALSE(set1.Сomparison(set2));
}

TEST_CASE("Set: Сomparison - одинаковый размер, разные элементы") {
    Set<int, ArraySequence> set1;
    set1.Add(1);
    set1.Add(2);
    set1.Add(3);
    
    Set<int, ArraySequence> set2;
    set2.Add(1);
    set2.Add(2);
    set2.Add(4);
    
    REQUIRE_FALSE(set1.Сomparison(set2));
}

TEST_CASE("Set: Сomparison - пустые множества") {
    Set<int, ArraySequence> set1;
    Set<int, ArraySequence> set2;
    
    REQUIRE(set1.Сomparison(set2));
}


TEST_CASE("Set: с типом double") {
    Set<double, ArraySequence> set;
    
    set.Add(1.5);
    set.Add(2.7);
    set.Add(1.5);
    
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains(1.5));
    REQUIRE(set.Contains(2.7));
}

TEST_CASE("Set: с типом bool") {
    Set<bool, ArraySequence> set;
    
    set.Add(true);
    set.Add(false);
    set.Add(true);
    
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains(true));
    REQUIRE(set.Contains(false));
}

TEST_CASE("Set: с типом string") {
    Set<std::string, ArraySequence> set;
    
    set.Add("apple");
    set.Add("banana");
    set.Add("apple");
    
    REQUIRE(set.GetSize() == 2);
    REQUIRE(set.Contains("apple"));
    REQUIRE(set.Contains("banana"));
}

TEST_CASE("Set: с ListSequence вместо ArraySequence") {
    Set<int, ListSequence> set;
    
    set.Add(10);
    set.Add(20);
    set.Add(30);
    
    REQUIRE(set.GetSize() == 3);
    REQUIRE(set.Contains(20));
    
    set.RemoveByValue(20);
    REQUIRE(set.GetSize() == 2);
    REQUIRE_FALSE(set.Contains(20));
}

TEST_CASE("Set: исключения при неверных операциях") {
    Set<int, ArraySequence> set;
    
    REQUIRE_THROWS_AS(set.RemoveByValue(0), OutOfRangeException);
    REQUIRE_THROWS_AS(set.RemoveByValue(5), OutOfRangeException);
    REQUIRE_THROWS_AS(set.RemoveByValue(99), OutOfRangeException);
    
    REQUIRE_THROWS_AS(set.GetData(0), OutOfRangeException);

    REQUIRE_FALSE(set.Contains(42));
    
    set.Add(1);
    REQUIRE_THROWS_AS(set.RemoveByValue(99), NotSetElemException);
}

TEST_CASE("Set: итераторы - range-based for") {
    Set<int, ArraySequence> set;
    set.Add(1);
    set.Add(2);
    set.Add(3);
    
    int sum = 0;
    for (const auto& val : set) {
        sum += val;
    }
    REQUIRE(sum == 6);
}

TEST_CASE("Set: итераторы - пустое множество") {
    Set<int, ArraySequence> set;
    
    int count = 0;
    for (const auto& val : set) {
        count++;
    }
    REQUIRE(count == 0);
}


TEST_CASE("Set: добавление большого количества элементов") {
    Set<int, ArraySequence> set;
    
    for (int i = 0; i < 1000; i++) {
        set.Add(i);
    }
    
    REQUIRE(set.GetSize() == 1000);
    
    for (int i = 0; i < 1000; i++) {
        REQUIRE(set.Contains(i));
    }
}

TEST_CASE("Set: добавление элементов в обратном порядке") {
    Set<int, ArraySequence> set;
    
    for (int i = 1000; i > 0; i--) {
        set.Add(i);
    }
    
    REQUIRE(set.GetSize() == 1000);
    
    for (int i = 1; i <= 1000; i++) {
        REQUIRE(set.Contains(i));
    }
}