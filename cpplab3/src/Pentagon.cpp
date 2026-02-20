#include "../include/Pentagon.h"
#include <cmath>
#include <sstream>

Pentagon::Pentagon() : side_length(0) {
    calculateVertices();
}

Pentagon::Pentagon(double side) : side_length(side) {
    if (side <= 0) {
        throw std::invalid_argument("Side length must be positive");
    }
    calculateVertices();
}

Pentagon::Pentagon(const Pentagon& other) : side_length(other.side_length) {
    vertices = other.vertices;
}

Pentagon::Pentagon(Pentagon&& other) noexcept : side_length(other.side_length) {
    vertices = std::move(other.vertices);
    other.side_length = 0;
}

std::pair<double, double> Pentagon::center() const {
    double x_sum = 0, y_sum = 0;
    for (const auto& vertex : vertices) {
        x_sum += vertex.first;
        y_sum += vertex.second;
    }
    return {x_sum / 5.0, y_sum / 5.0};
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon vertices:";
    for (const auto& vertex : vertices) {
        os << " (" << vertex.first << ", " << vertex.second << ")";
    }
}

void Pentagon::read(std::istream& is) {
    double side;
    if (is >> side) {
        if (side <= 0) {
            throw std::invalid_argument("Side length must be positive");
        }
        side_length = side;
        calculateVertices();
    }
}

Pentagon::operator double() const {
    return area();
}

double Pentagon::area() const {
    return (5.0 * side_length * side_length) / (4.0 * std::tan(M_PI / 5.0));
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* pentagon = dynamic_cast<const Pentagon*>(&other);
    if (!pentagon) return false;
    return std::abs(side_length - pentagon->side_length) < 1e-9;
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this != &other) {
        side_length = other.side_length;
        vertices = other.vertices;
    }
    return *this;
}

Figure& Pentagon::operator=(const Figure& other) {
    const Pentagon* pentagon = dynamic_cast<const Pentagon*>(&other);
    if (pentagon) {
        side_length = pentagon->side_length;
        vertices = pentagon->vertices;
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        side_length = other.side_length;
        vertices = std::move(other.vertices);
        other.side_length = 0;
    }
    return *this;
}

void Pentagon::calculateVertices() {
    vertices.clear();
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        double x = side_length * std::cos(angle);
        double y = side_length * std::sin(angle);
        vertices.emplace_back(x, y);
    }
}