#include "headers.h"

//=================================================================

CheeseBurstDecorator::CheeseBurstDecorator(
    Pizza* p,
    std::string type,
    double volume,
    bool doubleLayer
) : PizzaDecorator(p), cheeseType(type), cheeseVolume(volume), isDoubleLayered(doubleLayer) {
    validateCheeseType();
    validateCheeseVolume();
}

//=================================================================

std::string CheeseBurstDecorator::getDescription() const {
    std::string desc = wrappedPizza->getDescription();
    desc = desc + "\n+ " + cheeseType + " Cheese Burst";
    if (isDoubleLayered) {
        desc = desc + " (Double Layered)";
    }
    return desc;
}

double CheeseBurstDecorator::getCost() const {
    double baseCost = wrappedPizza->getCost();
    double cheeseCost = cheeseVolume / 50.0;
    if (isDoubleLayered) {
        cheeseCost *= 1.5;
    }
    cheeseCost = round(cheeseCost);
    return baseCost + cheeseCost;
}

void CheeseBurstDecorator::bake() const {
    wrappedPizza->bake();
    logBakingStep("Adding " + cheeseType + " cheese layer...");
    if (isDoubleLayered) {
        logBakingStep("Adding second cheese layer...");
    }
    logBakingStep("Cheese burst baking complete.");
}

void CheeseBurstDecorator::logBakingStep(const std::string& message) const {
    std::cout << "[CheeseBurst] " << message << std::endl;
}

//=================================================================

void CheeseBurstDecorator::validateCheeseType() const {
    static const std::vector<std::string> allowed = {"Mozzarella", "Cheddar", "Gouda"};
    if (find(allowed.begin(), allowed.end(), cheeseType) == allowed.end()) {
        throw CheeseDecoratorException("Unsupported cheese type: " + cheeseType);
    }
}

void CheeseBurstDecorator::validateCheeseVolume() const {
    if (cheeseVolume < 50 || cheeseVolume > 300) {
        throw CheeseDecoratorException("Cheese volume must be between 50g and 300g.");
    }
}