#include "Bird.h"
#include "Input/Input.h"
#include "TextureManager.h"

Bird::Bird()
{
	m_width = 34;
	m_height = 24;
	m_xPosition = 80.f;
	m_yPosition = 450.f / 2.f - m_height;
	m_velocity = -7.f;

	RigBody(m_xPosition, m_yPosition, m_width, m_height);
	TextureManager::Get().Load("bird", "assets/textures/bird.png");
	
}

void Bird::RigBody(int x, int y, int w, int h)
{
	m_body.x = x;
	m_body.y = y;
	m_body.w = w;
	m_body.h = h;
}

void Bird::Update()
{
	RigBody(m_xPosition, m_yPosition, m_width, m_height);

	m_velocity += 0.5;
	m_yPosition += m_velocity;

	if (m_yPosition >= 0.f)
	{
		if (Input.keys[SDL_SCANCODE_SPACE])
			m_velocity = -7;
	}
	else
	{
		m_yPosition = 0.f;
	}
}

void Bird::Draw(SDL_Renderer* renderer)
{	
	TextureManager::Get().Draw("bird", m_xPosition, m_yPosition, m_body.w, m_body.h, 2);
}
