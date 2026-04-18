#include "catch.hpp"
#include "../Error.hpp"
#include "../Quete.hpp"
#include "../ArraySequence.hpp"
#include "../ListSequence.hpp"
#include <string>

bool IsEven(const int& x) {
    return x % 2 == 0;
}

bool IsPositive(const int& x) {
    return x > 0;
}

bool IsGreaterThan5(const int& x) {
    return x > 5;
}

int DoubleValue(const int& x) {
    return x * 2;
}

int Sum(const int& a, const int& b) {
    return a + b;
}

TEST_CASE("Queue: конструктор по умолчанию") {
    Quate<int, ArraySequence> queue;
    
    REQUIRE(queue.IsEmpty());
    REQUIRE(queue.GetSize() == 0);
}

TEST_CASE("Queue: конструктор копирования") {
    Quate<int, ArraySequence> original;
    original.Enqueue(1);
    original.Enqueue(2);
    original.Enqueue(3);
    
    Quate<int, ArraySequence> copy(original);
    
    REQUIRE(copy.GetSize() == 3);
    REQUIRE(copy.Peek() == 1);
    
    copy.Dequeue();
    REQUIRE(copy.GetSize() == 2);
    REQUIRE(original.GetSize() == 3);
}

TEST_CASE("Queue: конструктор от Container") {
    ArraySequence<int> seq;
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    
    Quate<int, ArraySequence> queue(seq);
    
    REQUIRE(queue.GetSize() == 3);
    REQUIRE(queue.Peek() == 1);
    REQUIRE(queue.GetData(1) == 2);
    REQUIRE(queue.GetData(2) == 3);
}

TEST_CASE("Queue: Enqueue - добавление элементов") {
    Quate<int, ArraySequence> queue;
    
    queue.Enqueue(10);
    REQUIRE(queue.GetSize() == 1);
    REQUIRE(queue.Peek() == 10);
    
    queue.Enqueue(20);
    REQUIRE(queue.GetSize() == 2);
    REQUIRE(queue.Peek() == 10);
    
    queue.Enqueue(30);
    REQUIRE(queue.GetSize() == 3);
    REQUIRE(queue.Peek() == 10);
}

TEST_CASE("Queue: Enqueue - отрицательные числа") {
    Quate<int, ArraySequence> queue;
    
    queue.Enqueue(-5);
    queue.Enqueue(-10);
    queue.Enqueue(-15);
    
    REQUIRE(queue.GetSize() == 3);
    REQUIRE(queue.Peek() == -5);
    REQUIRE(queue.GetData(1) == -10);
    REQUIRE(queue.GetData(2) == -15);
}

TEST_CASE("Queue: Enqueue - ноль") {
    Quate<int, ArraySequence> queue;
    
    queue.Enqueue(0);
    
    REQUIRE(queue.GetSize() == 1);
    REQUIRE(queue.Peek() == 0);
}

TEST_CASE("Queue: Dequeue - удаление из начала") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    
    queue.Dequeue();
    
    REQUIRE(queue.GetSize() == 2);
    REQUIRE(queue.Peek() == 20);
    REQUIRE(queue.GetData(1) == 30);
}

TEST_CASE("Queue: Dequeue - до пустой") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    
    queue.Dequeue();
    queue.Dequeue();
    queue.Dequeue();
    
    REQUIRE(queue.IsEmpty());
    REQUIRE(queue.GetSize() == 0);
}

TEST_CASE("Queue: Dequeue - единственный элемент") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(42);
    
    queue.Dequeue();
    
    REQUIRE(queue.IsEmpty());
    REQUIRE_THROWS_AS(queue.Peek(), QueueIsEmptyException);
}

TEST_CASE("Queue: Dequeue - на пустой очереди") {
    Quate<int, ArraySequence> queue;
    
    REQUIRE_THROWS_AS(queue.Dequeue(), QueueIsEmptyException);
}

TEST_CASE("Queue: Dequeue - после Enqueue/Dequeue циклов") {
    Quate<int, ArraySequence> queue;
    
    for (int i = 0; i < 100; i++) {
        queue.Enqueue(i);
    }
    
    for (int i = 0; i < 50; i++) {
        queue.Dequeue();
    }
    
    REQUIRE(queue.GetSize() == 50);
    REQUIRE(queue.Peek() == 50);
}


TEST_CASE("Queue: Peek - на пустой очереди") {
    Quate<int, ArraySequence> queue;
    
    REQUIRE_THROWS_AS(queue.Peek(), QueueIsEmptyException);
}

