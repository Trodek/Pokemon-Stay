#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"


#define NUM_MODULES 8


class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleFadeToBlack;
class ModuleAudio;
class ModuleCollision;
class ModuleFonts;
class Module;



class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleCollision* collisions;
	ModuleFonts* fonts;
	


public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	Module* current_level=nullptr;

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__