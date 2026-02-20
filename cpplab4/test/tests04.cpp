#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <cmath>
#include "../include/Point.h"
#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include "../include/Array.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Алиасы для удобства
using TrapezoidD = Trapezoid<double>;
using RhombusD = Rhombus<double>;
using PentagonD = Pentagon<double>;

// Тесты для Point
TEST(PointTest, ConstructionAndAccessors) {
    Point<double> p1;
    EXPECT_DOUBLE_EQ(p1.x(), 0.0);
    EXPECT_DOUBLE_EQ(p1.y(), 0.0);
    
    Point<double> p2(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p2.x(), 3.5);
    EXPECT_DOUBLE_EQ(p2.y(), 4.2);
    
    p2.setX(1.0);
    p2.setY(2.0);
    EXPECT_DOUBLE_EQ(p2.x(), 1.0);
    EXPECT_DOUBLE_EQ(p2.y(), 2.0);
}

TEST(PointTest, Operations) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(3.0, 4.0);
    
    auto p3 = p1 + p2;
    EXPECT_DOUBLE_EQ(p3.x(), 4.0);
    EXPECT_DOUBLE_EQ(p3.y(), 6.0);
    
    auto p4 = p1 - p2;
    EXPECT_DOUBLE_EQ(p4.x(), -2.0);
    EXPECT_DOUBLE_EQ(p4.y(), -2.0);
    
    auto p5 = p1 * 2.0;
    EXPECT_DOUBLE_EQ(p5.x(), 2.0);
    EXPECT_DOUBLE_EQ(p5.y(), 4.0);
    
    auto p6 = p2 / 2.0;
    EXPECT_DOUBLE_EQ(p6.x(), 1.5);
    EXPECT_DOUBLE_EQ(p6.y(), 2.0);
}

TEST(PointTest, Comparison) {
    Point<double> p1(1.0, 2.0);
    Point<double> p2(1.0, 2.0);
    Point<double> p3(2.0, 3.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, Distance) {
    Point<double> p1(0.0, 0.0);
    Point<double> p2(3.0, 4.0);
    
    EXPECT_DOUBLE_EQ(p1.distanceTo(p2), 5.0);
}

TEST(PointTest, StreamOperators) {
    Point<double> p(1.5, 2.5);
    
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "(1.5, 2.5)");
    
    Point<double> p2;
    std::stringstream ss2("3.0 4.0");
    ss2 >> p2;
    EXPECT_DOUBLE_EQ(p2.x(), 3.0);
    EXPECT_DOUBLE_EQ(p2.y(), 4.0);
}

// Тесты для Trapezoid
TEST(TrapezoidTest, Construction) {
    TrapezoidD t1;
    EXPECT_DOUBLE_EQ(t1.base1(), 0.0);
    EXPECT_DOUBLE_EQ(t1.base2(), 0.0);
    EXPECT_DOUBLE_EQ(t1.height(), 0.0);
    
    TrapezoidD t2(4.0, 6.0, 3.0);
    EXPECT_DOUBLE_EQ(t2.base1(), 4.0);
    EXPECT_DOUBLE_EQ(t2.base2(), 6.0);
    EXPECT_DOUBLE_EQ(t2.height(), 3.0);
    
    EXPECT_THROW(TrapezoidD(-1.0, 2.0, 3.0), std::invalid_argument);
    EXPECT_THROW(TrapezoidD(1.0, -2.0, 3.0), std::invalid_argument);
    EXPECT_THROW(TrapezoidD(1.0, 2.0, -3.0), std::invalid_argument);
}