TEST_CASE("Queue: Peek - после Dequeue") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    
    queue.Dequeue();
    REQUIRE(queue.Peek() == 20);
    
    queue.Dequeue();
    REQUIRE(queue.Peek() == 30);
}

TEST_CASE("Queue: IsEmpty - новая очередь") {
    Quate<int, ArraySequence> queue;
    
    REQUIRE(queue.IsEmpty());
}

TEST_CASE("Queue: IsEmpty - после добавления") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    
    REQUIRE_FALSE(queue.IsEmpty());
}

TEST_CASE("Queue: IsEmpty - после добавления и удаления") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Dequeue();
    
    REQUIRE(queue.IsEmpty());
}

TEST_CASE("Queue: GetSize - динамика размера") {
    Quate<int, ArraySequence> queue;
    
    REQUIRE(queue.GetSize() == 0);
    
    queue.Enqueue(1);
    REQUIRE(queue.GetSize() == 1);
    
    queue.Enqueue(2);
    REQUIRE(queue.GetSize() == 2);
    
    queue.Dequeue();
    REQUIRE(queue.GetSize() == 1);
    
    queue.Dequeue();
    REQUIRE(queue.GetSize() == 0);
}

TEST_CASE("Queue: GetData - доступ по индексу") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    queue.Enqueue(40);
    
    REQUIRE(queue.GetData(0) == 10);
    REQUIRE(queue.GetData(1) == 20);
    REQUIRE(queue.GetData(2) == 30);
    REQUIRE(queue.GetData(3) == 40);
}

TEST_CASE("Queue: GetData - неверный индекс") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    
    REQUIRE_THROWS_AS(queue.GetData(-1), OutOfRangeException);
    REQUIRE_THROWS_AS(queue.GetData(2), OutOfRangeException);
    REQUIRE_THROWS_AS(queue.GetData(10), OutOfRangeException);
}

TEST_CASE("Queue: GetData - пустая очередь") {
    Quate<int, ArraySequence> queue;
    
    REQUIRE_THROWS_AS(queue.GetData(0), OutOfRangeException);
}

TEST_CASE("Queue: Map - удвоение чисел") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Enqueue(4);
    
    auto result = queue.Map<int>(DoubleValue);
    
    REQUIRE(result.GetSize() == 4);
    REQUIRE(result.GetData(0) == 2);
    REQUIRE(result.GetData(1) == 4);
    REQUIRE(result.GetData(2) == 6);
    REQUIRE(result.GetData(3) == 8);
}

TEST_CASE("Queue: Map - пустая очередь") {
    Quate<int, ArraySequence> queue;
    
    auto result = queue.Map<int>(DoubleValue);
    
    REQUIRE(result.GetSize() == 0);
    REQUIRE(result.IsEmpty());
}

TEST_CASE("Queue: Map - отрицательные числа") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(-1);
    queue.Enqueue(-2);
    queue.Enqueue(-3);
    
    auto result = queue.Map<int>(DoubleValue);
    
    REQUIRE(result.GetData(0) == -2);
    REQUIRE(result.GetData(1) == -4);
    REQUIRE(result.GetData(2) == -6);
}

TEST_CASE("Queue: Where - фильтрация чётных чисел") {
    Quate<int, ArraySequence> queue;
    for (int i = 1; i <= 10; i++) {
        queue.Enqueue(i);
    }
    
    auto result = queue.Where(IsEven);
    
    REQUIRE(result.GetSize() == 5);
    REQUIRE(result.GetData(0) == 2);
    REQUIRE(result.GetData(1) == 4);
    REQUIRE(result.GetData(2) == 6);
    REQUIRE(result.GetData(3) == 8);
    REQUIRE(result.GetData(4) == 10);
}

TEST_CASE("Queue: Where - фильтрация чисел больше 5") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(6);
    queue.Enqueue(3);
    queue.Enqueue(8);
    queue.Enqueue(2);
    queue.Enqueue(9);
    
    auto result = queue.Where(IsGreaterThan5);
    
    REQUIRE(result.GetSize() == 3);
    REQUIRE(result.GetData(0) == 6);
    REQUIRE(result.GetData(1) == 8);
    REQUIRE(result.GetData(2) == 9);
}

TEST_CASE("Queue: Where - пустая очередь") {
    Quate<int, ArraySequence> queue;
    
    auto result = queue.Where(IsEven);
    
    REQUIRE(result.GetSize() == 0);
}

TEST_CASE("Queue: Where - все элементы подходят") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(2);
    queue.Enqueue(4);
    queue.Enqueue(6);
    
    auto result = queue.Where(IsEven);
    
    REQUIRE(result.GetSize() == 3);
    REQUIRE(result.GetData(0) == 2);
    REQUIRE(result.GetData(1) == 4);
    REQUIRE(result.GetData(2) == 6);
}

