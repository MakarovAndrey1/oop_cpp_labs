#include "../include/Array.h"
#include <iostream>
#include <iomanip>

void Array::addFigure(std::shared_ptr<Figure> figure) {
    figures.push_back(figure);
}

void Array::removeFigure(size_t index) {
    if (index < figures.size()) {
        figures.erase(figures.begin() + index);
    }
}

double Array::totalArea() const {
    double total = 0.0;
    for (const auto& figure : figures) {
        total += figure->area();
    }
    return total;
}

void Array::printAll() const {
    std::cout << std::fixed << std::setprecision(3);
    
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Figure #" << i + 1 << ":\n";
        std::cout << "  Vertices: " << *figures[i] << "\n";
        
        auto center = figures[i]->center();
        std::cout << "  Center: (" << center.first << ", " << center.second << ")\n";
        
        std::cout << "  Area: " << figures[i]->area() << "\n";
        std::cout << std::string(30, '-') << "\n";
    }
}

size_t Array::size() const {
    return figures.size();
}

std::shared_ptr<Figure> Array::getFigure(size_t index) const {
    if (index < figures.size()) {
        return figures[index];
    }
    return nullptr;
}

void Array::clear() {
    figures.clear();
}