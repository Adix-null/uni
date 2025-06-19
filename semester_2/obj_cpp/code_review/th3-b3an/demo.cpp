#include "headers.h"

using namespace std;

void summary(Pizza* pizza) {
    // order summary
    cout << "\nOrder Summary:\n\n";
    cout << pizza->getDescription() << endl;
    cout << fixed << setprecision(2) << "\nTotal Cost: " << pizza->getCost() << "€" << endl;

    // baking
    cout << "\nBaking Process:\n";
    pizza->bake();
}

int main() {
    try {
        cout << endl << "First option: ";
        cout << endl << "----------------------------------------" << endl;

        Pizza* pizza1 = new Margherita();
        pizza1 = new CheeseBurstDecorator(pizza1); // polimorfism
        summary(pizza1);

        cout << endl << "Second option: ";
        cout << endl << "----------------------------------------" << endl;

        Pizza* pizza2 = new Margherita();
        pizza2 = new SpiceDecorator(pizza2, "Black Pepper", 2, true); // polimorfism
        summary(pizza2);

        cout << endl << "Third option: ";
        cout << endl << "----------------------------------------" << endl;

        Pizza* pizza3 = new Margherita();
        pizza3 = new CheeseBurstDecorator(pizza3, "Mozzarella", 220, false); // polimorfism
        pizza3 = new SpiceDecorator(pizza3, "Chili Flakes", 5, false); // polimorfism
        summary(pizza3);

    } catch (const PizzaCustomizationException& e) {
        std::cout << "Caught Pizza Customization Exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught std::exception: " << e.what() << std::endl;
    }
    return 0;
}