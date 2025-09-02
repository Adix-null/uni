#include "headers.h"

//=================================================================

std::string Margherita::getDescription() const {
    return "Margherita";
}

double Margherita::getCost() const {
    return 6.5;
}

void Margherita::bake() const {
    std::cout << "Baking Margherita pizza...\n";
}

    