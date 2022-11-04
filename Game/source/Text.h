#pragma once
#include <SDL2/SDL_render.h>
#include <stdint.h>
#include <string>

class Text
{
public:
	Text(const std::string& text, int fontSize);

	void SetFont(const char* path);
	void SetColor(uint8_t r, uint8_t g, uint8_t b);

	void Display(int x, int y);

	inline int GetW() const { return m_body.w; }
	inline int GetH() const { return m_body.h; }
	inline std::string GetText() const { return m_text; }

	inline void SetText(const std::string& s) { m_text = s; }

private:
	int m_fontSize;
	std::string m_text;
	SDL_Color m_color;
	SDL_Rect m_body;
	SDL_Texture* m_texture;
};
