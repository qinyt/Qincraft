#ifndef TEMPERATEFORESTBIOME_H_INCLUDED
#define TEMPERATEFORESTBIOME_H_INCLUDED

#include "Biome.h"

class TemperateForestBiome : public Biome {
  public:
    TemperateForestBiome(int seed);

    Block getPlant(Rand &rand) const override;
    Block getTopBlock(Rand &rand) const override;
    Block getUnderWaterBlock(Rand &rand) const override;
    void makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const override;

  private:
    NoiseParameters getNoiseParameters();
};

#endif // TEMPERATEFORESTBIOME_H_INCLUDED
