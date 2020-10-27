#include "GrasslandBiome.h"

//#include "../Structures/TreeGenerator.h"

GrasslandBiome::GrasslandBiome(int seed)
    : Biome(getNoiseParameters(), 1000, 20, seed)
{
}

BlockType GrasslandBiome::getTopBlock(Rand &rand) const
{
    return BlockType::DIRT_TOP;
}

BlockType GrasslandBiome::getUnderWaterBlock(Rand &rand) const
{
    return rand.intInRange(0, 10) > 8 ? BlockType::DIRT_TOP: BlockType::SAND;
}

BlockType GrasslandBiome::getBeachBlock(Rand &rand) const
{
    return rand.intInRange(0, 10) > 2 ? BlockType::DIRT_TOP : BlockType::MUD;
}

void GrasslandBiome::makeTree(Rand &rand, Chunk &chunk, int x, int y,
                              int z) const
{
    //makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters GrasslandBiome::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 85;
    heightParams.smoothness = 235;
    heightParams.heightOffset = -20;
    heightParams.roughness = 0.51;

    return heightParams;
}

BlockType GrasslandBiome::getPlant(Rand &rand) const
{
    return rand.intInRange(0, 10) > 6 ? BlockType::Rose : BlockType::TallGrass;
}
