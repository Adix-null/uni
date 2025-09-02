#include "headers.h"

//=================================================================

PizzaDecorator::PizzaDecorator(Pizza *pizza) : wrappedPizza(pizza) {}

//=================================================================

std::string PizzaDecorator::getDescription() const {
    return wrappedPizza->getDescription();
}

double PizzaDecorator::getCost() const {
    return wrappedPizza->getCost();
}

void PizzaDecorator::bake() const {
    wrappedPizza->bake();
}