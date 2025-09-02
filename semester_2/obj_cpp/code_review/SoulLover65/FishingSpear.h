#ifndef FISHINGSPEAR_H_INCLUDED
#define FISHINGSPEAR_H_INCLUDED

#include "FishingTool.h"
#include "FishingDepth.h"
#include "FishCategory.h"
#include <unordered_map>

class FishingSpear : public FishingTool
{
private:
    FishingDepth depthLevel;
    double successChance;
    double doubleCatchChance;
    FishCategory category;

public:
    void prepare() override;
    void prepare(FishingDepth depth);
    void fish() const override;
};

#endif // FISHINGSPEAR_H_INCLUDED
