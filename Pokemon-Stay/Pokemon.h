#ifndef _Pokemon_H_
#define _Pokemon_H_

#include "Globals.h"
#include "MyString.h"
#include "Point2D.h"
#include "Application.h"
#include "ModulePokemons.h"

struct SDL_Texture;

class Pokemon{
public:
	Pokemons Poke;
	MyString name;
	iPoint position;
	
	Pokemons evolved_from = None;
	Pokemons evolution = None;

private:
	SDL_Texture* pokemon_tex;
	SDL_Texture* siluet_tex;
	SDL_Rect Sprite;
	SDL_Rect Siluet;
	uint combat_power;

public:
	Pokemon(Pokemons number, const char* name, int x, int y, Pokemons evolution, Pokemons evolved_from):Poke(number),name(name),
	evolution(evolution), evolved_from(evolved_from){
		position.x = x;
		position.y = y;
		Sprite.x = Siluet.x = (number - 1) % 5 * TILE_SIZE;
		Sprite.y = Siluet.y = (number - 1) / 5 * TILE_SIZE;
		pokemon_tex = App->pokemons->Pokemon_sprites;
		siluet_tex = App->pokemons->Pokemon_siluets;
	}

private:

};


#endif