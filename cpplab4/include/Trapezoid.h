#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Figure.h"
#include <stdexcept>

template<typename T>
class Trapezoid : public Figure<T> {
private:
    T base1_, base2_, height_;
    
    void calculateVertices() {
        this->vertices_.clear();
        
        this->vertices_.push_back(this->createPoint(0, 0));
        this->vertices_.push_back(this->createPoint(base1_, 0));
        
        T x_offset = (base1_ - base2_) / 2;
        this->vertices_.push_back(this->createPoint(x_offset + base2_, height_));
        this->vertices_.push_back(this->createPoint(x_offset, height_));
    }
    
public:
    Trapezoid() : base1_(0), base2_(0), height_(0) {
        calculateVertices();
    }
    
    Trapezoid(T base1, T base2, T height) 
        : base1_(base1), base2_(base2), height_(height) {
        
        if (base1 <= 0 || base2 <= 0 || height <= 0) {
            throw std::invalid_argument("All dimensions must be positive");
        }
        calculateVertices();
    }
    
    Trapezoid(const Trapezoid<T>& other) 
        : base1_(other.base1_), base2_(other.base2_), height_(other.height_) {
        
        this->vertices_.clear();
        for (const auto& vertex : other.vertices_) {
            this->vertices_.push_back(this->createPoint(vertex->x(), vertex->y()));
        }
    }
    
    Trapezoid(Trapezoid<T>&& other) noexcept 
        : base1_(other.base1_), base2_(other.base2_), height_(other.height_) {
        
        this->vertices_ = std::move(other.vertices_);
        other.base1_ = other.base2_ = other.height_ = 0;
    }
    
    ~Trapezoid() override = default;
    
    Point<T> center() const override {
        T x_center = (base1_ + base2_) / 4;
        T y_center = height_ / 2;
        return Point<T>(x_center, y_center);
    }
    
    double area() const override {
        return (static_cast<double>(base1_) + static_cast<double>(base2_)) 
               * static_cast<double>(height_) / 2.0;
    }
    
    void print(std::ostream& os) const override {
        os << "Trapezoid[";
        for (size_t i = 0; i < this->vertices_.size(); ++i) {
            os << " " << *this->vertices_[i];
        }
        os << " ] (bases: " << base1_ << ", " << base2_ << ", height: " << height_ << ")";
    }
    
    void read(std::istream& is) override {
        is >> base1_ >> base2_ >> height_;
        
        if (base1_ <= 0 || base2_ <= 0 || height_ <= 0) {
            throw std::invalid_argument("All dimensions must be positive");
        }
        calculateVertices();
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Trapezoid<T>* trapezoid = dynamic_cast<const Trapezoid<T>*>(&other);
        if (!trapezoid) return false;
        
        return base1_ == trapezoid->base1_ && 
               base2_ == trapezoid->base2_ && 
               height_ == trapezoid->height_;
    }
    
    Trapezoid<T>& operator=(const Figure<T>& other) override {
        const Trapezoid<T>* trapezoid = dynamic_cast<const Trapezoid<T>*>(&other);
        if (trapezoid) {
            base1_ = trapezoid->base1_;
            base2_ = trapezoid->base2_;
            height_ = trapezoid->height_;
            
            this->vertices_.clear();
            for (const auto& vertex : trapezoid->vertices_) {
                this->vertices_.push_back(this->createPoint(vertex->x(), vertex->y()));
            }
        }
        return *this;
    }
    
    Trapezoid<T>& operator=(const Trapezoid<T>& other) {
        if (this != &other) {
            base1_ = other.base1_;
            base2_ = other.base2_;
            height_ = other.height_;
            
            this->vertices_.clear();
            for (const auto& vertex : other.vertices_) {
                this->vertices_.push_back(this->createPoint(vertex->x(), vertex->y()));
            }
        }
        return *this;
    }
    
    Trapezoid<T>& operator=(Trapezoid<T>&& other) noexcept {
        if (this != &other) {
            base1_ = other.base1_;
            base2_ = other.base2_;
            height_ = other.height_;
            this->vertices_ = std::move(other.vertices_);
            
            other.base1_ = other.base2_ = other.height_ = 0;
        }
        return *this;
    }
    
    T base1() const { return base1_; }
    T base2() const { return base2_; }
    T height() const { return height_; }
};

#endif