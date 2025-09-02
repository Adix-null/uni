#include "FishingNet.h"
#include "FishingSpear.h"
#include "FishingBoat.h"

int main()
{
    FishingNet net;
    FishingSpear spear;

    FishingBoat boat(&net);

    boat.prepareFishing();
    boat.goFishing();

    //pakeiciame strategija, pasinaudojama polimorfizmu tam kad butu visai kitaip zvejojama
    boat.setStrategy(&spear);
    boat.prepareFishing();
    boat.goFishing();

    return 0;
}

