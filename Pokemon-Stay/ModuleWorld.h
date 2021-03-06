#ifndef _ModuleWorld_H_
#define _ModuleWorld_H_

#include "Module.h"
#include "World.h"

class ModuleWorld : public Module{
public:
	SDL_Texture* MapTiles = nullptr;
	RandomWorld* World;

private:
	SDL_Rect Tile;

public:
	ModuleWorld();
	~ModuleWorld();

	update_status Update();
	bool Start();

private:
	void PrintWorld();
};

#endif