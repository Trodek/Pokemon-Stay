#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleWorld.h"

ModuleWorld::ModuleWorld(){
	Tile.h = TILE_SIZE;
	Tile.w = TILE_SIZE;
	Tile.x = 0;
	Tile.y = 0;
	World = new RandomWorld(250);
}

ModuleWorld::~ModuleWorld(){
	App->textures->Unload(MapTiles);
	delete World;
}

bool ModuleWorld::Start(){

	LOG("ModuleWorld Init ------------------");

	MapTiles = App->textures->Load("PokemonStay/Sprites/Maps/Map Tiles.png");

	return true;
}

update_status ModuleWorld::Update(){

	PrintWorld();
	
	return UPDATE_CONTINUE;
}

void ModuleWorld::PrintWorld(){
	for (uint row = 0; row < World->height; row++){
		for (uint column = 0; column < World->width; column++){
			Tile.x = (*(World->zonemap + column + row*World->width) % 10)*TILE_SIZE;
			Tile.y = (*(World->zonemap + column + row*World->width) / 10)*TILE_SIZE;
			App->render->Blit(MapTiles, column*TILE_SIZE, row*TILE_SIZE, &Tile);
		}
	}
}
