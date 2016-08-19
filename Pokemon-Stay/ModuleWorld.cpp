#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleWorld.h"
#include "ModulePlayer.h"

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
	int row = App->player->current_pos.y - 12;
	if (row < 0) row = 0;
	int end_row = row + 25;
	if (end_row>World->height) {
		end_row = World->height;
		row = end_row - 25;
	}
	for (; row < end_row; row++){
		int column = App->player->current_pos.x - 16;
		if (column < 0) column = 0;
		int end_column = column + 32;
		if (end_column>World->width) {
			end_column = World->width;
			column = end_column - 32;
		}
		for (0; column < end_column; column++){
			Tile.x = (*(World->zonemap + column + row*World->width) % 10)*TILE_SIZE;
			Tile.y = (*(World->zonemap + column + row*World->width) / 10)*TILE_SIZE;
			App->render->Blit(MapTiles, column*TILE_SIZE, row*TILE_SIZE, &Tile);
		}
	}
}
