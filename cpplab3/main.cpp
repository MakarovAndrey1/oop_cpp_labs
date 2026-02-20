#include <iostream>
#include <memory>
#include <limits>
#include "include/Pentagon.h"
#include "include/Hexagon.h"
#include "include/Octagon.h"
#include "include/Array.h"

void showMenu() {
    std::cout << "\n=== Figure Management System ===\n";
    std::cout << "1. Add Pentagon\n";
    std::cout << "2. Add Hexagon\n";
    std::cout << "3. Add Octagon\n";
    std::cout << "4. Show all figures\n";
    std::cout << "5. Remove figure by index\n";
    std::cout << "6. Calculate total area\n";
    std::cout << "7. Clear all figures\n";
    std::cout << "0. Exit\n";
    std::cout << "Choice: ";
}

int main() {
    Array figuresArray;
    int choice;
    
    do {
        showMenu();
        std::cin >> choice;
        
        try {
            switch (choice) {
                case 1: { // Add Pentagon
                    std::cout << "Enter side length for Pentagon: ";
                    double side;
                    std::cin >> side;
                    
                    auto pentagon = std::make_shared<Pentagon>(side);
                    figuresArray.addFigure(pentagon);
                    std::cout << "Pentagon added successfully!\n";
                    break;
                }
                
                case 2: { // Add Hexagon
                    std::cout << "Enter side length for Hexagon: ";
                    double side;
                    std::cin >> side;
                    
                    auto hexagon = std::make_shared<Hexagon>(side);
                    figuresArray.addFigure(hexagon);
                    std::cout << "Hexagon added successfully!\n";
                    break;
                }
                
                case 3: { // Add Octagon
                    std::cout << "Enter side length for Octagon: ";
                    double side;
                    std::cin >> side;
                    
                    auto octagon = std::make_shared<Octagon>(side);
                    figuresArray.addFigure(octagon);
                    std::cout << "Octagon added successfully!\n";
                    break;
                }
                
                case 4: // Show all figures
                    if (figuresArray.size() == 0) {
                        std::cout << "No figures in the array.\n";
                    } else {
                        std::cout << "\n=== All Figures (" << figuresArray.size() << ") ===\n";
                        figuresArray.printAll();
                    }
                    break;
                
                case 5: { // Remove figure
                    if (figuresArray.size() == 0) {
                        std::cout << "No figures to remove.\n";
                        break;
                    }
                    
                    std::cout << "Enter index to remove (1-" << figuresArray.size() << "): ";
                    size_t index;
                    std::cin >> index;
                    
                    if (index >= 1 && index <= figuresArray.size()) {
                        figuresArray.removeFigure(index - 1);
                        std::cout << "Figure removed successfully!\n";
                    } else {
                        std::cout << "Invalid index!\n";
                    }
                    break;
                }
                
                case 6: // Calculate total area
                    if (figuresArray.size() == 0) {
                        std::cout << "No figures in the array.\n";
                    } else {
                        std::cout << "Total area of all figures: " << figuresArray.totalArea() << "\n";
                    }
                    break;
                
                case 7: // Clear all figures
                    figuresArray.clear();
                    std::cout << "All figures removed.\n";
                    break;
                
                case 0: // Exit
                    std::cout << "Goodbye!\n";
                    break;
                
                default:
                    std::cout << "Invalid choice!\n";
            }
            
            // Clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
    } while (choice != 0);
    
    return 0;
}