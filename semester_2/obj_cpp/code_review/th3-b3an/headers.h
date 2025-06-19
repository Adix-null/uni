#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>

//=================================================================

// interface
class Pizza
{
public:
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
    virtual void bake() const = 0;
};

//=================================================================

// concrete class
class Margherita : public Pizza
{
public:
    std::string getDescription() const override;
    double getCost() const override;
    void bake() const override;
};

// abstract decorator
class PizzaDecorator : public Pizza
{
protected:
    Pizza *wrappedPizza;

public:
    PizzaDecorator(Pizza *pizza);

    virtual std::string getDescription() const override;
    virtual double getCost() const override;
    virtual void bake() const override;
};

//=================================================================

// concrete decorator 1
class CheeseBurstDecorator : public PizzaDecorator
{
private:
    std::string cheeseType;
    int cheeseVolume;
    bool isDoubleLayered;

public:
    CheeseBurstDecorator(Pizza *p, std::string type = "Mozzarella", double volume = 100.0, bool doubleLayer = false);

    std::string getDescription() const override;
    double getCost() const override;
    void bake() const override;

private:
    void validateCheeseType() const;
    void validateCheeseVolume() const;

    void logBakingStep(const std::string &message) const;
};

// concrete decorator 2
class SpiceDecorator : public PizzaDecorator
{
private:
    std::string spiceType;
    int spiceLevel;
    bool addSpicySauce;

public:
    SpiceDecorator(Pizza *p, std::string type = "Chili Flakes", int level = 2, bool sauce = false);

    std::string getDescription() const override;
    double getCost() const override;
    void bake() const override;

private:
    void validateSpiceType() const;
    void validateSpiceLevel() const;
    void simulateSpiceInfusion() const;
    void simulateSauceCaramelization() const;
    void logStep(const std::string &msg) const;
};

// concrete decorator 3
// HERE GOES YOUR IMPLEMENTATION HEADER

class StuffedCrustDecorator : public PizzaDecorator
{
private:
    std::string stuffingType;
    double stuffingAmount;
    bool isExtraCrispy;

public:
    StuffedCrustDecorator(Pizza *p, std::string type = "Chili Flakes", int level = 2, bool sauce = false);

    std::string getDescription() const override;
    double getCost() const override;
    void bake() const override;

private:
    void validateStuffingType() const;
    void validateStuffingAmount() const;
    void logStep(const std::string &msg) const;
};

// base exception class
class PizzaCustomizationException : public std::exception
{
protected:
    std::string msg_;

public:
    PizzaCustomizationException(const std::string &message);
    virtual const char *what() const noexcept override;
};

// exception 1
class CheeseDecoratorException : public PizzaCustomizationException
{
public:
    CheeseDecoratorException(const std::string &msg);
};

// exception 2
class SpiceDecoratorException : public PizzaCustomizationException
{
public:
    SpiceDecoratorException(const std::string &msg);
};

// exception 3
class StuffedDecoratorException : public PizzaCustomizationException
{
public:
    StuffedDecoratorException(const std::string &msg);
};
