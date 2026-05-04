#include "catch.hpp"
#include "../../Error.hpp"
#include "../Matrix.hpp"
#include "../ListSequence.hpp"
#include "../Complex.hpp"


TEST_CASE("Матрица: конструктор по умолчанию") {
    SquareMatrix<int, ListSequence> mat;
    REQUIRE(mat.GetSize() == 0);
}

TEST_CASE("Матрица: конструктор с размером") {
    SquareMatrix<int, ListSequence> mat(5);
    REQUIRE(mat.GetSize() == 5);
    
    REQUIRE(mat.Get(0, 0) == 0);
    REQUIRE(mat.Get(2, 2) == 0);
    REQUIRE(mat.Get(4, 4) == 0);
}

TEST_CASE("Конструктор с initializer_list") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
    REQUIRE(mat.GetSize() == 3);
    REQUIRE(mat.Get(0, 0) == 1);
    REQUIRE(mat.Get(0, 1) == 2);
    REQUIRE(mat.Get(0, 2) == 3);
    REQUIRE(mat.Get(1, 0) == 4);
    REQUIRE(mat.Get(1, 1) == 5);
    REQUIRE(mat.Get(1, 2) == 6);
    REQUIRE(mat.Get(2, 0) == 7);
    REQUIRE(mat.Get(2, 1) == 8);
    REQUIRE(mat.Get(2, 2) == 9);
}

TEST_CASE("Конструктор с initializer_list - не квадратная матрица") {
    REQUIRE_THROWS_AS((SquareMatrix<int, ListSequence>{{1, 2}, {1, 2, 3}}), MatrixSquereException);
    REQUIRE_THROWS_AS((SquareMatrix<int, ListSequence>{{1, 2, 3}, {4, 5}}), MatrixSquereException);
}

TEST_CASE("Get и Set правильные") {
    SquareMatrix<int, ListSequence> mat(3);
    
    mat.Set(0, 0, 10);
    mat.Set(1, 1, 20);
    mat.Set(2, 2, 30);
    
    REQUIRE(mat.Get(0, 0) == 10);
    REQUIRE(mat.Get(1, 1) == 20);
    REQUIRE(mat.Get(2, 2) == 30);
}

TEST_CASE("Get с неверными индексами") {
    SquareMatrix<int, ListSequence> mat(3);
    
    REQUIRE_THROWS_AS(mat.Get(3, 0), OutOfRangeException);
    REQUIRE_THROWS_AS(mat.Get(0, 3), OutOfRangeException);
    REQUIRE_THROWS_AS(mat.Get(5, 5), OutOfRangeException);
}

TEST_CASE("Set с неверными индексами") {
    SquareMatrix<int, ListSequence> mat(3);
    
    REQUIRE_THROWS_AS(mat.Set(3, 0, 10), OutOfRangeException);
    REQUIRE_THROWS_AS(mat.Set(0, 3, 10), OutOfRangeException);
    REQUIRE_THROWS_AS(mat.Set(5, 5, 10), OutOfRangeException);
}

TEST_CASE("Sum - сложение матриц") {
    SquareMatrix<int, ListSequence> mat1 = {{1, 2}, {3, 4}};
    SquareMatrix<int, ListSequence> mat2 = {{5, 6}, {7, 8}};
    
    SquareMatrix<int, ListSequence> expected = {{6, 8}, {10, 12}};
    SquareMatrix<int, ListSequence> result = mat1.Sum(mat2);
    
    REQUIRE(result == expected);
}

TEST_CASE("Sum - сложение с нулевой матрицей") {
    SquareMatrix<int, ListSequence> mat1 = {{1, 2}, {3, 4}};
    SquareMatrix<int, ListSequence> zero(2);
    
    SquareMatrix<int, ListSequence> result = mat1.Sum(zero);
    
    REQUIRE(result == mat1);
}

