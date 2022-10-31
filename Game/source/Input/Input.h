#pragma once
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>
#include <cstdint>

struct GInput
{
	int mouseX = 0;
	int mouseY = 0;
	int flags = 0;
	const uint8_t* keys;
};

void HandleEvents();
void SetWindowShouldClose();
bool WindowShouldClose();

extern GInput Input;
