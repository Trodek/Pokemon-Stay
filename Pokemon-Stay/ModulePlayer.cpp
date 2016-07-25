#include "Globals.h"
#include "Animation.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleWorld.h"

ModulePlayer::ModulePlayer(){
	// Idle pos
	idle_up = { 0, 0, TILE_SIZE, TILE_SIZE };
	idle_down = { 0, TILE_SIZE, TILE_SIZE, TILE_SIZE };
	idle_right = { 0, TILE_SIZE*2, TILE_SIZE, TILE_SIZE };
	idle_left = { 0, TILE_SIZE*3, TILE_SIZE, TILE_SIZE };

	// Animations
	up.PushBack({ TILE_SIZE, 0, TILE_SIZE, TILE_SIZE });
	up.PushBack({ TILE_SIZE*2, 0, TILE_SIZE, TILE_SIZE });
	up.speed = 0.1f;

	down.PushBack({ TILE_SIZE, TILE_SIZE, TILE_SIZE, TILE_SIZE });
	down.PushBack({ TILE_SIZE * 2, TILE_SIZE, TILE_SIZE, TILE_SIZE });
	down.speed = 0.1f;

	right.PushBack({ TILE_SIZE, TILE_SIZE*2, TILE_SIZE, TILE_SIZE });
	right.PushBack({ TILE_SIZE * 2, TILE_SIZE*2, TILE_SIZE, TILE_SIZE });
	right.speed = 0.1f;

	left.PushBack({ TILE_SIZE, TILE_SIZE*3, TILE_SIZE, TILE_SIZE });
	left.PushBack({ TILE_SIZE * 2, TILE_SIZE*3, TILE_SIZE, TILE_SIZE });
	left.speed = 0.1f;

	//
}

ModulePlayer::~ModulePlayer(){
	
}

bool ModulePlayer::Start(){
	
	LOG("Player Start........");

	Character_tex = App->textures->Load("PokemonStay/Sprites/Players/Arlet.png");
	current_dir = target_dir = DOWN;
	current_pos = target_pos = { 14, 180 };
	world_pos = ConvertToWorld(current_pos);
	SetInitialCameraView();

	return true;
}

bool ModulePlayer::CleanUp(){
	App->textures->Unload(Character_tex);

	return true;
}

update_status ModulePlayer::Update(){

	if (!move){
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT){
			target_dir = RIGHT;
			key_used = true;
			if (target_dir == current_dir && current_pos.x < App->world->World->width-1){
				if (*(App->world->World->zonemap + current_pos.x + 1 + current_pos.y*App->world->World->width))
					target_pos.x += 1;
			}
			else{
				current_dir = target_dir;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !key_used){
			target_dir = LEFT;
			key_used = true;
			if (target_dir == current_dir && current_pos.x > 0){
				if (*(App->world->World->zonemap + current_pos.x - 1 + current_pos.y*App->world->World->width))
					target_pos.x -= 1;
			}
			else{
				current_dir = target_dir;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && !key_used){
			target_dir = UP;
			key_used = true;
			if (target_dir == current_dir && current_pos.y > 0){
				if (*(App->world->World->zonemap + current_pos.x + (current_pos.y-1)*App->world->World->width))
					target_pos.y -= 1;
			}
			else{
				current_dir = target_dir;
			}
		}
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && !key_used){
			target_dir = DOWN;
			key_used = true;
			if (target_dir == current_dir && current_pos.y < App->world->World->height-1){
				if (*(App->world->World->zonemap + current_pos.x + (current_pos.y + 1)*App->world->World->width))
					target_pos.y += 1;
			}
			else{
				current_dir = target_dir;
			}
		}
		key_used = false;

		if (target_pos != current_pos){
			move = true;
		}

	}
	else{
		uint speed = 2;
		iPoint world_target_pos = ConvertToWorld(target_pos);

		switch (current_dir)
		{
		case UP:
			world_pos.y -= speed;
			if (target_pos.y > 9 && target_pos.y < App->world->World->width - 12)
				App->render->camera.y += speed;
			break;
		case RIGHT:
			world_pos.x += speed;
			if (target_pos.x > 15 && target_pos.x < App->world->World->width - 14)
				App->render->camera.x -= speed;
			break;
		case DOWN:
			world_pos.y += speed;
			if (target_pos.y > 10 && target_pos.y < App->world->World->width - 11)
				App->render->camera.y -= speed;
			break;
		case LEFT:
			world_pos.x -= speed;
			if (target_pos.x > 14 && target_pos.x < App->world->World->width - 15)
				App->render->camera.x += speed;
			break;
		}

		if (world_target_pos == world_pos){
			move = false;
			current_pos = target_pos;
		}
	}

	App->render->Blit(Character_tex, world_pos.x, world_pos.y, GetRectToprint());

	return UPDATE_CONTINUE;
}

iPoint ModulePlayer::ConvertToWorld(iPoint& position){
	return { position.x*TILE_SIZE, position.y*TILE_SIZE };
}

SDL_Rect* ModulePlayer::GetRectToprint(){
	if (move){
		switch (current_dir)
		{
		case UP:
			return &up.GetCurrentFrame();
		case RIGHT:
			return &right.GetCurrentFrame();
		case DOWN:
			return &down.GetCurrentFrame();
		case LEFT:
			return &left.GetCurrentFrame();
		}
	}
	else{
		switch (current_dir)
		{
		case UP:
			return &idle_up;
		case RIGHT:
			return &idle_right;
		case DOWN:
			return &idle_down;
		case LEFT:
			return &idle_left;

		}
	}
}

void ModulePlayer::SetInitialCameraView(){
	App->render->camera.x = -(current_pos.x*TILE_SIZE - 14 * TILE_SIZE);
	App->render->camera.y = -(current_pos.y*TILE_SIZE - 10 * TILE_SIZE);
}