TEST_CASE("Sum - разные размеры матриц") {
    SquareMatrix<int, ListSequence> mat1(2);
    SquareMatrix<int, ListSequence> mat2(3);
    
    REQUIRE_THROWS_AS(mat1.Sum(mat2), MatrixSquereSizeException);
}

TEST_CASE("Multiply - умножение на скаляр") {
    SquareMatrix<int, ListSequence> mat = {{1, 2}, {3, 4}};
    SquareMatrix<int, ListSequence> expected = {{2, 4}, {6, 8}};
    
    SquareMatrix<int, ListSequence> result = mat.Multiply(2);
    
    REQUIRE(result == expected);
}

TEST_CASE("Multiply - умножение на 0") {
    SquareMatrix<int, ListSequence> mat = {{1, 2}, {3, 4}};
    SquareMatrix<int, ListSequence> expected(2);
    
    SquareMatrix<int, ListSequence> result = mat.Multiply(0);
    
    REQUIRE(result == expected);
}

TEST_CASE("Multiply - умножение на отрицательное число") {
    SquareMatrix<int, ListSequence> mat = {{1, 2}, {3, 4}};
    SquareMatrix<int, ListSequence> expected = {{-1, -2}, {-3, -4}};
    
    SquareMatrix<int, ListSequence> result = mat.Multiply(-1);
    
    REQUIRE(result == expected);
}

TEST_CASE("MultiplyRow - умножение строки на скаляр") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SquareMatrix<int, ListSequence> expected = {{2, 4, 6}, {4, 5, 6}, {7, 8, 9}};
    
    SquareMatrix<int, ListSequence> result = mat.MultiplyRow(0, 2);
    
    REQUIRE(result == expected);
}

TEST_CASE("MultiplyRow - неверный индекс строки") {
    SquareMatrix<int, ListSequence> mat(3);
    
    REQUIRE_THROWS_AS(mat.MultiplyRow(3, 2), OutOfRangeException);
}

TEST_CASE("MultiplyCol - умножение столбца на скаляр") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SquareMatrix<int, ListSequence> expected = {{2, 2, 3}, {8, 5, 6}, {14, 8, 9}};
    
    SquareMatrix<int, ListSequence> result = mat.MultiplyCol(0, 2);
    
    REQUIRE(result == expected);
}

TEST_CASE("MultiplyCol - неверный индекс столбца") {
    SquareMatrix<int, ListSequence> mat(3);
    
    REQUIRE_THROWS_AS(mat.MultiplyCol(3, 2), OutOfRangeException);
}

TEST_CASE("SumRow - сложение строк (к первой прибавляем вторую)") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SquareMatrix<int, ListSequence> expected = {{5, 7, 9}, {4, 5, 6}, {7, 8, 9}};
    
    SquareMatrix<int, ListSequence> result = mat.SumRow(0, 1, 1);
    
    REQUIRE(result == expected);
}

TEST_CASE("SumRow - сложение строк с коэффициентом") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SquareMatrix<int, ListSequence> expected = {{9, 12, 15}, {4, 5, 6}, {7, 8, 9}};
    
    SquareMatrix<int, ListSequence> result = mat.SumRow(0, 1, 2);
    
    REQUIRE(result == expected);
}

TEST_CASE("SumRow - неверные индексы строк") {
    SquareMatrix<int, ListSequence> mat(3);
    
    REQUIRE_THROWS_AS(mat.SumRow(3, 0, 1), OutOfRangeException);
    REQUIRE_THROWS_AS(mat.SumRow(0, 3, 1), OutOfRangeException);
}

TEST_CASE("SumCol - сложение столбцов") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SquareMatrix<int, ListSequence> expected = {{3, 2, 3}, {9, 5, 6}, {15, 8, 9}};
    
    SquareMatrix<int, ListSequence> result = mat.SumCol(0, 1, 1);
    
    REQUIRE(result == expected);
}

