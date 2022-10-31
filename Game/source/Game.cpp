#include "Game.h"
#include "Input/Input.h"

#include <time.h>
#include <stdlib.h>

Game::Game()
{
	m_width = 800;
	m_height = 450;
	m_title = "Flappy Bird";
	m_gameOver = false;

	srand(time(NULL));

	if (!Init()) return;

	m_bird = new Bird();
	
	for (int i = 0; i < 4; i++)
	{
		m_groundPipes.push_back(new Pipe(225*i + 800, rand() % 250 + 200));
		m_ceilingPipes.push_back(new Pipe(m_groundPipes[i]->GetX(), m_groundPipes[i]->GetY() - 450));	
	}
}

Game::~Game()
{
	delete m_bird;

	for (Pipe* pipe : m_groundPipes)
		delete pipe;

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

bool Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	return true;
}

bool Game::Collide(Bird* bird, Pipe* pipe)
{
	return bird->GetX() + bird->GetW() > pipe->GetX() && bird->GetX() < pipe->GetX() + pipe->GetW() &&
			bird->GetY() + bird->GetH() > pipe->GetY() && bird->GetY() < pipe->GetY() + pipe->GetH();
}

void Game::Reset()
{
	m_gameOver = false;

	m_bird->SetX(80.f);
	m_bird->SetY(450.f / 2.f - m_bird->GetH());
	m_bird->SetVelocity(-7.f);

	for (int i = 0; i < 4; i++)
	{
		m_groundPipes[i]->SetX(225 * i + 800);
		m_groundPipes[i]->SetY(rand() % 250 + 200);
		m_ceilingPipes[i]->SetX(m_groundPipes[i]->GetX());
		m_ceilingPipes[i]->SetY(m_groundPipes[i]->GetY() - 450);
	}
}

void Game::Update()
{
	HandleEvents();

	if (!m_gameOver)
	{
		m_bird->Update();
	
		for (int i = 0; i < 4; i++)
		{
			m_groundPipes[i]->Update();
			m_ceilingPipes[i]->Update();

			if (Collide(m_bird, m_groundPipes[i])) m_gameOver = true;
			if (Collide(m_bird, m_ceilingPipes[i])) m_gameOver = true;
			if (m_bird->GetY() + m_bird->GetH() > 450.f) m_gameOver = true;
		}
	}
	else
	{
		if (Input.keys[SDL_SCANCODE_R])
		{
			Reset();
		}
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 0x00, 0x11, 0x22, 0xFF);
	SDL_RenderClear(m_renderer);

	m_bird->Draw(m_renderer);
	
	for (int i = 0; i < 4; i++)
	{
		m_groundPipes[i]->Draw(m_renderer);
		m_ceilingPipes[i]->Draw(m_renderer);
	}

	SDL_RenderPresent(m_renderer);
}

void Game::Run()
{
	while (!WindowShouldClose())
	{
		uint32_t frameStart = SDL_GetTicks();

		Update();
		Render();

		int frameTime = SDL_GetTicks() - frameStart;

		if (1000 / 60 > frameTime)
			SDL_Delay(1000 / 60 - frameTime);
	}
}
