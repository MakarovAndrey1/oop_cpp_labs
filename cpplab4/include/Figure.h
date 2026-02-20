#ifndef FIGURE_H
#define FIGURE_H

#include "Point.h"
#include "concepts.h"
#include <vector>
#include <memory>
#include <iostream>

template<typename T>
class Figure {
protected:
    std::vector<PointPtr<T>> vertices_;
    
public:
    virtual ~Figure() = default;
    
    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual Figure<T>& operator=(const Figure<T>& other) = 0;
    
    virtual operator double() const {
        return area();
    }
    
    size_t vertexCount() const { return vertices_.size(); }
    
    const Point<T>& vertex(size_t index) const {
        if (index >= vertices_.size()) {
            throw std::out_of_range("Vertex index out of range");
        }
        return *vertices_[index];
    }
    
    PointPtr<T> createPoint(T x, T y) {
        return std::make_unique<Point<T>>(x, y);
    }
    
    bool isValidVertexIndex(size_t index) const {
        return index < vertices_.size();
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
    figure.print(os);
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Figure<T>& figure) {
    figure.read(is);
    return is;
}

#endif