#include "../include/Hexagon.h"
#include <cmath>
#include <sstream>

Hexagon::Hexagon() : side_length(0) {
    calculateVertices();
}

Hexagon::Hexagon(double side) : side_length(side) {
    if (side <= 0) {
        throw std::invalid_argument("Side length must be positive");
    }
    calculateVertices();
}

Hexagon::Hexagon(const Hexagon& other) : side_length(other.side_length) {
    vertices = other.vertices;
}

Hexagon::Hexagon(Hexagon&& other) noexcept : side_length(other.side_length) {
    vertices = std::move(other.vertices);
    other.side_length = 0;
}

std::pair<double, double> Hexagon::center() const {
    double x_sum = 0, y_sum = 0;
    for (const auto& vertex : vertices) {
        x_sum += vertex.first;
        y_sum += vertex.second;
    }
    return {x_sum / 6.0, y_sum / 6.0};
}

void Hexagon::print(std::ostream& os) const {
    os << "Hexagon vertices:";
    for (const auto& vertex : vertices) {
        os << " (" << vertex.first << ", " << vertex.second << ")";
    }
}

void Hexagon::read(std::istream& is) {
    double side;
    if (is >> side) {
        if (side <= 0) {
            throw std::invalid_argument("Side length must be positive");
        }
        side_length = side;
        calculateVertices();
    }
}

Hexagon::operator double() const {
    return area();
}

double Hexagon::area() const {
    return (3.0 * std::sqrt(3.0) * side_length * side_length) / 2.0;
}

bool Hexagon::operator==(const Figure& other) const {
    const Hexagon* hexagon = dynamic_cast<const Hexagon*>(&other);
    if (!hexagon) return false;
    return std::abs(side_length - hexagon->side_length) < 1e-9;
}

Hexagon& Hexagon::operator=(const Hexagon& other) {
    if (this != &other) {
        side_length = other.side_length;
        vertices = other.vertices;
    }
    return *this;
}

Figure& Hexagon::operator=(const Figure& other) {
    const Hexagon* hexagon = dynamic_cast<const Hexagon*>(&other);
    if (hexagon) {
        side_length = hexagon->side_length;
        vertices = hexagon->vertices;
    }
    return *this;
}

Hexagon& Hexagon::operator=(Hexagon&& other) noexcept {
    if (this != &other) {
        side_length = other.side_length;
        vertices = std::move(other.vertices);
        other.side_length = 0;
    }
    return *this;
}

void Hexagon::calculateVertices() {
    vertices.clear();
    for (int i = 0; i < 6; ++i) {
        double angle = 2 * M_PI * i / 6;
        double x = side_length * std::cos(angle);
        double y = side_length * std::sin(angle);
        vertices.emplace_back(x, y);
    }
}