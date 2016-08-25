#ifndef _ModulePokemons_H_
#define _ModulePokemons_H_

#include "Globals.h"
#include "Application.h"
#include "Module.h"

#define POKEMON_DIVISIOR 5

enum Pokemons{
	None,
	Bulbasaur, Ivysaur, Venusaur,
	Charmander, Charmeleon, Charizard,
	Squirtle, Wartortle, Blastoise,
	Caterpie, Metapod, Butterfree,
	Weedle, Kakuna, Beedrill,
	Pidgey, Pidgeotto, Pidgeot,
	Rattata, Raticate,
	Spearow, Fearow,
	Ekans, Arbok,
	Pikachu, Raichu,
	Sandshrew, Sandslash,
	Nidoran_f, Nidorina, Nidoqueen,
	Nidoran_m, Nidorino, Nidoking,
	Clefairy, Clefable,
	Vulpix, Ninetales,
	Jigglypuff, Wigglytuff,
	Zubat, Golbat,
	Oddish, Gloom, Vileplume,
	Paras, Parasect,
	Venonat, Venomoth,
	Diglett, Dugtrio,
	Meowth, Persian,
	Psyduck, Golduck,
	Mankey, Primeape,
	Growlithe, Arcanine,
	Poliwag, Poliwhirl, Poliwrath,
	Abra, Kadabra, Alakazam,
	Machop, Machoke, Machamp,
	Bellsprout, Weepinbell, Victreebel,
	Tentacool, Tentacruel,
	Geodude, Graveler, Golem,
	Ponyta, Rapidash,
	Slowpoke, Slowbro,
	Magnemite, Magneton,
	Farfetch’d,
	Doduo, Dodrio,
	Seel, Dewgong,
	Grimer, Muk,
	Shellder, Cloyster,
	Gastly, Haunter, Gengar,
	Onix,
	Drowzee, Hypno,
	Krabby, Kingler,
	Voltorb, Electrode,
	Exeggcute, Exeggutor,
	Cubone, Marowak,
	Hitmonlee,
	Hitmonchan,
	Lickitung,
	Koffing, Weezing,
	Rhyhorn, Rhydon,
	Chansey,
	Tangela,
	Kangaskhan,
	Horsea, Seadra,
	Goldeen, Seaking,
	Staryu, Starmie,
	Mr_Mime,
	Scyther,
	Jynx,
	Electabuzz,
	Magmar,
	Pinsir,
	Tauros,
	Magikarp, Gyarados,
	Lapras,
	Ditto,
	Eevee, Vaporeon, Jolteon, Flareon,
	Porygon,
	Omanyte,
	Omastar,
	Kabuto, Kabutops,
	Aerodactyl,
	Snorlax,
	Articuno,
	Zapdos,
	Moltres,
	Dratini, Dragonair, Dragonite,
	Mewtwo,
	Mew,
	Max_Pokemons,
};

enum Types{
	Normal, Plant, Fire, Electric, Water, Rock, Psiquic, Ice, Dragon, Poison
};

struct SDL_Texture;
class Pokemon;

class ModulePokemons : public Module{
public:
	SDL_Texture* Pokemon_sprites;
	SDL_Texture* Pokemon_siluets;

private:
	Pokemon* spawned[WORLD_SIZE / POKEMON_DIVISIOR];
	uint count = 0;

public:
	ModulePokemons();
	bool Start();
	update_status Update();
	bool CleanUp();


private:
	bool SpawnPokemon();
	Pokemons PokemonToSpawn(Pokemons& random_pokemon);
	bool IsLegendary(Pokemons& pokemon);
	bool IsSecondEvolution(Pokemons& pokemon);
	bool IsEvolution(Pokemons& pokemon);

};

#endif