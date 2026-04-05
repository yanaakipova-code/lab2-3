#include "catch.hpp"
#include "../LinkedList.hpp"

TEST_CASE("Двусвязный список 7.1: конструктор по умолчанию"){
    LinkedList<int> list;
    
    REQUIRE(list.GetLength() == 0);
    REQUIRE(list.IsEmpty() == true);
}

TEST_CASE("Двусвязный список 7.2: конструктор из массива"){
    int temp[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(temp, 5);
    
    REQUIRE(list.GetLength() == 5);
    REQUIRE(list.GetFirst() == 1);
    REQUIRE(list.GetLast() == 5);
    REQUIRE(list.Get(0) == 1);
    REQUIRE(list.Get(2) == 3);
    REQUIRE(list.Get(4) == 5);
}

TEST_CASE("Двусвязный список 7.3: конструктор копирования"){
    int temp[] = {10, 20, 30};
    LinkedList<int> original(temp, 3);
    LinkedList<int> copy(original);
    
    REQUIRE(copy.GetLength() == 3);
    REQUIRE(copy.Get(0) == 10);
    REQUIRE(copy.Get(1) == 20);
    REQUIRE(copy.Get(2) == 30);
    
    original.Set(0, 999);
    REQUIRE(copy.Get(0) == 10);
}

TEST_CASE("Двусвязный список 8.1: GetFirst"){
    int temp[] = {5, 10, 15};
    LinkedList<int> list(temp, 3);
    
    REQUIRE(list.GetFirst() == 5);
}

TEST_CASE("Двусвязный список 8.2: GetFirst на пустом списке"){
    LinkedList<int> list;
    
    REQUIRE_THROWS_AS(list.GetFirst(), std::out_of_range);
}

TEST_CASE("Двусвязный список 8.3: GetLast"){
    int temp[] = {5, 10, 15};
    LinkedList<int> list(temp, 3);
    
    REQUIRE(list.GetLast() == 15);
}

TEST_CASE("Двусвязный список 8.4: GetLast на пустом списке"){
    LinkedList<int> list;
    
    REQUIRE_THROWS_AS(list.GetLast(), std::out_of_range);
}

TEST_CASE("Двусвязный список 8.5: Get по индексу"){
    int temp[] = {100, 200, 300, 400};
    LinkedList<int> list(temp, 4);
    
    REQUIRE(list.Get(0) == 100);
    REQUIRE(list.Get(1) == 200);
    REQUIRE(list.Get(2) == 300);
    REQUIRE(list.Get(3) == 400);
}

TEST_CASE("Двусвязный список 8.6: Get с неверным индексом"){
    int temp[] = {1, 2, 3};
    LinkedList<int> list(temp, 3);
    
    REQUIRE_THROWS_AS(list.Get(3), std::out_of_range);
    REQUIRE_THROWS_AS(list.Get(100), std::out_of_range);
}

TEST_CASE("Двусвязный список 8.7: GetLength"){
    int temp[] = {1, 2, 3, 4, 5, 6, 7};
    LinkedList<int> list(temp, 7);
    
    REQUIRE(list.GetLength() == 7);
}

TEST_CASE("Двусвязный список 8.8: IsEmpty"){
    LinkedList<int> emptyList;
    int temp[] = {1, 2, 3};
    LinkedList<int> nonEmptyList(temp, 3);
    
    REQUIRE(emptyList.IsEmpty() == true);
    REQUIRE(nonEmptyList.IsEmpty() == false);
}

TEST_CASE("Двусвязный список 9.1: Append"){
    LinkedList<int> list;
    
    list.Append(10);
    list.Append(20);
    list.Append(30);
    
    REQUIRE(list.GetLength() == 3);
    REQUIRE(list.GetFirst() == 10);
    REQUIRE(list.GetLast() == 30);
    REQUIRE(list.Get(0) == 10);
    REQUIRE(list.Get(1) == 20);
    REQUIRE(list.Get(2) == 30);
}

TEST_CASE("Двусвязный список 9.2: Prepend"){
    LinkedList<int> list;
    
    list.Append(20);
    list.Append(30);
    list.Prepend(10);
    
    REQUIRE(list.GetLength() == 3);
    REQUIRE(list.GetFirst() == 10);
    REQUIRE(list.Get(0) == 10);
    REQUIRE(list.Get(1) == 20);
    REQUIRE(list.Get(2) == 30);
}

TEST_CASE("Двусвязный список 9.3: InsertAt в начало"){
    int temp[] = {2, 3, 4};
    LinkedList<int> list(temp, 3);
    
    list.InsertAt(1, 0);
    
    REQUIRE(list.GetLength() == 4);
    REQUIRE(list.Get(0) == 1);
    REQUIRE(list.Get(1) == 2);
    REQUIRE(list.Get(2) == 3);
    REQUIRE(list.Get(3) == 4);
}

TEST_CASE("Двусвязный список 9.4: InsertAt в середину"){
    int temp[] = {1, 2, 4, 5};
    LinkedList<int> list(temp, 4);
    
    list.InsertAt(3, 2);
    
    REQUIRE(list.GetLength() == 5);
    REQUIRE(list.Get(0) == 1);
    REQUIRE(list.Get(1) == 2);
    REQUIRE(list.Get(2) == 3);
    REQUIRE(list.Get(3) == 4);
    REQUIRE(list.Get(4) == 5);
}

TEST_CASE("Двусвязный список 9.5: InsertAt в конец"){
    int temp[] = {1, 2, 3};
    LinkedList<int> list(temp, 3);
    
    list.InsertAt(4, 3);
    
    REQUIRE(list.GetLength() == 4);
    REQUIRE(list.Get(3) == 4);
    REQUIRE(list.GetLast() == 4);
}

TEST_CASE("Двусвязный список 9.6: InsertAt с неверным индексом"){
    int temp[] = {1, 2, 3};
    LinkedList<int> list(temp, 3);
    
    REQUIRE_THROWS_AS(list.InsertAt(99, 5), std::out_of_range);
    REQUIRE_THROWS_AS(list.InsertAt(99, 100), std::out_of_range);
}

TEST_CASE("Двусвязный список 10.1: Set"){
    int temp[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(temp, 5);
    
    list.Set(2, 100);
    
    REQUIRE(list.Get(2) == 100);
    REQUIRE(list.Get(0) == 1);
    REQUIRE(list.Get(1) == 2);
    REQUIRE(list.Get(3) == 4);
    REQUIRE(list.Get(4) == 5);
}

TEST_CASE("Двусвязный список 10.2: Set с неверным индексом"){
    int temp[] = {1, 2, 3};
    LinkedList<int> list(temp, 3);
    
    REQUIRE_THROWS_AS(list.Set(3, 100), std::out_of_range);
    REQUIRE_THROWS_AS(list.Set(100, 100), std::out_of_range);
}

TEST_CASE("Двусвязный список 11.1: RemoveAt из начала"){
    int temp[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(temp, 5);
    
    list.RemoveAt(0);
    
    REQUIRE(list.GetLength() == 4);
    REQUIRE(list.GetFirst() == 2);
    REQUIRE(list.Get(0) == 2);
    REQUIRE(list.Get(1) == 3);
    REQUIRE(list.Get(2) == 4);
    REQUIRE(list.Get(3) == 5);
}

TEST_CASE("Двусвязный список 11.2: RemoveAt из середины"){
    int temp[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(temp, 5);
    
    list.RemoveAt(2);
    
    REQUIRE(list.GetLength() == 4);
    REQUIRE(list.Get(0) == 1);
    REQUIRE(list.Get(1) == 2);
    REQUIRE(list.Get(2) == 4);
    REQUIRE(list.Get(3) == 5);
}

TEST_CASE("Двусвязный список 11.3: RemoveAt из конца"){
    int temp[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(temp, 5);
    
    list.RemoveAt(4);
    
    REQUIRE(list.GetLength() == 4);
    REQUIRE(list.GetLast() == 4);
    REQUIRE(list.Get(0) == 1);
    REQUIRE(list.Get(1) == 2);
    REQUIRE(list.Get(2) == 3);
    REQUIRE(list.Get(3) == 4);
}

TEST_CASE("Двусвязный список 11.4: RemoveAt до пустого списка"){
    int temp[] = {1};
    LinkedList<int> list(temp, 1);
    
    list.RemoveAt(0);
    
    REQUIRE(list.GetLength() == 0);
    REQUIRE(list.IsEmpty() == true);
}

TEST_CASE("Двусвязный список 11.5: RemoveAt с неверным индексом"){
    int temp[] = {1, 2, 3};
    LinkedList<int> list(temp, 3);
    
    REQUIRE_THROWS_AS(list.RemoveAt(3), std::out_of_range);
    REQUIRE_THROWS_AS(list.RemoveAt(100), std::out_of_range);
}

TEST_CASE("Двусвязный список 12.1: Clear"){
    int temp[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(temp, 5);
    
    list.Clear();
    
    REQUIRE(list.GetLength() == 0);
    REQUIRE(list.IsEmpty() == true);
    REQUIRE_THROWS_AS(list.GetFirst(), std::out_of_range);
}

TEST_CASE("Двусвязный список 12.2: Clear на пустом списке"){
    LinkedList<int> list;
    
    list.Clear();
    
    REQUIRE(list.GetLength() == 0);
    REQUIRE(list.IsEmpty() == true);
}

TEST_CASE("Двусвязный список 13.1: GetSubList"){
    int temp[] = {10, 20, 30, 40, 50, 60};
    LinkedList<int> list(temp, 6);
    
    LinkedList<int>* sublist = list.GetSubList(1, 4);
    
    REQUIRE(sublist->GetLength() == 4);
    REQUIRE(sublist->Get(0) == 20);
    REQUIRE(sublist->Get(1) == 30);
    REQUIRE(sublist->Get(2) == 40);
    REQUIRE(sublist->Get(3) == 50);
    
    delete sublist;
}

TEST_CASE("Двусвязный список 13.2: GetSubList из одного элемента"){
    int temp[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(temp, 5);
    
    LinkedList<int>* sublist = list.GetSubList(2, 2);
    
    REQUIRE(sublist->GetLength() == 1);
    REQUIRE(sublist->GetFirst() == 3);
    
    delete sublist;
}

TEST_CASE("Двусвязный список 13.3: GetSubList с неверными индексами"){
    int temp[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(temp, 5);
    
    REQUIRE_THROWS_AS(list.GetSubList(3, 1), std::out_of_range);
    REQUIRE_THROWS_AS(list.GetSubList(0, 5), std::out_of_range);
    REQUIRE_THROWS_AS(list.GetSubList(2, 10), std::out_of_range);
}

TEST_CASE("Двусвязный список 14.1: Concat"){
    int temp1[] = {1, 2, 3};
    int temp2[] = {4, 5, 6};
    LinkedList<int> list1(temp1, 3);
    LinkedList<int> list2(temp2, 3);
    
    LinkedList<int>* result = list1.Concat(&list2);
    
    REQUIRE(result->GetLength() == 6);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 2);
    REQUIRE(result->Get(2) == 3);
    REQUIRE(result->Get(3) == 4);
    REQUIRE(result->Get(4) == 5);
    REQUIRE(result->Get(5) == 6);
    
    delete result;
}

TEST_CASE("Двусвязный список 14.2:  Concat с пустым списком"){
    int temp[] = {1, 2, 3};
    LinkedList<int> list1(temp, 3);
    LinkedList<int> list2;
    
    LinkedList<int>* result = list1.Concat(&list2);
    
    REQUIRE(result->GetLength() == 3);
    REQUIRE(result->Get(0) == 1);
    REQUIRE(result->Get(1) == 2);
    REQUIRE(result->Get(2) == 3);
    
    delete result;
}