#include <iostream>
#include <cstring>
#include <stdexcept>
#include <cassert>

using namespace std;

static int objectID = 0;
static int objectCount = 0;

int checksum(int num)
{
    int sum = 0;
    num %=10;

    while (num > 0)
    {
        sum += num % 10;
        num /= 10;
    }

    return sum % 10;
}

class Product{
private:
    int barcode;
    string name;
    float weight;
    int id;

    void setName(string name){ this->name = name; }

public:
    Product(int barcode, string name, float weight)
    {
        setBarcode(barcode);
        setName(name);
        setWeight(weight);
        id = objectID;
        objectID++;
        objectCount++;
    }

    ~Product()
    {
        objectCount--;
    };

    int getBarcode() { return barcode; }
    void setBarcode(int barcode)
    {
        if(barcode < 0)
        {
            throw invalid_argument("Barcode cannot be negative");
        }
        if(checksum(barcode) != barcode % 10)
        {
            throw invalid_argument("Barcode cannot have wrong checksum");
        }
        this->barcode = barcode;
    }

    string getName() { return name; }

    float getWeight() { return weight; }
    void setWeight(float weight)
    {
        if(weight <= 0)
        {
            throw invalid_argument("Weight cannot be negative or zero");
        }
        this->weight = weight;
    }

    int getId()
    {
        return id;
    }

    void toString()
    {
        cout << "\nId: " << getId() << "\nBarcode: " << getBarcode() << "\nName: " << getName() << "\nWeight: " << getWeight() << "kg\n";
    }
};

int main()
{
    Product p1(123, "Strawberry Miau", 1.2f);
    assert(p1.getBarcode() == 123);
    assert(p1.getName() == "Strawberry Miau");
    assert(p1.getWeight() == 1.2f);
    assert(p1.getId() == 0);
    p1.toString();

    assert(objectCount == 1);
    p1.~Product();
    assert(objectCount == 0);

    Product p2(28279, "Shirt", 1.3f);
    p2.setBarcode(9991110);
    p2.setWeight(2.1f);
    assert(p2.getBarcode() == 9991110);
    assert(p2.getName() == "Shirt");
    assert(p2.getWeight() == 2.1f);
    assert(p2.getId() == 1);
    p2.toString();

    return 0;
}
