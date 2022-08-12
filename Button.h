#include "SDL.h"

//The button
class Button
{
private:
	//The attributes of the button
	SDL_Rect box;
	
	bool buttonPressed;

public:
	//Initialize the variables
	Button(int x, int y, int w, int h);

	//Handles events and set the button's sprite region
	void handle_events(SDL_Event e);

	//Shows the button on the screen
	void show(SDL_Surface *buttonSurface, SDL_Surface *screen);

	//setter
	void set_x(int x);
	void set_y(int x);
	void set_w(int x);
	void set_h(int x);

	//getter
	int get_x();
	int get_y();
	int get_w();
	int get_h();
	
	void setButtonPressed(bool isPressed);
	int getButtonPressed();
};
