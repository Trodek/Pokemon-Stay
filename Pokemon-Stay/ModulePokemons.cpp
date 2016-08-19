#include "Globals.h"
#include "Application.h"
#include "Pokemon.h"
#include "ModulePokemons.h"
#include "ModuleTextures.h"

//Pokemons includes

ModulePokemons::ModulePokemons(){}

bool ModulePokemons::Start(){
	Pokemon_sprites = App->textures->Load("PokemonStay/Sprites/Pokemons/pokemon_sprites.png");
	Pokemon_siluets = App->textures->Load("PokemonStay/Sprites/Pokemons/pokemon_siluets.png");

	return true;
}
