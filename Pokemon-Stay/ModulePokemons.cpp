#include "Globals.h"
#include "Application.h"
#include "Pokemon.h"
#include "ModulePokemons.h"
#include "ModuleTextures.h"

//Pokemons includes

ModulePokemons::ModulePokemons(){}

bool ModulePokemons::Start(){

	LOG("Module Pokemons Start ......");

	Pokemon_sprites = App->textures->Load("PokemonStay/Sprites/Pokemons/pokemon_sprites.png");
	Pokemon_siluets = App->textures->Load("PokemonStay/Sprites/Pokemons/pokemon_siluets.png");

	return true;
}

bool ModulePokemons::CleanUp(){

	LOG("Module Pokemons CleanUp ......");

	App->textures->Unload(Pokemon_sprites);
	App->textures->Unload(Pokemon_siluets);

	return true;
}