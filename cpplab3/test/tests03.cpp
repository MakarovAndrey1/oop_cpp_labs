#include <gtest/gtest.h>
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include "../include/Octagon.h"
#include "../include/Array.h"

TEST(PentagonTest, AreaCalculation) {
    Pentagon p(5.0);
    double expected = (5.0 * 5.0 * 5.0) / (4.0 * std::tan(M_PI / 5.0));
    EXPECT_NEAR(static_cast<double>(p), expected, 1e-6);
    EXPECT_NEAR(p.area(), expected, 1e-6);
}

TEST(PentagonTest, CenterCalculation) {
    Pentagon p(2.0);
    auto center = p.center();
    EXPECT_NEAR(center.first, 0.0, 1e-9);
    EXPECT_NEAR(center.second, 0.0, 1e-9);
}

TEST(PentagonTest, Comparison) {
    Pentagon p1(3.0);
    Pentagon p2(3.0);
    Pentagon p3(4.0);
    
    // Проверяем через operator==
    EXPECT_TRUE(p1.operator==(p2));
    EXPECT_FALSE(p1.operator==(p3));
}

TEST(PentagonTest, CopyConstructor) {
    Pentagon p1(5.0);
    Pentagon p2(p1);
    
    EXPECT_TRUE(p1.operator==(p2));
    EXPECT_NEAR(p1.area(), p2.area(), 1e-9);
}

TEST(PentagonTest, AssignmentOperator) {
    Pentagon p1(5.0);
    Pentagon p2(2.0);
    
    p2 = p1;
    EXPECT_NEAR(p2.area(), p1.area(), 1e-9);
}

TEST(HexagonTest, AreaCalculation) {
    Hexagon h(4.0);
    double expected = (3.0 * std::sqrt(3.0) * 4.0 * 4.0) / 2.0;
    EXPECT_NEAR(static_cast<double>(h), expected, 1e-6);
}

TEST(HexagonTest, CenterCalculation) {
    Hexagon h(3.0);
    auto center = h.center();
    EXPECT_NEAR(center.first, 0.0, 1e-9);
    EXPECT_NEAR(center.second, 0.0, 1e-9);
}

TEST(OctagonTest, AreaCalculation) {
    Octagon o(3.0);
    double expected = 2.0 * (1.0 + std::sqrt(2.0)) * 3.0 * 3.0;
    EXPECT_NEAR(static_cast<double>(o), expected, 1e-6);
}

TEST(ArrayTest, AddAndRemoveFigures) {
    Array array;
    
    EXPECT_EQ(array.size(), 0);
    
    array.addFigure(std::make_shared<Pentagon>(2.0));
    EXPECT_EQ(array.size(), 1);
    
    array.addFigure(std::make_shared<Hexagon>(3.0));
    EXPECT_EQ(array.size(), 2);
    
    array.removeFigure(0);
    EXPECT_EQ(array.size(), 1);
}

TEST(ArrayTest, TotalArea) {
    Array array;
    
    array.addFigure(std::make_shared<Pentagon>(1.0));
    array.addFigure(std::make_shared<Hexagon>(1.0));
    array.addFigure(std::make_shared<Octagon>(1.0));
    
    double total = array.totalArea();
    EXPECT_GT(total, 0.0);
}

TEST(ArrayTest, GetFigure) {
    Array array;
    auto pentagon = std::make_shared<Pentagon>(5.0);
    
    array.addFigure(pentagon);
    
    auto retrieved = array.getFigure(0);
    EXPECT_NE(retrieved, nullptr);
    
    auto invalid = array.getFigure(10);
    EXPECT_EQ(invalid, nullptr);
}

TEST(FigureTest, StreamOperators) {
    Pentagon p(3.0);
    
    std::stringstream ss;
    ss << p;  // operator<<
    EXPECT_FALSE(ss.str().empty());
    
    Pentagon p2;
    std::stringstream ss2("2.5");
    ss2 >> p2;  // operator>>
    EXPECT_NEAR(p2.getSide(), 2.5, 1e-9);
}

TEST(FigureTest, DifferentTypesNotEqual) {
    Pentagon p(5.0);
    Hexagon h(5.0);
    
    // Фигуры разных типов не равны
    EXPECT_FALSE(p.operator==(h));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}