TEST_CASE("Queue: Where - ни один элемент не подходит") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(3);
    queue.Enqueue(5);
    
    auto result = queue.Where(IsEven);
    
    REQUIRE(result.GetSize() == 0);
}

TEST_CASE("Queue: Reduce - сумма элементов") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Enqueue(4);
    queue.Enqueue(5);
    
    int sum = queue.Reduce(Sum);
    
    REQUIRE(sum == 15);
}

TEST_CASE("Queue: Reduce - один элемент") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(42);
    
    int sum = queue.Reduce(Sum);
    
    REQUIRE(sum == 42);
}

TEST_CASE("Queue: Reduce - отрицательные числа") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(-5);
    queue.Enqueue(-10);
    queue.Enqueue(-15);
    
    int sum = queue.Reduce(Sum);
    
    REQUIRE(sum == -30);
}

TEST_CASE("Queue: Concat - объединение двух очередей") {
    Quate<int, ArraySequence> q1;
    q1.Enqueue(1);
    q1.Enqueue(2);
    q1.Enqueue(3);
    
    Quate<int, ArraySequence> q2;
    q2.Enqueue(4);
    q2.Enqueue(5);
    q2.Enqueue(6);
    
    Quate<int, ArraySequence> result = q1.Concat(q2);
    
    REQUIRE(result.GetSize() == 6);
    REQUIRE(result.GetData(0) == 1);
    REQUIRE(result.GetData(1) == 2);
    REQUIRE(result.GetData(2) == 3);
    REQUIRE(result.GetData(3) == 4);
    REQUIRE(result.GetData(4) == 5);
    REQUIRE(result.GetData(5) == 6);
    
    REQUIRE(q1.GetSize() == 3);
    REQUIRE(q2.GetSize() == 3);
}

TEST_CASE("Queue: Concat - первая очередь пуста") {
    Quate<int, ArraySequence> q1;
    Quate<int, ArraySequence> q2;
    q2.Enqueue(1);
    q2.Enqueue(2);
    
    Quate<int, ArraySequence> result = q1.Concat(q2);
    
    REQUIRE(result.GetSize() == 2);
    REQUIRE(result.GetData(0) == 1);
    REQUIRE(result.GetData(1) == 2);
}

TEST_CASE("Queue: Concat - вторая очередь пуста") {
    Quate<int, ArraySequence> q1;
    q1.Enqueue(1);
    q1.Enqueue(2);
    Quate<int, ArraySequence> q2;
    
    Quate<int, ArraySequence> result = q1.Concat(q2);
    
    REQUIRE(result.GetSize() == 2);
    REQUIRE(result.GetData(0) == 1);
    REQUIRE(result.GetData(1) == 2);
}

TEST_CASE("Queue: Concat - обе очереди пусты") {
    Quate<int, ArraySequence> q1;
    Quate<int, ArraySequence> q2;
    
    Quate<int, ArraySequence> result = q1.Concat(q2);
    
    REQUIRE(result.IsEmpty());
}

TEST_CASE("Queue: Clutch - сцепление (изменяет первую очередь)") {
    Quate<int, ArraySequence> q1;
    q1.Enqueue(1);
    q1.Enqueue(2);
    
    Quate<int, ArraySequence> q2;
    q2.Enqueue(3);
    q2.Enqueue(4);
    
    q1.Clutch(q2);
    
    REQUIRE(q1.GetSize() == 4);
    REQUIRE(q1.GetData(0) == 1);
    REQUIRE(q1.GetData(1) == 2);
    REQUIRE(q1.GetData(2) == 3);
    REQUIRE(q1.GetData(3) == 4);
}

TEST_CASE("Queue: Clutch - пустая вторая очередь") {
    Quate<int, ArraySequence> q1;
    q1.Enqueue(1);
    q1.Enqueue(2);
    Quate<int, ArraySequence> q2;
    
    q1.Clutch(q2);
    
    REQUIRE(q1.GetSize() == 2);
    REQUIRE(q1.GetData(0) == 1);
    REQUIRE(q1.GetData(1) == 2);
}

TEST_CASE("Queue: Clutch - пустая первая очередь") {
    Quate<int, ArraySequence> q1;
    Quate<int, ArraySequence> q2;
    q2.Enqueue(1);
    q2.Enqueue(2);
    
    q1.Clutch(q2);
    
    REQUIRE(q1.GetSize() == 2);
    REQUIRE(q1.GetData(0) == 1);
    REQUIRE(q1.GetData(1) == 2);
}


