#include "headers.h"

StuffedCrustDecorator::StuffedCrustDecorator(
    Pizza *p,
    std::string type,
    int amount,
    bool crispy) : PizzaDecorator(p), stuffingType(type), stuffingAmount(amount), isExtraCrispy(crispy)
{
    validateStuffingType();
    validateStuffingAmount();
}

std::string StuffedCrustDecorator::getDescription() const
{
    std::string desc = wrappedPizza->getDescription();
    desc += "\n+ Stuffed Crust (" + stuffingType + ", " + std::to_string(stuffingAmount) + "g)";
    if (isExtraCrispy)
    {
        desc += ", Extra Crispy";
    }
    return desc;
}

double StuffedCrustDecorator::getCost() const
{
    double cost = wrappedPizza->getCost();
    cost += stuffingAmount * 0.03;
    return cost;
}

void StuffedCrustDecorator::bake() const
{
    wrappedPizza->bake();
    logStep("Stuffing " + stuffingType + "...");
    if (isExtraCrispy)
    {
        logStep("Drizzling garlic butter over pizza...");
    }
    logStep("Stuffing infusion complete.");
}

void StuffedCrustDecorator::validateStuffingType() const
{
    static const std::vector<std::string> allowed = {"Cheese", "Garlic Butter", "Cream Cheese"};
    if (find(allowed.begin(), allowed.end(), stuffingType) == allowed.end())
    {
        throw StuffedDecoratorException("Unsupported stuffing type: " + stuffingType);
    }
}

void StuffedCrustDecorator::validateStuffingAmount() const
{
    if (stuffingAmount < 30 || stuffingAmount > 150)
    {
        throw StuffedDecoratorException("Stuffing amount must be between 30 and 150.");
    }
}

void StuffedCrustDecorator::logStep(const std::string &msg) const
{
    std::cout << "[StuffedDecorator] " << msg << std::endl;
}
