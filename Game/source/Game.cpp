#include "Game.h"
#include "Input/Input.h"
#include "Global.h"
#include "Pipe.h"
#include "TextureManager.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include <stdlib.h>

Game::Game()
{
	m_width = 800;
	m_height = 450;
	m_title = "Flappy Bird";
	m_gameOver = false;
	m_score = 0;

	srand(time(NULL));

	if (!Init()) return;

	m_bird = new Bird();
	
	for (int i = 0; i < 4; i++)
	{
		m_groundPipes.push_back(new Pipe(225*i + 800, rand() % 250 + 200, PIPE_GROUND));
		m_ceilingPipes.push_back(new Pipe(m_groundPipes[i]->GetX(), m_groundPipes[i]->GetY() - 450, PIPE_CEILING));	
	}

	m_gameOverText = new Text("Game Over! Press R to restart", 32);
	m_gameOverText->SetColor(0xFF, 0x00, 0x00);
	m_gameOverText->SetFont("assets/fonts/font.ttf");

	TextureManager::Get().Load("bg", "assets/textures/bg.png");
}

Game::~Game()
{
	delete m_bird;
	delete m_gameOverText;

	for (Pipe* pipe : m_groundPipes)
		delete pipe;

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(Global.renderer);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Game::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();

	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0);
	Global.renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

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
	m_score = 0;

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

	if (Input.keys[SDL_SCANCODE_ESCAPE])
		SetWindowShouldClose();

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

			if (m_bird->GetX() == m_groundPipes[i]->GetX())
				m_score++;

			
		}
	}
	else
	{
		if (Input.keys[SDL_SCANCODE_R])
			Reset();
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(Global.renderer, 0x00, 0x11, 0x22, 0xFF);
	SDL_RenderClear(Global.renderer);

	TextureManager::Get().Draw("bg", 0, -800, 288, 512, 3);

	m_bird->Draw();
	
	for (int i = 0; i < 4; i++)
	{
		m_groundPipes[i]->Draw(Global.renderer);
		m_ceilingPipes[i]->Draw(Global.renderer);
	}

	if (m_gameOver)
		m_gameOverText->Display(m_width / 2 - m_gameOverText->GetW() / 2, 300);

	SDL_RenderPresent(Global.renderer);
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