TEST_CASE("SumCol - неверные индексы столбцов") {
    SquareMatrix<int, ListSequence> mat(3);

    REQUIRE_THROWS_AS(mat.SumCol(3, 0, 1), OutOfRangeException);
    REQUIRE_THROWS_AS(mat.SumCol(0, 3, 1), OutOfRangeException);
}

TEST_CASE("SwapRow - обмен строк") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SquareMatrix<int, ListSequence> expected = {{4, 5, 6}, {1, 2, 3}, {7, 8, 9}};
    
    SquareMatrix<int, ListSequence> result = mat.SwapRow(0, 1);
    
    REQUIRE(result == expected);
}

TEST_CASE("SwapRow - обмен строк с одинаковыми индексами") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
    SquareMatrix<int, ListSequence> result = mat.SwapRow(0, 0);
    
    REQUIRE(result == mat);
}

TEST_CASE("SwapRow - неверные индексы строк") {
    SquareMatrix<int, ListSequence> mat(3);
    
    REQUIRE_THROWS_AS(mat.SwapRow(3, 0), OutOfRangeException);
    REQUIRE_THROWS_AS(mat.SwapRow(0, 3), OutOfRangeException);
}

TEST_CASE("SwapCol - обмен столбцов") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SquareMatrix<int, ListSequence> expected = {{2, 1, 3}, {5, 4, 6}, {8, 7, 9}};
    
    SquareMatrix<int, ListSequence> result = mat.SwapCol(0, 1);
    
    REQUIRE(result == expected);
}

TEST_CASE("SwapCol - обмен столбцов с одинаковыми индексами") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
    SquareMatrix<int, ListSequence> result = mat.SwapCol(0, 0);
    
    REQUIRE(result == mat);
}

TEST_CASE("SwapCol - неверные индексы столбцов") {
    SquareMatrix<int, ListSequence> mat(3);
    
    REQUIRE_THROWS_AS(mat.SwapCol(3, 0), OutOfRangeException);
    REQUIRE_THROWS_AS(mat.SwapCol(0, 3), OutOfRangeException);
}

TEST_CASE("MatrixNorm - норма матрицы (максимальный элемент)") {
    SquareMatrix<int, ListSequence> mat = {{1, -5, 3}, {4, 2, -8}, {7, 0, 6}};
    
    REQUIRE(mat.MatrixNorm() == 8);
}

TEST_CASE("MatrixNorm - все элементы положительные") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    
    REQUIRE(mat.MatrixNorm() == 9);
}

TEST_CASE("MatrixNorm - с отрицательными числами") {
    SquareMatrix<int, ListSequence> mat = {{-1, -2}, {-3, -4}};
    
    REQUIRE(mat.MatrixNorm() == 4);
}

TEST_CASE("MatrixNorm - нулевая матрица") {
    SquareMatrix<int, ListSequence> mat(3);
    
    REQUIRE(mat.MatrixNorm() == 0);
}

TEST_CASE("Оператор == - одинаковые матрицы") {
    SquareMatrix<int, ListSequence> mat1 = {{1, 2}, {3, 4}};
    SquareMatrix<int, ListSequence> mat2 = {{1, 2}, {3, 4}};
    
    REQUIRE(mat1 == mat2);
}

TEST_CASE("Оператор == - разные матрицы") {
    SquareMatrix<int, ListSequence> mat1 = {{1, 2}, {3, 4}};
    SquareMatrix<int, ListSequence> mat2 = {{1, 2}, {3, 5}};
    SquareMatrix<int, ListSequence> mat3(2);
    
    REQUIRE(mat1 != mat2);
    REQUIRE(mat1 != mat3);
}

TEST_CASE("Конструктор копирования") {
    SquareMatrix<int, ListSequence> original = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    SquareMatrix<int, ListSequence> copy(original);
    
    REQUIRE(copy == original);
    
    original.Set(0, 0, 100);
    REQUIRE(copy.Get(0, 0) == 1);
}

