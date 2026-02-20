#ifndef POINT_H
#define POINT_H

#include "concepts.h"
#include <memory>
#include <iostream>
#include <cmath>

template<typename T>
class Point {
private:
    T x_, y_;

public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}
    
    T x() const { return x_; }
    T y() const { return y_; }
    
    void setX(T x) { x_ = x; }
    void setY(T y) { y_ = y; }
    
    double distanceTo(const Point<T>& other) const {
        double dx = static_cast<double>(x_ - other.x_);
        double dy = static_cast<double>(y_ - other.y_);
        return std::sqrt(dx * dx + dy * dy);
    }
    
    bool operator==(const Point<T>& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
    
    Point<T> operator+(const Point<T>& other) const {
        return Point<T>(x_ + other.x_, y_ + other.y_);
    }
    
    Point<T> operator-(const Point<T>& other) const {
        return Point<T>(x_ - other.x_, y_ - other.y_);
    }
    
    Point<T> operator*(T scalar) const {
        return Point<T>(x_ * scalar, y_ * scalar);
    }
    
    Point<T> operator/(T scalar) const {
        return Point<T>(x_ / scalar, y_ / scalar);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point<T>& point) {
        os << "(" << point.x_ << ", " << point.y_ << ")";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Point<T>& point) {
        is >> point.x_ >> point.y_;
        return is;
    }
};

template<typename T>
using PointPtr = std::unique_ptr<Point<T>>;

#endif