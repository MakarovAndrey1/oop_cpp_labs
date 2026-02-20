#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"

class Pentagon : public Figure {
public:
    Pentagon();
    explicit Pentagon(double side);
    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;
    ~Pentagon() override = default;
    
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    double area() const override;
    
    bool operator==(const Figure& other) const override;
    
    // Операторы присваивания
    Pentagon& operator=(const Pentagon& other);
    Figure& operator=(const Figure& other) override;
    Pentagon& operator=(Pentagon&& other) noexcept;
    
    double getSide() const { return side_length; }
    
private:
    double side_length;
    void calculateVertices();
};

#endif