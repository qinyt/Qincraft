#include "LightForest.h"

//#include "../Structures/TreeGenerator.h"

LightForest::LightForest(int seed)
    : Biome(getNoiseParameters(), 60, 80, seed)
{
}

Block LightForest::getTopBlock(Rand &rand) const
{
    return BlockType::GRASS;
}

Block LightForest::getUnderWaterBlock(Rand &rand) const
{
    return rand.intInRange(0, 10) > 9 ? BlockType::SAND : BlockType::MUD;
}

void LightForest::makeTree(Rand &rand, Chunk &chunk, int x, int y, int z) const
{
    //makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters LightForest::getNoiseParameters()
{
    NoiseParameters heightParams;
    heightParams.octaves = 5;
    heightParams.amplitude = 100;
    heightParams.smoothness = 195; // 195
    heightParams.heightOffset = -32;
    heightParams.roughness = 0.52;

    return heightParams;
}

Block LightForest::getPlant(Rand &rand) const
{
    return rand.intInRange(0, 10) > 8 ? BlockType::Rose : BlockType::TallGrass;
}
