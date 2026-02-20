#ifndef HEXAGON_H
#define HEXAGON_H

#include "Figure.h"

class Hexagon : public Figure {
public:
    Hexagon();
    explicit Hexagon(double side);
    Hexagon(const Hexagon& other);
    Hexagon(Hexagon&& other) noexcept;
    ~Hexagon() override = default;
    
    std::pair<double, double> center() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    operator double() const override;
    double area() const override;
    
    bool operator==(const Figure& other) const override;
    
    Hexagon& operator=(const Hexagon& other);
    Figure& operator=(const Figure& other) override;
    Hexagon& operator=(Hexagon&& other) noexcept;
    
    double getSide() const { return side_length; }
    
private:
    double side_length;
    void calculateVertices();
};

#endif