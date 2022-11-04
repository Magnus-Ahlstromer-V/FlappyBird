#include "Pipe.h"
#include "TextureManager.h"

Pipe::Pipe(int x, int y, int type)
{
	m_width = 60;
	m_height = 300;
	m_speed = 3;
	m_xPosition = x;
	m_yPosition = y;

	m_type = type;

	RigBody(m_xPosition, m_yPosition, m_width, m_height);
	TextureManager::Get().Load("pipe", "assets/textures/pipe.png");
}

void Pipe::RigBody(int x, int y, int w, int h)
{
	m_body.x = x;
	m_body.y = y;
	m_body.w = w;
	m_body.h = h;
}

void Pipe::Update()
{
	RigBody(m_xPosition, m_yPosition, m_width, m_height);
	m_xPosition -= m_speed;

	if (m_xPosition < -m_width)
		m_xPosition = 800 + m_width;
}

void Pipe::Draw(SDL_Renderer *renderer)
{
	//SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	//SDL_RenderFillRect(renderer, &m_body);
	

	if (m_type == PIPE_GROUND)
		TextureManager::Get().Draw("pipe", m_xPosition, m_yPosition, m_body.w, m_body.h);
	else if (m_type == PIPE_CEILING)
		TextureManager::Get().Draw("pipe", m_xPosition, m_yPosition, m_body.w, m_body.h, 1, SDL_FLIP_VERTICAL);
}