TEST_CASE("Queue: Extraction - извлечение подпоследовательности") {
    Quate<int, ArraySequence> queue;
    for (int i = 0; i < 10; i++) {
        queue.Enqueue(i);
    }
    
    Quate<int, ArraySequence> sub = queue.Extraction(2, 5);
    
    REQUIRE(sub.GetSize() == 4);
    REQUIRE(sub.GetData(0) == 2);
    REQUIRE(sub.GetData(1) == 3);
    REQUIRE(sub.GetData(2) == 4);
    REQUIRE(sub.GetData(3) == 5);
}

TEST_CASE("Queue: Extraction - извлечение одного элемента") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    
    Quate<int, ArraySequence> sub = queue.Extraction(1, 1);
    
    REQUIRE(sub.GetSize() == 1);
    REQUIRE(sub.GetData(0) == 20);
}

TEST_CASE("Queue: Extraction - вся очередь") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    
    Quate<int, ArraySequence> sub = queue.Extraction(0, 2);
    
    REQUIRE(sub.GetSize() == 3);
    REQUIRE(sub.GetData(0) == 1);
    REQUIRE(sub.GetData(1) == 2);
    REQUIRE(sub.GetData(2) == 3);
}

TEST_CASE("Queue: Extraction - начало больше конца") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    
    REQUIRE_THROWS_AS(queue.Extraction(2, 1), OutOfRangeException);
}

TEST_CASE("Queue: Extraction - неверные индексы") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    
    REQUIRE_THROWS_AS(queue.Extraction(-1, 1), OutOfRangeException);
    REQUIRE_THROWS_AS(queue.Extraction(0, 3), OutOfRangeException);
    REQUIRE_THROWS_AS(queue.Extraction(5, 6), OutOfRangeException);
}

TEST_CASE("Queue: Check - поиск подпоследовательности") {
    Quate<int, ArraySequence> queue;
    for (int i = 1; i <= 10; i++) {
        queue.Enqueue(i);
    }
    
    Quate<int, ArraySequence> pattern;
    pattern.Enqueue(3);
    pattern.Enqueue(4);
    pattern.Enqueue(5);
    
    REQUIRE(queue.Check(pattern));
}

TEST_CASE("Queue: Check - подпоследовательность не найдена") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Enqueue(4);
    queue.Enqueue(5);
    
    Quate<int, ArraySequence> pattern;
    pattern.Enqueue(2);
    pattern.Enqueue(4);
    
    REQUIRE_FALSE(queue.Check(pattern));
}

TEST_CASE("Queue: Check - пустой шаблон") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    
    Quate<int, ArraySequence> pattern;
    
    REQUIRE(queue.Check(pattern));
}

TEST_CASE("Queue: Check - шаблон длиннее очереди") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    
    Quate<int, ArraySequence> pattern;
    pattern.Enqueue(1);
    pattern.Enqueue(2);
    pattern.Enqueue(3);
    
    REQUIRE_FALSE(queue.Check(pattern));
}

TEST_CASE("Queue: Check - подпоследовательность в начале") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Enqueue(4);
    
    Quate<int, ArraySequence> pattern;
    pattern.Enqueue(1);
    pattern.Enqueue(2);
    
    REQUIRE(queue.Check(pattern));
}

TEST_CASE("Queue: Check - подпоследовательность в конце") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(2);
    queue.Enqueue(3);
    queue.Enqueue(4);
    
    Quate<int, ArraySequence> pattern;
    pattern.Enqueue(3);
    pattern.Enqueue(4);
    
    REQUIRE(queue.Check(pattern));
}

TEST_CASE("Queue: Split - разделение по чётности") {
    Quate<int, ArraySequence> queue;
    for (int i = 1; i <= 10; i++) {
        queue.Enqueue(i);
    }
    
    auto result = queue.Split(IsEven);
    
    REQUIRE(result.Que_1.GetSize() == 5);
    REQUIRE(result.Que_2.GetSize() == 5);
    
    REQUIRE(result.Que_1.GetData(0) == 2);
    REQUIRE(result.Que_1.GetData(1) == 4);
    REQUIRE(result.Que_1.GetData(2) == 6);
    REQUIRE(result.Que_1.GetData(3) == 8);
    REQUIRE(result.Que_1.GetData(4) == 10);
    
    REQUIRE(result.Que_2.GetData(0) == 1);
    REQUIRE(result.Que_2.GetData(1) == 3);
    REQUIRE(result.Que_2.GetData(2) == 5);
    REQUIRE(result.Que_2.GetData(3) == 7);
    REQUIRE(result.Que_2.GetData(4) == 9);
}

