#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "World.h"

// --Constructors--

RandomWorld::RandomWorld()
{
	boolmap = new bool[height*width];
	CreateBoolMap();
	zonemap = new int[height*width];
	CreateZoneMap();
}

RandomWorld::RandomWorld(int size) : width(size), height(size)
{

	boolmap = new bool[height*width];
	CreateBoolMap();
	zonemap = new int[height*width];
	CreateZoneMap();

}

// --Destructor--

RandomWorld::~RandomWorld()
{
	delete[] boolmap;
	delete[] zonemap;
}

// --Methods--

// Bool map

bool RandomWorld::CreateBoolMap(){

	CreateRandomBoolMap();

	for (int i = 0; i < steps; i++){
		DoSimulationStep();
	}
	
	return true;
}

bool RandomWorld::CreateRandomBoolMap(){
	srand(time(NULL));
	for (int row = 0; row < height; row++){
		for (int colum = 0; colum < width; colum++){
			if (rand() % 100 < chance_to_be_ground){
				*(boolmap + colum + row*height) = true;
			}
			else *(boolmap + colum + row*height) = false;
		}
	}
	return true;
}

void RandomWorld::PrintBoolWorld(){
	for (int row = 0; row < height; row++){
		for (int colum = 0; colum < width; colum++){
			char temp = 0;
			switch (*(boolmap + colum + row*width))
			{
			case true: temp = 219;
				break;
			case false: temp = 32;
				break;
			}
			printf("%c", temp);
		}
		printf("\n");
	}
	printf("\n");
}

bool RandomWorld::DoSimulationStep(){
	bool* tempmap = new bool[height*width]; 
	for (int row = 0; row < height; row++){
		for (int colum = 0; colum < width; colum++){
			int alive = CountAliveNeighbours(row, colum);
			if (*(boolmap + colum + row*width)){
				if (alive < death_limit){
					*(tempmap + colum + row*width) = false;
				}
				else{
					*(tempmap + colum + row*width) = true;
				}
			}
			else{
				if (alive < birth_limit){
					*(tempmap + colum + row*width) = false;
				}
				else{
					*(tempmap + colum + row*width) = true;
				}
			}
		}
	}
	delete[] boolmap;
	boolmap = tempmap;

	return true;
}

int RandomWorld::CountAliveNeighbours(int row, int colum){
	int count = 0;
	for (int i = -1; i<2; i++){
		for (int j = -1; j<2; j++){
			int neighbour_row = row + i;
			int neighbour_colum = colum + j;

			//If we're looking at the middle point
			if (i == 0 && j == 0){
				//Do nothing
			}
			//In case the index we're looking at it off the edge of the map
			else if (neighbour_row < 0 || neighbour_colum < 0 || neighbour_row >= height || neighbour_colum >= width){
				//count = count + 1;
			}
			//Otherwise, a normal check of the neighbour
			else if (*(boolmap+neighbour_row*width+neighbour_colum)){
				count = count + 1;
			}
		}
	}
	return count;
}

// Zone map

bool RandomWorld::CreateZoneMap(){
	CreateIntMapTemplate();
	SetBiomes();
	DefineBiomesZones();

	return true;
}

bool RandomWorld::CreateIntMapTemplate(){
	for (int row = 0; row < height; row++){
		for (int colum = 0; colum < width; colum++){
			if (*(boolmap + colum + row*width)){
				*(zonemap + colum + row*width) = 1;
			}
			else *(zonemap + colum + row*width) = 0;
		}
	}
	return true;
}

void RandomWorld::SetBiomes(){
	//Ocean
	biomes[0].repesentation = 32;
	biomes[0].rang_min = 0;
	biomes[0].range_max = 9;
	biomes[0].Zone = "Ocean";

	//Desert
	biomes[1].repesentation = 126;
	biomes[1].rang_min = 10;
	biomes[1].range_max = 19;
	biomes[1].Zone = "Desert";

	//Mountain
	biomes[2].repesentation = 77;
	biomes[2].rang_min = 20;
	biomes[2].range_max = 29;
	biomes[2].Zone = "Mountain";

	//Forest
	biomes[3].repesentation = 190;
	biomes[3].rang_min = 30;
	biomes[3].range_max = 39;
	biomes[3].Zone = "Forest";

	//Plain
	biomes[4].repesentation = 219;
	biomes[4].rang_min = 40;
	biomes[4].range_max = 49;
	biomes[4].Zone = "Plain";

	//Snow Plain
	biomes[5].repesentation = 178;
	biomes[5].rang_min = 50;
	biomes[5].range_max = 59;
	biomes[5].Zone = "Snow Plain";

	//Snow Mountain
	biomes[6].repesentation = 229;
	biomes[6].rang_min = 60;
	biomes[6].range_max = 69;
	biomes[6].Zone = "Snow Mountain";

	for (int i = 1; i < 7; i++)	{
		biomes[i].center.x = rand() % width;
		biomes[i].center.y = rand() % height;

		while (*(zonemap + biomes[i].center.x + biomes[i].center.y*width) == 0){
			biomes[i].center.x = rand() % width;
			biomes[i].center.y = rand() % height;
		}
	}
	
}

bool RandomWorld::DefineBiomesZones(){
	for (int row = 0; row < height; row++){
		for (int colum = 0; colum < width; colum++){
			if (*(zonemap + colum + row*width) != 0){
				int nearest = 10;
				int dist = 2147483647; // biggest value to compare dist
				for (int i = 1; i < 7; i++){
					iPoint temp(colum, row);
					int curr_dist = temp.DistanceManhattan(biomes[i].center);
					if (curr_dist < dist){
						nearest = biomes[i].rang_min;
						dist = curr_dist;
					}
				}
				*(zonemap + colum + row*width) = nearest;
			}
		}
	}
	return true;
}

void RandomWorld::PrintIntWorld(){
	for (int row = 0; row < height; row++){
		for (int colum = 0; colum < width; colum++){
			printf("%d", *(zonemap + colum + row*width));
		}
		printf("\n");
	}
	printf("\n\n");
}

void RandomWorld::PrintZoneWorld(){
	for (int row = 0; row < height; row++){
		for (int colum = 0; colum < width; colum++){
			for (int i = 0; i < 7; i++){
				if (*(zonemap + colum + row*width) >= biomes[i].rang_min &&*(zonemap + colum + row*width) <= biomes[i].range_max){
					printf("%c", biomes[i].repesentation);
					break;
				}
			}
		}
		printf("\n");
	}
	printf("\n\n");
}