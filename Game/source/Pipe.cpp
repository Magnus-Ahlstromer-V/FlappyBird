#include "Pipe.h"

Pipe::Pipe(int x, int y)
{
	m_width = 40;
	m_height = 300;
	m_speed = 3;
	m_xPosition = x;
	m_yPosition = y;

	RigBody(m_xPosition, m_yPosition, m_width, m_height);
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
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &m_body);
}