TEST(TrapezoidTest, Area) {
    TrapezoidD t1(4.0, 6.0, 3.0);
    EXPECT_DOUBLE_EQ(t1.area(), 15.0); // (4+6)*3/2 = 15
    
    TrapezoidD t2(5.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(t2.area(), 16.0); // (5+3)*4/2 = 16
}

TEST(TrapezoidTest, Center) {
    TrapezoidD t1(4.0, 6.0, 3.0);
    auto center = t1.center();
    // Для равнобедренной трапеции центр по y будет на половине высоты
    EXPECT_DOUBLE_EQ(center.y(), 1.5); // height/2 = 1.5
}

TEST(TrapezoidTest, CopyAndMove) {
    TrapezoidD t1(4.0, 6.0, 3.0);
    
    // Copy constructor
    TrapezoidD t2(t1);
    EXPECT_DOUBLE_EQ(t2.area(), t1.area());
    
    // Move constructor
    TrapezoidD t3(std::move(t2));
    EXPECT_DOUBLE_EQ(t3.area(), 15.0);
    
    // Copy assignment
    TrapezoidD t4;
    t4 = t1;
    EXPECT_DOUBLE_EQ(t4.area(), 15.0);
    
    // Move assignment
    TrapezoidD t5;
    t5 = std::move(t3);
    EXPECT_DOUBLE_EQ(t5.area(), 15.0);
}

TEST(TrapezoidTest, Comparison) {
    TrapezoidD t1(4.0, 6.0, 3.0);
    TrapezoidD t2(4.0, 6.0, 3.0);
    TrapezoidD t3(3.0, 5.0, 2.0);
    
    EXPECT_TRUE(t1 == t2);
    EXPECT_FALSE(t1 == t3);
}

TEST(TrapezoidTest, StreamOperators) {
    TrapezoidD t(4.0, 6.0, 3.0);
    
    std::stringstream ss;
    t.print(ss);
    EXPECT_FALSE(ss.str().empty());
    
    TrapezoidD t2;
    std::stringstream ss2("5.0 7.0 4.0");
    ss2 >> t2;
    EXPECT_DOUBLE_EQ(t2.area(), 24.0); // (5+7)*4/2 = 24
}

TEST(TrapezoidTest, VertexCount) {
    TrapezoidD t(4.0, 6.0, 3.0);
    EXPECT_EQ(t.vertexCount(), 4);
    
    // Проверка доступа к вершинам
    for (size_t i = 0; i < t.vertexCount(); ++i) {
        EXPECT_NO_THROW(t.vertex(i));
    }
    
    EXPECT_THROW(t.vertex(4), std::out_of_range);
}

// Тесты для Rhombus
TEST(RhombusTest, Construction) {
    RhombusD r1;
    EXPECT_DOUBLE_EQ(r1.diagonal1(), 0.0);
    EXPECT_DOUBLE_EQ(r1.diagonal2(), 0.0);
    
    RhombusD r2(5.0, 8.0);
    EXPECT_DOUBLE_EQ(r2.diagonal1(), 5.0);
    EXPECT_DOUBLE_EQ(r2.diagonal2(), 8.0);
    
    EXPECT_THROW(RhombusD(-1.0, 2.0), std::invalid_argument);
    EXPECT_THROW(RhombusD(1.0, -2.0), std::invalid_argument);
}

TEST(RhombusTest, Area) {
    RhombusD r1(5.0, 8.0);
    EXPECT_DOUBLE_EQ(r1.area(), 20.0); // 5*8/2 = 20
    
    RhombusD r2(6.0, 4.0);
    EXPECT_DOUBLE_EQ(r2.area(), 12.0); // 6*4/2 = 12
}

TEST(RhombusTest, Side) {
    RhombusD r1(6.0, 8.0);
    // Сторона = sqrt((6/2)^2 + (8/2)^2) = sqrt(9 + 16) = sqrt(25) = 5
    EXPECT_DOUBLE_EQ(r1.side(), 5.0);
}

TEST(RhombusTest, Center) {
    RhombusD r1(5.0, 8.0);
    auto center = r1.center();
    EXPECT_DOUBLE_EQ(center.x(), 0.0);
    EXPECT_DOUBLE_EQ(center.y(), 0.0);
}

TEST(RhombusTest, Comparison) {
    RhombusD r1(5.0, 8.0);
    RhombusD r2(5.0, 8.0);
    RhombusD r3(4.0, 7.0);
    
    EXPECT_TRUE(r1 == r2);
    EXPECT_FALSE(r1 == r3);
}

TEST(RhombusTest, StreamOperators) {
    RhombusD r(5.0, 8.0);
    
    std::stringstream ss;
    r.print(ss);
    EXPECT_FALSE(ss.str().empty());
    
    RhombusD r2;
    std::stringstream ss2("6.0 4.0");
    ss2 >> r2;
    EXPECT_DOUBLE_EQ(r2.area(), 12.0);
}

TEST(RhombusTest, VertexCount) {
    RhombusD r(5.0, 8.0);
    EXPECT_EQ(r.vertexCount(), 4);
    
    for (size_t i = 0; i < r.vertexCount(); ++i) {
        EXPECT_NO_THROW(r.vertex(i));
    }
    
    EXPECT_THROW(r.vertex(4), std::out_of_range);
}

// Тесты для Pentagon
TEST(PentagonTest, Construction) {
    PentagonD p1;
    EXPECT_DOUBLE_EQ(p1.side(), 0.0);
    
    PentagonD p2(4.0);
    EXPECT_DOUBLE_EQ(p2.side(), 4.0);
    
    EXPECT_THROW(PentagonD(-1.0), std::invalid_argument);
}

TEST(PentagonTest, Area) {
    PentagonD p1(1.0);
    double expectedArea = (5.0 * 1.0 * 1.0) / (4.0 * std::tan(M_PI / 5.0));
    EXPECT_NEAR(p1.area(), expectedArea, 0.0001);
    
    PentagonD p2(2.0);
    expectedArea = (5.0 * 2.0 * 2.0) / (4.0 * std::tan(M_PI / 5.0));
    EXPECT_NEAR(p2.area(), expectedArea, 0.0001);
}

TEST(PentagonTest, Center) {
    PentagonD p1(4.0);
    auto center = p1.center();
    EXPECT_DOUBLE_EQ(center.x(), 0.0);
    EXPECT_DOUBLE_EQ(center.y(), 0.0);
}

TEST(PentagonTest, Comparison) {
    PentagonD p1(4.0);
    PentagonD p2(4.0);
    PentagonD p3(3.0);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PentagonTest, StreamOperators) {
    PentagonD p(4.0);
    
    std::stringstream ss;
    p.print(ss);
    EXPECT_FALSE(ss.str().empty());
    
    PentagonD p2;
    std::stringstream ss2("3.0");
    ss2 >> p2;
    EXPECT_DOUBLE_EQ(p2.side(), 3.0);
}

TEST(PentagonTest, VertexCount) {
    PentagonD p(4.0);
    EXPECT_EQ(p.vertexCount(), 5);
    
    for (size_t i = 0; i < p.vertexCount(); ++i) {
        EXPECT_NO_THROW(p.vertex(i));
    }
    
    EXPECT_THROW(p.vertex(5), std::out_of_range);
}

// Тесты для Array
TEST(ArrayTest, Construction) {
    Array<int> arr1;
    EXPECT_EQ(arr1.size(), 0);
    EXPECT_TRUE(arr1.empty());
    EXPECT_GE(arr1.capacity(), 10); // Начальная capacity
    
    Array<double> arr2(20);
    EXPECT_EQ(arr2.size(), 0);
    EXPECT_GE(arr2.capacity(), 20);
}

TEST(ArrayTest, PushBackAndAccess) {
    Array<int> arr;
    
    arr.push_back(10);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 10);
    
    arr.push_back(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    
    arr.push_back(30);
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[2], 30);
}

