/*
    Sukure: Edvinas Bagdonas, programu sistemu studentas, 1 kursas, 4 grupė

    Programa sukuria klase HotelRoom, kuri turi kintamuosius, metodus, konstruktrius ir destruktoriu. Main funkcijoje vienetu testais patikrinama ar klase veikia tinkamai.
*/

#include <iostream>
#include <sstream>
#include <assert.h>

using namespace std;

class hotelRoom
{

private:
    static int nextID;
    static int count;

    int id;
    string roomType;
    int roomNumber;
    int pricePerNight;

public:
    hotelRoom(int number)
    {
        setDefaults(number);
    }

    hotelRoom(string type, int number, int price)
    {
        setDefaults(number);
        setRoomType(type);
        setPricePerNight(price);
    }

    ~hotelRoom()
    {
        count--;
    }

public:
    void setDefaults(int number)
    {
        setRoomNumber(number);
        setRoomType("Single");
        setPricePerNight(0);
        incrementID();
        incrementCount();
    }

    void incrementID()
    {
        id = nextID++;
    }

    void incrementCount()
    {
        count++;
    }

public:
    string getRoomType()
    {
        return roomType;
    }
    void setRoomType(string type)
    {
        roomType = type;
    }
    int getRoomNumber()
    {
        return roomNumber;
    }
    void setRoomNumber(int number)
    {
        if (number < 0)
        {
            throw invalid_argument("RoomNumber cannot be negative.");
        }
        roomNumber = number;
    }
    int getPricePerNight()
    {
        return pricePerNight;
    }
    void setPricePerNight(int price)
    {
        if (price < 0)
        {
            throw invalid_argument("Price cannot be negative.");
        }
        pricePerNight = price;
    }

    int getId()
    {
        return id;
    }

    static int getCount()
    {
        return count;
    }
};

int hotelRoom::nextID = 1;
int hotelRoom::count = 0;

int main(int argc, char const *argv[])
{
    hotelRoom room(10);

    hotelRoom *rooms[4] = {
        new hotelRoom("Lux", 3, 500),
        new hotelRoom("Suite", 4, 200),
        new hotelRoom("Triple", 5, 30),
        new hotelRoom("Presidential", 6, 1000)};

    assert(room.getId() == 1);
    assert(room.getRoomType() == "Single");
    room.setRoomType("Double");
    assert(room.getRoomType() == "Double");
    assert(room.getRoomNumber() == 10);
    room.setRoomNumber(1);
    assert(room.getRoomNumber() == 1);
    assert(room.getPricePerNight() == 0);
    room.setPricePerNight(50);
    assert(room.getPricePerNight() == 50);
    assert(room.getCount() == 5);
    for (int i = 0; i < 4; i++)
    {
        assert(rooms[i]->getId() == i + 2);
        assert(rooms[i]->getRoomNumber() == i + 3);
        delete rooms[i];
    }

    assert(room.getCount() == 1);

    hotelRoom room7("Single", 7, 500);
    assert(room7.getId() == 6);

    assert(room.getCount() == 2);
    room7.~hotelRoom();
    room.~hotelRoom();
    assert(hotelRoom::getCount() == 0);

    return 0;
}