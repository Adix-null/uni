#ifndef FISHINGBOAT_H_INCLUDED
#define FISHINGBOAT_H_INCLUDED

#include "FishingTool.h"

// Context
class FishingBoat
{
private:
    FishingTool* strategy;  // Not owning pointer

public:
    explicit FishingBoat(FishingTool* initialStrategy)
        : strategy(initialStrategy) {}

    void setStrategy(FishingTool* newStrategy);

    void prepareFishing() const;

    void goFishing() const;
};

#endif // FISHINGBOAT_H_INCLUDED
