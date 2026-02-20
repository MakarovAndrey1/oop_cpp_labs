#ifndef OCTAGON_H
#define OCTAGON_H

#include "Figure.h"

class Octagon : public Figure {
public:
    Octagon();
    explicit Octagon(double side);
    Octagon(const Octagon& other);
    Octagon(Octagon&& other) noexcept;
    ~Octagon() override = default;
    
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    double area() const override;
    
    bool operator==(const Figure& other) const override;
    
    Octagon& operator=(const Octagon& other);
    Figure& operator=(const Figure& other) override;
    Octagon& operator=(Octagon&& other) noexcept;
    
    double getSide() const { return side_length; }
    
private:
    double side_length;
    void calculateVertices();
};

#endif