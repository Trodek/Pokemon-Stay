#ifndef _WORLD_H_
#define _WORLD_H_

#include "Point2D.h"
#include "MyString.h"

class RandomWorld
{
private:
	int death_limit = 3;
	int birth_limit = 4;
	int chance_to_be_ground = 40;
	int steps = 5;

public:
	
	struct biome{
		char repesentation;
		int rang_min, range_max;
		iPoint center;
		MyString Zone;
	};

	biome biomes[7];
	int width = 200;
	int height = 200;
	bool* boolmap = nullptr;
	int* zonemap = nullptr;

private:
	// --Methods--
	// Bool map generation

	bool CreateBoolMap();
	bool CreateRandomBoolMap();
	bool DoSimulationStep();
	int CountAliveNeighbours(int x, int y);

	// Zone Map Generation

	bool CreateZoneMap();
	bool CreateIntMapTemplate();
	bool DefineBiomesZones();

	// Biomes
	void SetBiomes();

public:
	// --Constructors--
	RandomWorld();

	RandomWorld(int size);

	// --Destructor--
	~RandomWorld();

	// --Methods--

	void PrintBoolWorld();

	void PrintIntWorld();

	void PrintZoneWorld();

};



#endif