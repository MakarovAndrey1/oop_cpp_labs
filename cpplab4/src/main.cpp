#include "../include/Trapezoid.h"
#include "../include/Rhombus.h"
#include "../include/Pentagon.h"
#include "../include/Array.h"
#include <iostream>
#include <memory>
#include <limits>
#include <typeinfo>
#include <iomanip>

using namespace std;

// Алиасы для удобства
using TrapezoidD = Trapezoid<double>;
using RhombusD = Rhombus<double>;
using PentagonD = Pentagon<double>;

// Псевдоним для shared_ptr на фигуру
template<typename T>
using FigurePtr = shared_ptr<Figure<T>>;

void showMenu() {
    cout << "\n=== Figure Management System ===\n";
    cout << "1. Add Trapezoid\n";
    cout << "2. Add Rhombus\n";
    cout << "3. Add Pentagon\n";
    cout << "4. Show all figures\n";
    cout << "5. Remove figure by index\n";
    cout << "6. Calculate total area\n";
    cout << "7. Clear all figures\n";
    cout << "8. Demo with Array<Figure<double>*>\n";
    cout << "9. Demo with Array<Rhombus<double>>\n";
    cout << "10. Demo move semantics\n";
    cout << "11. Run tests\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
}

void demoArrayOfFigures() {
    cout << "\n=== Demo: Array<Figure<double>*> ===\n";
    
    Array<Figure<double>*> figures;
    
    // Добавляем разные фигуры
    figures.push_back(new TrapezoidD(4.0, 6.0, 3.0));
    figures.push_back(new RhombusD(5.0, 8.0));
    figures.push_back(new PentagonD(4.0));
    
    cout << "Array size: " << figures.size() << "\n";
    
    double totalArea = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << "Figure " << i + 1 << ":\n";
        figures[i]->print(cout);
        cout << "\nArea: " << figures[i]->area() << "\n";
        totalArea += figures[i]->area();
        cout << "-------------------\n";
    }
    cout << "Total area: " << totalArea << "\n";
    
    // Очистка памяти
    for (size_t i = 0; i < figures.size(); ++i) {
        delete figures[i];
    }
}

void demoArrayOfRhombuses() {
    cout << "\n=== Demo: Array<Rhombus<double>> ===\n";
    
    Array<RhombusD> rhombuses;
    
    rhombuses.push_back(RhombusD(3.0, 4.0));
    rhombuses.push_back(RhombusD(5.0, 6.0));
    rhombuses.push_back(RhombusD(2.0, 7.0));
    
    cout << "Array size: " << rhombuses.size() << "\n";
    
    double totalArea = 0;
    for (size_t i = 0; i < rhombuses.size(); ++i) {
        cout << "Rhombus " << i + 1 << ":\n";
        rhombuses[i].print(cout);
        cout << "\nArea: " << rhombuses[i].area() << "\n";
        totalArea += rhombuses[i].area();
        cout << "-------------------\n";
    }
    cout << "Total area: " << totalArea << "\n";
}

void demoMoveSemantics() {
    cout << "\n=== Demo: Move Semantics ===\n";
    
    // Создаем трапецию
    TrapezoidD t1(4.0, 6.0, 3.0);
    cout << "Original trapezoid area: " << t1.area() << "\n";
    
    // Move constructor
    TrapezoidD t2(move(t1));
    cout << "After move constructor: " << t2.area() << "\n";
    
    // Move assignment
    TrapezoidD t3;
    t3 = move(t2);
    cout << "After move assignment: " << t3.area() << "\n";
    
    // Демонстрация с массивом
    Array<TrapezoidD> trapezoids;
    trapezoids.push_back(TrapezoidD(3.0, 5.0, 4.0));
    trapezoids.push_back(TrapezoidD(2.0, 4.0, 3.0));
    
    cout << "Array capacity before resize: " << trapezoids.capacity() << "\n";
    
    // Добавляем элементы, чтобы вызвать resize
    for (int i = 0; i < 15; ++i) {
        trapezoids.push_back(TrapezoidD(1.0 + i, 2.0 + i, 1.0 + i));
    }
    
    cout << "Array capacity after resize: " << trapezoids.capacity() << "\n";
    cout << "Array size: " << trapezoids.size() << "\n";
}

int main() {
    Array<FigurePtr<double>> figures;
    int choice;
    
    do {
        showMenu();
        cin >> choice;
        
        try {
            switch (choice) {
                case 1: { // Add Trapezoid
                    cout << "Enter trapezoid dimensions (base1 base2 height): ";
                    double base1, base2, height;
                    cin >> base1 >> base2 >> height;
                    
                    auto trapezoid = make_shared<TrapezoidD>(base1, base2, height);
                    figures.push_back(trapezoid);
                    cout << "Trapezoid added successfully!\n";
                    break;
                }
                
                case 2: { // Add Rhombus
                    cout << "Enter rhombus diagonals (d1 d2): ";
                    double d1, d2;
                    cin >> d1 >> d2;
                    
                    auto rhombus = make_shared<RhombusD>(d1, d2);
                    figures.push_back(rhombus);
                    cout << "Rhombus added successfully!\n";
                    break;
                }
                
                case 3: { // Add Pentagon
                    cout << "Enter pentagon side length: ";
                    double side;
                    cin >> side;
                    
                    auto pentagon = make_shared<PentagonD>(side);
                    figures.push_back(pentagon);
                    cout << "Pentagon added successfully!\n";
                    break;
                }
                
                case 4: // Show all figures
                    if (figures.empty()) {
                        cout << "No figures in the array.\n";
                    } else {
                        cout << "\n=== All Figures (" << figures.size() << ") ===\n";
                        for (size_t i = 0; i < figures.size(); ++i) {
                            cout << "Figure #" << i + 1 << ":\n";
                            cout << "  ";
                            figures[i]->print(cout);
                            cout << "\n";
                            
                            auto center = figures[i]->center();
                            cout << "  Center: " << center << "\n";
                            cout << "  Area: " << figures[i]->area() << "\n";
                            cout << "-------------------\n";
                        }
                    }
                    break;
                
                case 5: { // Remove figure
                    if (figures.empty()) {
                        cout << "No figures to remove.\n";
                        break;
                    }
                    
                    cout << "Enter index to remove (1-" << figures.size() << "): ";
                    size_t index;
                    cin >> index;
                    
                    if (index >= 1 && index <= figures.size()) {
                        figures.erase(index - 1);
                        cout << "Figure removed successfully!\n";
                    } else {
                        cout << "Invalid index!\n";
                    }
                    break;
                }
                
                case 6: // Calculate total area
                    if (figures.empty()) {
                        cout << "No figures in the array.\n";
                    } else {
                        double totalArea = 0;
                        for (size_t i = 0; i < figures.size(); ++i) {
                            totalArea += figures[i]->area();
                        }
                        cout << "Total area of all figures: " << totalArea << "\n";
                    }
                    break;
                
                case 7: // Clear all figures
                    figures.clear();
                    cout << "All figures removed.\n";
                    break;
                
                case 8: // Demo with Array<Figure<double>*>
                    demoArrayOfFigures();
                    break;
                
                case 9: // Demo with Array<Rhombus<double>>
                    demoArrayOfRhombuses();
                    break;
                
                case 10: // Demo move semantics
                    demoMoveSemantics();
                    break;
                
                case 11: // Run tests
                    system("./tests04");
                    break;
                
                case 0: // Exit
                    cout << "Goodbye!\n";
                    break;
                
                default:
                    cout << "Invalid choice!\n";
            }
            
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
    } while (choice != 0);
    
    return 0;
}
