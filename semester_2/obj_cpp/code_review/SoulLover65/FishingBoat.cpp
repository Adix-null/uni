#include "FishingBoat.h"

    void FishingBoat::setStrategy(FishingTool* newStrategy)
    {
        strategy = newStrategy;
    }

    void FishingBoat::prepareFishing() const
    {
        if (strategy)
        {
            strategy->prepare();
        }
        else
        {
            std::cout << "Nera pasirinkta zvejybos strategija!" << std::endl;
        }
    }

    void FishingBoat::goFishing() const
    {
        std::cout << "Valtis pradeda zvejyba..." << std::endl;
        if (strategy)
        {
            strategy->fish();
        }
        else
        {
            std::cout << "Nera pasirinkta zvejybos strategija!" << std::endl;
        }
    }
