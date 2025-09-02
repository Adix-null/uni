#ifndef FISHINGROD_H_INCLUDED
#define FISHINGROD_H_INCLUDED

#include "FishingTool.h"
#include "FishingDepth.h"
#include "FishingNet.h"
#include "FishSelector.h"
#include <unordered_map>

class FishingRod : public FishingTool
{
private:
    std::string chosenFish;
    FishingDepth depthLevel;
    FishCategory category;

public:
    void prepare() override;
    void prepare(int baitChoice);
    void fish() const override;
    std::string getChosenFish() const;
    FishCategory getFishCategory() const;
};

#endif // FISHINGROD_H_INCLUDED
