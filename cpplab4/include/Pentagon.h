#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <cmath>
#include <stdexcept>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template<typename T>
class Pentagon : public Figure<T> {
private:
    T side_;
    
    void calculateVertices() {
        this->vertices_.clear();
        
        for (int i = 0; i < 5; ++i) {
            double angle = 2 * M_PI * i / 5 - M_PI / 2;
            T x = static_cast<T>(side_ * std::cos(angle));
            T y = static_cast<T>(side_ * std::sin(angle));
            this->vertices_.push_back(this->createPoint(x, y));
        }
    }
    
public:
    Pentagon() : side_(0) {
        calculateVertices();
    }
    
    Pentagon(T side) : side_(side) {
        if (side <= 0) {
            throw std::invalid_argument("Side must be positive");
        }
        calculateVertices();
    }
    
    Pentagon(const Pentagon<T>& other) : side_(other.side_) {
        this->vertices_.clear();
        for (const auto& vertex : other.vertices_) {
            this->vertices_.push_back(this->createPoint(vertex->x(), vertex->y()));
        }
    }
    
    Pentagon(Pentagon<T>&& other) noexcept : side_(other.side_) {
        this->vertices_ = std::move(other.vertices_);
        other.side_ = 0;
    }
    
    ~Pentagon() override = default;
    
    Point<T> center() const override {
        return Point<T>(0, 0);
    }
    
    double area() const override {
        double side_d = static_cast<double>(side_);
        return (5.0 * side_d * side_d) / (4.0 * std::tan(M_PI / 5.0));
    }
    
    void print(std::ostream& os) const override {
        os << "Pentagon[";
        for (size_t i = 0; i < this->vertices_.size(); ++i) {
            os << " " << *this->vertices_[i];
        }
        os << " ] (side: " << side_ << ")";
    }
    
    void read(std::istream& is) override {
        is >> side_;
        
        if (side_ <= 0) {
            throw std::invalid_argument("Side must be positive");
        }
        calculateVertices();
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Pentagon<T>* pentagon = dynamic_cast<const Pentagon<T>*>(&other);
        if (!pentagon) return false;
        
        return side_ == pentagon->side_;
    }
    
    Pentagon<T>& operator=(const Figure<T>& other) override {
        const Pentagon<T>* pentagon = dynamic_cast<const Pentagon<T>*>(&other);
        if (pentagon) {
            side_ = pentagon->side_;
            
            this->vertices_.clear();
            for (const auto& vertex : pentagon->vertices_) {
                this->vertices_.push_back(this->createPoint(vertex->x(), vertex->y()));
            }
        }
        return *this;
    }
    
    Pentagon<T>& operator=(const Pentagon<T>& other) {
        if (this != &other) {
            side_ = other.side_;
            
            this->vertices_.clear();
            for (const auto& vertex : other.vertices_) {
                this->vertices_.push_back(this->createPoint(vertex->x(), vertex->y()));
            }
        }
        return *this;
    }
    
    Pentagon<T>& operator=(Pentagon<T>&& other) noexcept {
        if (this != &other) {
            side_ = other.side_;
            this->vertices_ = std::move(other.vertices_);
            other.side_ = 0;
        }
        return *this;
    }
    
    T side() const { return side_; }
};

#endif