#ifndef BIOME_H_INCLUDED
#define BIOME_H_INCLUDED

#include "../NoiseGenerator.h"
#include "../Random.h"
#include "../Block.h"

using Rand = Random<std::minstd_rand>;

class Chunk;

struct Biome {
  public:
    Biome(const NoiseParameters &parameters, int treeFreq, int plantFreq,
          int seed);
    virtual ~Biome() = default;

    virtual BlockType getPlant(Rand &rand) const = 0;
    virtual BlockType getTopBlock(Rand &rand) const = 0;
    virtual BlockType getUnderWaterBlock(Rand &rand) const = 0;
    virtual BlockType getBeachBlock(Rand &rand) const;
    virtual void makeTree(Rand &rand, Chunk &chunk, int x, int y,
                          int z) const = 0;

    int getHeight(int x, int z, int chunkX, int chunkZ) const;
    int getTreeFrequency() const noexcept;
    int getPlantFrequency() const noexcept;

  protected:
    virtual NoiseParameters getNoiseParameters() = 0;

  private:
    NoiseGenerator m_heightGenerator;
    int m_treeFreq;
    int m_plantFreq;
};

#endif // BIOME_H_INCLUDED
