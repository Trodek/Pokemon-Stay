#ifndef _Pokemon_H_
#define _Pokemon_H_

#include "Globals.h"
#include "MyString.h"
#include "Point2D.h"
#include "Application.h"
#include "ModulePokemons.h"
#include "ModulePlayer.h"
#include "ModuleWorld.h"
#include "ModuleRender.h"
#include <stdlib.h>

struct SDL_Texture;

class Pokemon{
public:
	Pokemons Poke;
	MyString name;
	iPoint position;
	uint combat_power;
	bool legendary;

	Types type;
	
	Pokemons evolved_from = None;
	Pokemons evolution = None;

private:
	SDL_Texture* pokemon_tex;
	SDL_Texture* siluet_tex;
	SDL_Rect Sprite;

public:
	Pokemon(Pokemons number, const char* name, Pokemons evolution, Pokemons evolved_from, Types type, bool legendary = false):Poke(number),name(name),
	evolution(evolution), evolved_from(evolved_from), type(type), legendary(legendary){
		do{
			position.x = rand() % WORLD_SIZE;
			position.y = rand() % WORLD_SIZE;
		} while (!CanBeThere());

		Sprite.x = (number - 1) % 5 * TILE_SIZE;
		Sprite.y = (number - 1) / 5 * TILE_SIZE;
		Sprite.w = Sprite.h = TILE_SIZE;
		pokemon_tex = App->pokemons->Pokemon_sprites;
		siluet_tex = App->pokemons->Pokemon_siluets;

		combat_power = rand() % (App->player->level * 10);
		if (combat_power < 10) combat_power = 10;
	}

	virtual ~Pokemon(){}

	virtual bool CanBeThere(){
		bool ret = false;

		uint zone = *(App->world->World->zonemap + position.x + position.y*WORLD_SIZE);

		switch (type)
		{
		case Normal:
			if (zone > 9) ret = true;
			break;
		case Plant:
			if (zone > 29 && zone < 50) 
				ret = true;
			break;
		case Fire:
			if (zone > 19 && zone < 30)
				ret = true;
			break;
		case Electric:
			if (zone > 9) ret = true;
			break;
		case Water:
			if (zone < 10) ret = true;
			break;
		case Rock:
			if (zone > 9 && zone < 30)
				ret = true;
			break;
		case Psiquic:
			if (zone > 59 && zone < 70)
				ret = true;
			break;
		case Ice:
			if (zone > 49 && zone < 60)
				ret = true;
			break;
		case Dragon:
			if (zone > 19 && zone < 30)
				ret = true;
			break;
		case Poison:
			if (zone > 29 && zone < 40)
				ret = true;
			break;
		}

		return ret;
	}

	virtual void Draw(){
		App->render->Blit(pokemon_tex, position.x*TILE_SIZE, position.y*TILE_SIZE, &Sprite);
	}

private:

};


#endif