#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include <cmath>
#include <stdexcept>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template<typename T>
class Rhombus : public Figure<T> {
private:
    T diagonal1_, diagonal2_;
    
    void calculateVertices() {
        this->vertices_.clear();
        
        this->vertices_.push_back(this->createPoint(diagonal1_ / 2, 0));
        this->vertices_.push_back(this->createPoint(0, diagonal2_ / 2));
        this->vertices_.push_back(this->createPoint(-diagonal1_ / 2, 0));
        this->vertices_.push_back(this->createPoint(0, -diagonal2_ / 2));
    }
    
public:
    Rhombus() : diagonal1_(0), diagonal2_(0) {
        calculateVertices();
    }
    
    Rhombus(T d1, T d2) : diagonal1_(d1), diagonal2_(d2) {
        if (d1 <= 0 || d2 <= 0) {
            throw std::invalid_argument("Diagonals must be positive");
        }
        calculateVertices();
    }
    
    Rhombus(const Rhombus<T>& other) 
        : diagonal1_(other.diagonal1_), diagonal2_(other.diagonal2_) {
        
        this->vertices_.clear();
        for (const auto& vertex : other.vertices_) {
            this->vertices_.push_back(this->createPoint(vertex->x(), vertex->y()));
        }
    }
    
    Rhombus(Rhombus<T>&& other) noexcept 
        : diagonal1_(other.diagonal1_), diagonal2_(other.diagonal2_) {
        
        this->vertices_ = std::move(other.vertices_);
        other.diagonal1_ = other.diagonal2_ = 0;
    }
    
    ~Rhombus() override = default;
    
    Point<T> center() const override {
        return Point<T>(0, 0);
    }
    
    double area() const override {
        return static_cast<double>(diagonal1_) * static_cast<double>(diagonal2_) / 2.0;
    }
    
    void print(std::ostream& os) const override {
        os << "Rhombus[";
        for (size_t i = 0; i < this->vertices_.size(); ++i) {
            os << " " << *this->vertices_[i];
        }
        os << " ] (diagonals: " << diagonal1_ << ", " << diagonal2_ << ")";
    }
    
    void read(std::istream& is) override {
        is >> diagonal1_ >> diagonal2_;
        
        if (diagonal1_ <= 0 || diagonal2_ <= 0) {
            throw std::invalid_argument("Diagonals must be positive");
        }
        calculateVertices();
    }
    
    bool operator==(const Figure<T>& other) const override {
        const Rhombus<T>* rhombus = dynamic_cast<const Rhombus<T>*>(&other);
        if (!rhombus) return false;
        
        return diagonal1_ == rhombus->diagonal1_ && 
               diagonal2_ == rhombus->diagonal2_;
    }
    
    Rhombus<T>& operator=(const Figure<T>& other) override {
        const Rhombus<T>* rhombus = dynamic_cast<const Rhombus<T>*>(&other);
        if (rhombus) {
            diagonal1_ = rhombus->diagonal1_;
            diagonal2_ = rhombus->diagonal2_;
            
            this->vertices_.clear();
            for (const auto& vertex : rhombus->vertices_) {
                this->vertices_.push_back(this->createPoint(vertex->x(), vertex->y()));
            }
        }
        return *this;
    }
    
    Rhombus<T>& operator=(const Rhombus<T>& other) {
        if (this != &other) {
            diagonal1_ = other.diagonal1_;
            diagonal2_ = other.diagonal2_;
            
            this->vertices_.clear();
            for (const auto& vertex : other.vertices_) {
                this->vertices_.push_back(this->createPoint(vertex->x(), vertex->y()));
            }
        }
        return *this;
    }
    
    Rhombus<T>& operator=(Rhombus<T>&& other) noexcept {
        if (this != &other) {
            diagonal1_ = other.diagonal1_;
            diagonal2_ = other.diagonal2_;
            this->vertices_ = std::move(other.vertices_);
            
            other.diagonal1_ = other.diagonal2_ = 0;
        }
        return *this;
    }
    
    T diagonal1() const { return diagonal1_; }
    T diagonal2() const { return diagonal2_; }
    
    double side() const {
        double d1_half = static_cast<double>(diagonal1_) / 2.0;
        double d2_half = static_cast<double>(diagonal2_) / 2.0;
        return std::sqrt(d1_half * d1_half + d2_half * d2_half);
    }
};

#endif