TEST(ArrayTest, CopySemantics) {
    Array<int> arr1;
    arr1.push_back(10);
    arr1.push_back(20);
    arr1.push_back(30);
    
    // Copy constructor
    Array<int> arr2(arr1);
    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2[0], 10);
    EXPECT_EQ(arr2[1], 20);
    EXPECT_EQ(arr2[2], 30);
    
    // Copy assignment
    Array<int> arr3;
    arr3 = arr1;
    EXPECT_EQ(arr3.size(), 3);
    EXPECT_EQ(arr3[0], 10);
    EXPECT_EQ(arr3[1], 20);
    EXPECT_EQ(arr3[2], 30);
}

TEST(ArrayTest, MoveSemantics) {
    Array<std::string> arr1;
    arr1.push_back("Hello");
    arr1.push_back("World");
    
    // Move constructor
    Array<std::string> arr2(std::move(arr1));
    EXPECT_EQ(arr2.size(), 2);
    EXPECT_EQ(arr1.size(), 0);
    EXPECT_EQ(arr2[0], "Hello");
    EXPECT_EQ(arr2[1], "World");
    
    // Move assignment
    Array<std::string> arr3;
    arr3 = std::move(arr2);
    EXPECT_EQ(arr3.size(), 2);
    EXPECT_EQ(arr2.size(), 0);
}

TEST(ArrayTest, Erase) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.push_back(40);
    
    EXPECT_EQ(arr.size(), 4);
    
    arr.erase(1); // Удаляем 20
    EXPECT_EQ(arr.size(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
    EXPECT_EQ(arr[2], 40);
    
    arr.erase(0); // Удаляем 10
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 30);
    EXPECT_EQ(arr[1], 40);
}

TEST(ArrayTest, Clear) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    
    EXPECT_EQ(arr.size(), 3);
    
    arr.clear();
    EXPECT_EQ(arr.size(), 0);
    EXPECT_TRUE(arr.empty());
}

TEST(ArrayTest, Iterators) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    
    int sum = 0;
    for (const auto& val : arr) {
        sum += val;
    }
    EXPECT_EQ(sum, 60);
    
    // Изменение через итераторы
    for (auto& val : arr) {
        val *= 2;
    }
    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[1], 40);
    EXPECT_EQ(arr[2], 60);
}

TEST(ArrayTest, OutOfRange) {
    Array<int> arr;
    arr.push_back(10);
    
    EXPECT_THROW(arr[1], std::out_of_range);
    EXPECT_THROW(arr.erase(1), std::out_of_range);
}

TEST(ArrayTest, Resize) {
    Array<int> arr;
    size_t initial_capacity = arr.capacity();
    
    // Добавляем элементы до превышения capacity
    for (int i = 0; i < initial_capacity + 5; ++i) {
        arr.push_back(i);
    }
    
    EXPECT_GT(arr.capacity(), initial_capacity);
    EXPECT_EQ(arr.size(), initial_capacity + 5);
}

