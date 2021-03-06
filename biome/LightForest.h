#ifndef LIGHTFOREST_H_INCLUDED
#define LIGHTFOREST_H_INCLUDED

#include "Biome.h"

class LightForest : public Biome {
  public:
    LightForest(int seed);

   BlockType getPlant(Rand &rand) const override;
   BlockType getTopBlock(Rand &rand) const override;
   BlockType getUnderWaterBlock(Rand &rand) const override;
    void makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const override;

  private:
    NoiseParameters getNoiseParameters() override;
};

#endif // LIGHTFOREST_H_INCLUDED
