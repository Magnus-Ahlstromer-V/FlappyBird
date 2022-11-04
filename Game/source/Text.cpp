#include "Text.h"
#include "Global.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

Text::Text(const std::string& text, int fontSize)
{
	m_color.r = 0xFF;
	m_color.g = 0xFF;
	m_color.b = 0xFF;
	m_color.a = 0xFF;

	m_text = text;
	m_fontSize = fontSize;
}

void Text::Display(int x, int y)
{
	m_body.x = x;
	m_body.y = y;
	SDL_RenderCopy(Global.renderer, m_texture, NULL, &m_body);
}

void Text::SetFont(const char* path)
{
	TTF_Font* font = TTF_OpenFont(path, m_fontSize);
	SDL_Surface* surface = TTF_RenderText_Solid(font, m_text.c_str(), m_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Global.renderer, surface);

	m_texture = texture;
	SDL_QueryTexture(m_texture, NULL, NULL, &m_body.w, &m_body.h);

	SDL_FreeSurface(surface);
}

void Text::SetColor(uint8_t r, uint8_t g, uint8_t b)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;	
}
