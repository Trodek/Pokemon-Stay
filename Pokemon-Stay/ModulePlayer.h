#ifndef _ModulePlayer_H_
#define _ModulePlayer_H_

#include "Globals.h"
#include "Application.h"
#include "Module.h"
#include "Point2D.h"
#include "Animation.h"

struct SDL_Texture;

class ModulePlayer :public Module{
public:
	iPoint current_pos, world_pos, target_pos;
	uint level = 1;

private:
	SDL_Texture* Character_tex;
	Animation up, right, left, down;
	SDL_Rect idle_up, idle_down, idle_left, idle_right;
	Directions current_dir, target_dir;
	
	bool move = false, key_used = false;

public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();


private:
	iPoint ConvertToWorld(iPoint& pos);
	SDL_Rect* GetRectToprint();
	void SetInitialCameraView();
	bool CanMove();
};

#endif