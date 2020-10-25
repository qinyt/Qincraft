#include "TemperateForestBiome.h"

//#include "../Structures/TreeGenerator.h"

TemperateForestBiome::TemperateForestBiome(int seed)
    : Biome(getNoiseParameters(), 55, 75, seed)
{
}

Block TemperateForestBiome::getTopBlock(Rand &rand) const
{
    return rand.intInRange(0, 10) < 8 ? BlockType::GRASS : BlockType::MUD;
}

Block TemperateForestBiome::getUnderWaterBlock(Rand &rand) const
{
    return rand.intInRange(0, 10) > 8 ? BlockType::MUD : BlockType::SAND;
}

void TemperateForestBiome::makeTree(Rand &rand, Chunk &chunk, int x, int y,
                                    int z) const
{
    //makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters TemperateForestBiome::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves = 5;
    heightParams.amplitude = 100;
    heightParams.smoothness = 195;
    heightParams.heightOffset = -30;
    heightParams.roughness = 0.52;

    return heightParams;
}

Block TemperateForestBiome::getPlant(Rand &rand) const
{
    return BlockType::TallGrass;
}
