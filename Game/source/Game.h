#pragma once
#include "Bird.h"
#include "Pipe.h"
#include "Text.h"

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	bool Init();
	bool Collide(Bird* bird, Pipe* pipe);
	void Reset();
	void Update();
	void Render();

private:
	int m_width;
	int m_height;
	std::string m_title;
	bool m_gameOver;
	int m_score;

	// Game objects
	Bird* m_bird;
	std::vector<Pipe*> m_groundPipes;
	std::vector<Pipe*> m_ceilingPipes;
	Text* m_gameOverText;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};
