#include "Input.h"
#include <SDL2/SDL_events.h>

GInput Input;

void HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	Input.keys = SDL_GetKeyboardState(NULL);
	SDL_GetMouseState(&Input.mouseX, &Input.mouseY);

	switch (event.type)
	{
		// TODO: Add mouse pressed and mouse down

		case SDL_QUIT:
			SetWindowShouldClose();
			break;
	}

}

void SetWindowShouldClose()
{
	Input.flags |= (1 << 0); // Set quit flag on
}

bool WindowShouldClose()
{
	return (Input.flags & (1 << 0));
}
