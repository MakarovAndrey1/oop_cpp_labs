#include "../include/Octagon.h"
#include <cmath>
#include <sstream>

Octagon::Octagon() : side_length(0) {
    calculateVertices();
}

Octagon::Octagon(double side) : side_length(side) {
    if (side <= 0) {
        throw std::invalid_argument("Side length must be positive");
    }
    calculateVertices();
}

Octagon::Octagon(const Octagon& other) : side_length(other.side_length) {
    vertices = other.vertices;
}

Octagon::Octagon(Octagon&& other) noexcept : side_length(other.side_length) {
    vertices = std::move(other.vertices);
    other.side_length = 0;
}

std::pair<double, double> Octagon::center() const {
    double x_sum = 0, y_sum = 0;
    for (const auto& vertex : vertices) {
        x_sum += vertex.first;
        y_sum += vertex.second;
    }
    return {x_sum / 8.0, y_sum / 8.0};
}

void Octagon::print(std::ostream& os) const {
    os << "Octagon vertices:";
    for (const auto& vertex : vertices) {
        os << " (" << vertex.first << ", " << vertex.second << ")";
    }
}

void Octagon::read(std::istream& is) {
    double side;
    if (is >> side) {
        if (side <= 0) {
            throw std::invalid_argument("Side length must be positive");
        }
        side_length = side;
        calculateVertices();
    }
}

Octagon::operator double() const {
    return area();
}

double Octagon::area() const {
    return 2.0 * (1.0 + std::sqrt(2.0)) * side_length * side_length;
}

bool Octagon::operator==(const Figure& other) const {
    const Octagon* octagon = dynamic_cast<const Octagon*>(&other);
    if (!octagon) return false;
    return std::abs(side_length - octagon->side_length) < 1e-9;
}

Octagon& Octagon::operator=(const Octagon& other) {
    if (this != &other) {
        side_length = other.side_length;
        vertices = other.vertices;
    }
    return *this;
}

Figure& Octagon::operator=(const Figure& other) {
    const Octagon* octagon = dynamic_cast<const Octagon*>(&other);
    if (octagon) {
        side_length = octagon->side_length;
        vertices = octagon->vertices;
    }
    return *this;
}

Octagon& Octagon::operator=(Octagon&& other) noexcept {
    if (this != &other) {
        side_length = other.side_length;
        vertices = std::move(other.vertices);
        other.side_length = 0;
    }
    return *this;
}

void Octagon::calculateVertices() {
    vertices.clear();
    for (int i = 0; i < 8; ++i) {
        double angle = 2 * M_PI * i / 8;
        double x = side_length * std::cos(angle);
        double y = side_length * std::sin(angle);
        vertices.emplace_back(x, y);
    }
}