#ifndef __MODULE_H__
#define __MODULE_H__

#include "Globals.h"

struct Collider;

class Module
{
private:
	bool enabled = true;
	bool paused = false;

public:
	virtual ~Module() {}

	virtual bool Init()					{ return true; }
	virtual bool Start()					{ return true; }
	virtual update_status PreUpdate()		{ return update_status::UPDATE_CONTINUE; }
	virtual update_status Update()		{ return update_status::UPDATE_CONTINUE; }
	virtual update_status PostUpdate() 	{ return update_status::UPDATE_CONTINUE; }
	virtual bool CleanUp()				{ return true; }
		
	bool IsEnabled() const				{ return enabled; }
	bool IsPaused() const				{ return paused; }

	void Enable()
	{
		if(enabled == false)
		{
			enabled = true;
			Start();
		}
	}

	void Disable()
	{
		if (enabled == true){
			enabled =false;
			CleanUp();
		}
	}

	void Pause(){
		if (paused == false){
			paused = true;
		}
	}

	void Continue(){
		if (paused == true){
			paused = false;
		}
	}

	//Callbacks ---
	virtual void OnCollision(Collider*, Collider*) {}

};

#endif // __MODULE_H__