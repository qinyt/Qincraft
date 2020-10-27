#ifndef GRASSLANDBIOME_H_INCLUDED
#define GRASSLANDBIOME_H_INCLUDED

#include "Biome.h"

class GrasslandBiome : public Biome {
  public:
    GrasslandBiome(int seed);

    BlockType getBeachBlock(Rand &rand) const override;
    BlockType getPlant(Rand &rand) const override;
    BlockType getTopBlock(Rand &rand) const override;
    BlockType getUnderWaterBlock(Rand &rand) const override;
    void makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const override;

  private:
    NoiseParameters getNoiseParameters() override;
};

#endif // GRASSLANDBIOME_H_INCLUDED
