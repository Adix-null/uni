#include "headers.h"

SpiceDecorator::SpiceDecorator(
    Pizza* p,
    std::string type,
    int level,
    bool sauce
) : PizzaDecorator(p), spiceType(type), spiceLevel(level), addSpicySauce(sauce) {
    validateSpiceType();
    validateSpiceLevel();
}

std::string SpiceDecorator::getDescription() const {
    std::string desc = wrappedPizza->getDescription();
    desc = desc + "\n+ " + spiceType + " (Spice Level " + std::to_string(spiceLevel) + ")";
    if (addSpicySauce) {
        desc = desc + " with Spicy Sauce";
    }
    return desc;
}

double SpiceDecorator::getCost() const {
    double cost = wrappedPizza->getCost();
    if (addSpicySauce) {
        cost = cost + 0.7;
    }
    return cost;
}

void SpiceDecorator::bake() const {
    wrappedPizza->bake();
    logStep("Sprinkling " + spiceType + "...");
    if (addSpicySauce) {
        logStep("Drizzling spicy sauce over pizza...");
    }
    logStep("Spice infusion complete.");
}

void SpiceDecorator::validateSpiceType() const {
    static const std::vector<std::string> allowed = {"Chili Flakes", "Jalapenos", "Black Pepper"};
    if (find(allowed.begin(), allowed.end(), spiceType) == allowed.end()) {
        throw SpiceDecoratorException("Unsupported spice type: " + spiceType);
    }
}

void SpiceDecorator::validateSpiceLevel() const {
    if (spiceLevel < 1 || spiceLevel > 5) {
        throw SpiceDecoratorException("Spice level must be between 1 and 5.");
    }
}

void SpiceDecorator::logStep(const std::string& msg) const {
    std::cout << "[SpicyDecorator] " << msg << std::endl;
}
