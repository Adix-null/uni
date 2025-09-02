/**
 * write a 3rd concrete decorator called StuffedCrustDecorator
 *
 * it should have these fields:
 *  string StuffingType (default: "Cheese")
 *  double StuffingAmount (default: 80.0)
 *  bool isExtraCrispy (default: false)
 *
 * override these methods:
 *  string getDescription() - should add description info about stuffing type, amount and extra crust TO THE EXCISTING DESCRIPTION
 *  double getCost() - should add stuffingCost TO THE EXCISTING COST (stuffingCost = stuffingAmount * 0.03)
 *  void bake() - calls log method for each baking step
 *
 * have these methods:
 *  void log(string msg) - cout "[StuffedCrustDecorator]" and msg
 *
 * validate these fields:
 *  StuffingType - allowed types should be "Cheese", "Garlic Butter", "Cream Cheese"
 *  StuffingAmount - [30; 150]
 * and throw a StuffedDecoratorException (already created) if something is wrong
 *
 *
 * description depiction:
 * + Stuffed Crust ([stuffingType], [stuffingAmount]g)
 *
 * if extra crispy:
 * + Stuffed Crust ([stuffingType], [stuffingAmount]g), Extra Crispy
 */

#include "headers.h"
#include <cassert>

using namespace std;

int main()
{
    try
    {
        Pizza *pizza1 = new Margherita();

        cout << "Expected: " << 6.5 << endl;
        cout << "Is:       " << pizza1->getCost() << endl
             << endl;
        assert(pizza1->getCost() == 6.5);

        pizza1 = new StuffedCrustDecorator(pizza1);

        cout << "Expected: " << 8.9 << endl;
        cout << "Is:       " << pizza1->getCost() << endl
             << endl;
        assert(pizza1->getCost() == 8.9);

        cout << "Expected:\n"
             << "Margherita\n+ Stuffed Crust (Cheese, 80g)" << endl;
        cout << "Is:\n"
             << pizza1->getDescription() << endl
             << endl;
        assert(pizza1->getDescription() == "Margherita\n+ Stuffed Crust (Cheese, 80g)");

        Pizza *pizza2 = new Margherita();
        pizza2 = new StuffedCrustDecorator(pizza2, "Garlic Butter", 120, true);

        cout << "Expected: " << 10.1 << endl;
        cout << "Is:       " << pizza2->getCost() << endl
             << endl;
        assert(pizza2->getCost() == 10.1);

        cout << "Expected:\n"
             << "Margherita\n+ Stuffed Crust (Garlic Butter, 120g), Extra Crispy" << endl;
        cout << "Is:\n"
             << pizza2->getDescription() << endl
             << endl;
        assert(pizza2->getDescription() == "Margherita\n+ Stuffed Crust (Garlic Butter, 120g), Extra Crispy");

        try
        {
            Pizza *pizzaError = new Margherita();
            pizzaError = new StuffedCrustDecorator(pizza2, "Garlic ", 120, true);
            assert(0); // if no problems detected
        }
        catch (const PizzaCustomizationException &e)
        {
        }

        try
        {
            Pizza *pizzaError = new Margherita();
            pizzaError = new StuffedCrustDecorator(pizza2, "Garlic Butter", 151, true);
            assert(0); // if no problems detected
        }
        catch (const PizzaCustomizationException &e)
        {
        }
    }
    catch (const PizzaCustomizationException &e)
    {
        std::cout << "Caught Pizza Customization Exception: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught std::exception: " << e.what() << std::endl;
    }

    return 0;
}