// Интеграционные тесты
TEST(IntegrationTest, FigurePolymorphism) {
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push_back(std::make_shared<TrapezoidD>(4.0, 6.0, 3.0));
    figures.push_back(std::make_shared<RhombusD>(5.0, 8.0));
    figures.push_back(std::make_shared<PentagonD>(4.0));
    
    EXPECT_EQ(figures.size(), 3);
    
    double totalArea = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        totalArea += figures[i]->area();
    }
    
    double pentagonArea = (5.0 * 4.0 * 4.0) / (4.0 * std::tan(M_PI / 5.0));
    double expectedArea = 15.0 + 20.0 + pentagonArea;
    EXPECT_NEAR(totalArea, expectedArea, 0.001);
}

TEST(IntegrationTest, ArrayOfFigures) {
    Array<RhombusD> rhombuses;
    
    rhombuses.push_back(RhombusD(3.0, 4.0));
    rhombuses.push_back(RhombusD(5.0, 6.0));
    rhombuses.push_back(RhombusD(2.0, 7.0));
    
    EXPECT_EQ(rhombuses.size(), 3);
    
    double totalArea = 0;
    for (size_t i = 0; i < rhombuses.size(); ++i) {
        totalArea += rhombuses[i].area();
    }
    
    double expectedArea = 6.0 + 15.0 + 7.0; // 3*4/2=6, 5*6/2=15, 2*7/2=7
    EXPECT_DOUBLE_EQ(totalArea, expectedArea);
}

TEST(IntegrationTest, MoveFigure) {
    TrapezoidD t1(4.0, 6.0, 3.0);
    double area1 = t1.area();
    
    // Move constructor
    TrapezoidD t2(std::move(t1));
    EXPECT_DOUBLE_EQ(t2.area(), area1);
    
    // Move assignment
    TrapezoidD t3;
    t3 = std::move(t2);
    EXPECT_DOUBLE_EQ(t3.area(), area1);
}

TEST(IntegrationTest, DifferentScalarTypes) {
    // Тестирование с разными скалярными типами
    Trapezoid<float> t_float(4.0f, 6.0f, 3.0f);
    EXPECT_FLOAT_EQ(t_float.area(), 15.0f);
    
    Trapezoid<int> t_int(4, 6, 3);
    EXPECT_DOUBLE_EQ(t_int.area(), 15.0);
}

TEST(IntegrationTest, FigureConversionOperator) {
    PentagonD p(2.0);
    double area = p.area();
    
    // Тестирование оператора преобразования в double
    double converted = static_cast<double>(p);
    EXPECT_DOUBLE_EQ(converted, area);
}

TEST(IntegrationTest, ComplexFigureOperations) {
    // Создаем массив разных фигур
    Array<std::shared_ptr<Figure<double>>> figures;
    
    figures.push_back(std::make_shared<TrapezoidD>(3.0, 5.0, 4.0));  // area = 16
    figures.push_back(std::make_shared<RhombusD>(4.0, 6.0));          // area = 12
    figures.push_back(std::make_shared<PentagonD>(3.0));             // area ~ 15.48
    
    // Тестируем операции с центром
    for (size_t i = 0; i < figures.size(); ++i) {
        auto center = figures[i]->center();
        EXPECT_NO_THROW(figures[i]->vertex(0)); // Проверяем доступ к вершинам
    }
    
    // Тестируем удаление
    figures.erase(1);
    EXPECT_EQ(figures.size(), 2);
    
    // Добавляем новую фигуру
    figures.push_back(std::make_shared<RhombusD>(2.0, 3.0));
    EXPECT_EQ(figures.size(), 3);
}


TEST(EdgeCaseTest, VerySmallDimensions) {
    TrapezoidD t(0.001, 0.002, 0.001);
    EXPECT_GT(t.area(), 0.0);
    
    RhombusD r(0.001, 0.001);
    EXPECT_GT(r.area(), 0.0);
    
    PentagonD p(0.001);
    EXPECT_GT(p.area(), 0.0);
}

TEST(EdgeCaseTest, LargeDimensions) {
    TrapezoidD t(1000.0, 2000.0, 500.0);
    EXPECT_DOUBLE_EQ(t.area(), 750000.0); // (1000+2000)*500/2
    
    RhombusD r(1000.0, 2000.0);
    EXPECT_DOUBLE_EQ(r.area(), 1000000.0); // 1000*2000/2
    
    PentagonD p(1000.0);
    double expectedArea = (5.0 * 1000.0 * 1000.0) / (4.0 * std::tan(M_PI / 5.0));
    EXPECT_NEAR(p.area(), expectedArea, 0.001);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