TEST_CASE("Матрица с типом double") {
    SquareMatrix<double, ListSequence> mat = {{1.5, 2.5}, {3.5, 4.5}};
    
    REQUIRE(mat.Get(0, 0) == Approx(1.5));
    REQUIRE(mat.Get(0, 1) == Approx(2.5));
    
    auto result = mat.Multiply(2.0);
    REQUIRE(result.Get(0, 0) == Approx(3.0));
}

TEST_CASE("Matrix: оператор () для доступа и изменения элементов") {
    SquareMatrix<int, ListSequence> mat(3);
    
    mat(0, 0) = 1;
    mat(0, 1) = 2;
    mat(0, 2) = 3;
    mat(1, 0) = 4;
    mat(1, 1) = 5;
    mat(1, 2) = 6;
    mat(2, 0) = 7;
    mat(2, 1) = 8;
    mat(2, 2) = 9;
    
    REQUIRE(mat(0, 0) == 1);
    REQUIRE(mat(0, 1) == 2);
    REQUIRE(mat(0, 2) == 3);
    REQUIRE(mat(1, 0) == 4);
    REQUIRE(mat(1, 1) == 5);
    REQUIRE(mat(1, 2) == 6);
    REQUIRE(mat(2, 0) == 7);
    REQUIRE(mat(2, 1) == 8);
    REQUIRE(mat(2, 2) == 9);
}

TEST_CASE("Matrix: оператор () для комплексных чисел") {
    SquareMatrix<Complex<double>, ListSequence> mat(3);

    mat(0, 0) = Complex<double>(1, 1);
    mat(0, 1) = Complex<double>(2, 0);
    mat(0, 2) = Complex<double>(3, -1);
    mat(1, 0) = Complex<double>(0, 2);
    mat(1, 1) = Complex<double>(5, 0);
    mat(1, 2) = Complex<double>(1, 1);
    mat(2, 0) = Complex<double>(2, 2);
    mat(2, 1) = Complex<double>(0, 0);
    mat(2, 2) = Complex<double>(4, -1);
    
    REQUIRE(mat(0, 0).GetRe() == 1);
    REQUIRE(mat(0, 0).GetIm() == 1);
    REQUIRE(mat(0, 1).GetRe() == 2);
    REQUIRE(mat(0, 1).GetIm() == 0);
    REQUIRE(mat(0, 2).GetRe() == 3);
    REQUIRE(mat(0, 2).GetIm() == -1);
    REQUIRE(mat(1, 0).GetRe() == 0);
    REQUIRE(mat(1, 0).GetIm() == 2);
    REQUIRE(mat(1, 1).GetRe() == 5);
    REQUIRE(mat(1, 1).GetIm() == 0);
    REQUIRE(mat(2, 2).GetRe() == 4);
    REQUIRE(mat(2, 2).GetIm() == -1);
}

TEST_CASE("Matrix: оператор () - проверка на выход за границы") {
    SquareMatrix<int, ListSequence> mat(3);
    
    REQUIRE_THROWS_AS(mat(3, 0), OutOfRangeException);
    REQUIRE_THROWS_AS(mat(0, 3), OutOfRangeException);
    REQUIRE_THROWS_AS(mat(5, 5), OutOfRangeException);
    REQUIRE_THROWS_AS(mat(-1, 0), OutOfRangeException);
}

TEST_CASE("Matrix: оператор () - изменение существующих элементов") {
    SquareMatrix<int, ListSequence> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    mat(0, 0) = 100;
    mat(1, 1) = 200;
    mat(2, 2) = 300;
    
    REQUIRE(mat(0, 0) == 100);
    REQUIRE(mat(1, 1) == 200);
    REQUIRE(mat(2, 2) == 300);
    REQUIRE(mat(0, 1) == 2);
    REQUIRE(mat(1, 0) == 4);
}

