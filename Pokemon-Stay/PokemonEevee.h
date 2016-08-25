#ifndef _PokemonEevee_H_
#define _PokemonEevee_H_

#include "ModulePokemons.h"
#include "Pokemon.h"

class PokemonEevee : public Pokemon{
public:
	Pokemons evolution2 = Jolteon;
	Pokemons evolution3 = Flareon;

public:
	PokemonEevee() : Pokemon(Eevee, "Eevee", Vaporeon, None, Normal){}

};

#endif