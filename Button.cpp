#include "Button.h"

Button::Button(int x, int y, int w, int h)
{
	//Set the button's attributes
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;

	//Set the default mode
	buttonPressed = false;
}

void Button::handle_events(SDL_Event event)
{
	//The mouse offsets
	int x = 0, y = 0;

	/*
	//If the mouse moved
	if (event.type == SDL_MOUSEMOTION)
	{
		//Get the mouse offsets
		x = event.motion.x;
		y = event.motion.y;

		//If the mouse is over the button
		if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
		{
			//Set the button sprite
			mode = 0;
		}
		//If not
		else
		{
			//Set the button sprite
			mode = 1;
		}
	}
	*/

	//If a mouse button was pressed
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		//If the left mouse button was pressed
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			//Get the mouse offsets
			x = event.button.x;
			y = event.button.y;

			//If the mouse is over the button
			if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
			{
				buttonPressed = true;
			}
		}
	}
	//If a mouse button was released
	if (event.type == SDL_MOUSEBUTTONUP)
	{
		//If the left mouse button was released
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			//Get the mouse offsets
			x = event.button.x;
			y = event.button.y;

			//If the mouse is over the button
			if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
			{
				buttonPressed = false;
			}
		}
	}
}

void Button::set_x(int x)
{
	box.x = x;
}
void Button::set_y(int y)
{
	box.y = y;
}
void Button::set_w(int w)
{
	box.w = w;
}
void Button::set_h(int h)
{
	box.h = h;
}

int Button::get_x()
{
	return box.x;
}
int Button::get_y()
{
	return box.y;
}
int Button::get_w()
{
	return box.w;
}
int Button::get_h()
{
	return box.h;
}

void Button::show(SDL_Surface *buttonSurface, SDL_Surface *screen)
{
	//Show the button
	SDL_Rect dest;
	dest.x = box.x;
	dest.y = box.y;

	SDL_BlitSurface(buttonSurface, NULL, screen, &dest);
}

void Button::setButtonPressed(bool isPressed)
{
	buttonPressed = isPressed;
}

int Button::getButtonPressed()
{
	return buttonPressed;
}