TEST_CASE("Queue: Split - все элементы в первую очередь") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(2);
    queue.Enqueue(4);
    queue.Enqueue(6);
    
    auto result = queue.Split(IsEven);
    
    REQUIRE(result.Que_1.GetSize() == 3);
    REQUIRE(result.Que_2.GetSize() == 0);
}

TEST_CASE("Queue: Split - все элементы во вторую очередь") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(1);
    queue.Enqueue(3);
    queue.Enqueue(5);
    
    auto result = queue.Split(IsEven);
    
    REQUIRE(result.Que_1.GetSize() == 0);
    REQUIRE(result.Que_2.GetSize() == 3);
}

TEST_CASE("Queue: Split - пустая очередь") {
    Quate<int, ArraySequence> queue;
    
    auto result = queue.Split(IsEven);
    
    REQUIRE(result.Que_1.IsEmpty());
    REQUIRE(result.Que_2.IsEmpty());
}

TEST_CASE("Queue: Split - разделение положительных и отрицательных") {
    Quate<int, ArraySequence> queue;
    queue.Enqueue(-5);
    queue.Enqueue(3);
    queue.Enqueue(-2);
    queue.Enqueue(7);
    queue.Enqueue(0);
    queue.Enqueue(-1);
    queue.Enqueue(4);
    
    auto result = queue.Split(IsPositive);
    
    REQUIRE(result.Que_1.GetSize() == 3);
    REQUIRE(result.Que_2.GetSize() == 4);
}

TEST_CASE("Queue: с типом double") {
    Quate<double, ArraySequence> queue;
    
    queue.Enqueue(1.5);
    queue.Enqueue(2.7);
    queue.Enqueue(3.14);
    
    REQUIRE(queue.GetSize() == 3);
    REQUIRE(queue.Peek() == Approx(1.5));
    REQUIRE(queue.GetData(1) == Approx(2.7));
    REQUIRE(queue.GetData(2) == Approx(3.14));
}

TEST_CASE("Queue: с типом string") {
    Quate<std::string, ArraySequence> queue;
    
    queue.Enqueue("first");
    queue.Enqueue("second");
    queue.Enqueue("third");
    
    REQUIRE(queue.GetSize() == 3);
    REQUIRE(queue.Peek() == "first");
    REQUIRE(queue.GetData(1) == "second");
    REQUIRE(queue.GetData(2) == "third");
}

TEST_CASE("Queue: с типом bool") {
    Quate<bool, ArraySequence> queue;
    
    queue.Enqueue(true);
    queue.Enqueue(false);
    queue.Enqueue(true);
    
    REQUIRE(queue.GetSize() == 3);
    REQUIRE(queue.Peek() == true);
    REQUIRE(queue.GetData(1) == false);
    REQUIRE(queue.GetData(2) == true);
}

TEST_CASE("Queue: с ListSequence вместо ArraySequence") {
    Quate<int, ListSequence> queue;
    
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    
    REQUIRE(queue.GetSize() == 3);
    REQUIRE(queue.Peek() == 10);
    
    queue.Dequeue();
    REQUIRE(queue.Peek() == 20);
    REQUIRE(queue.GetSize() == 2);
}

TEST_CASE("Queue: исключения при неверных операциях") {
    Quate<int, ArraySequence> queue;
    
    REQUIRE_THROWS_AS(queue.Peek(), QueueIsEmptyException);
    
    REQUIRE_THROWS_AS(queue.Dequeue(), QueueIsEmptyException);
    
    REQUIRE_THROWS_AS(queue.GetData(0), OutOfRangeException);
    
    queue.Enqueue(1);
    REQUIRE_THROWS_AS(queue.Extraction(1, 0), OutOfRangeException);
    REQUIRE_THROWS_AS(queue.Extraction(0, 1), OutOfRangeException);
}

TEST_CASE("Queue: добавление большого количества элементов") {
    Quate<int, ArraySequence> queue;
    
    for (int i = 0; i < 10000; i++) {
        queue.Enqueue(i);
    }
    
    REQUIRE(queue.GetSize() == 10000);
    REQUIRE(queue.Peek() == 0);
    REQUIRE(queue.GetData(9999) == 9999);
}

TEST_CASE("Queue: удаление всех элементов по одному") {
    Quate<int, ArraySequence> queue;
    
    for (int i = 0; i < 1000; i++) {
        queue.Enqueue(i);
    }
    
    for (int i = 0; i < 1000; i++) {
        REQUIRE(queue.Peek() == i);
        queue.Dequeue();
    }
    
    REQUIRE(queue.IsEmpty());
}