#pragma once
#include <SDL2/SDL_render.h>

class Bird
{
public:
	Bird();

	inline float GetX() const { return m_xPosition; }
	inline float GetY() const { return m_yPosition; }
	inline int GetW() const { return m_width; }
	inline int GetH() const { return m_height; }

	inline void SetX(float x) { m_xPosition = x; }
	inline void SetY(float y) { m_yPosition = y; }
	inline void SetVelocity(float v) { m_velocity = v; }

	void Update();
	void Draw(SDL_Renderer* renderer);

private:
	void RigBody(int x, int y, int w, int h);

private:
	float m_xPosition;
	float m_yPosition;
	int m_width;
	int m_height;

	float m_velocity;

	SDL_Rect m_body;
	SDL_Texture* m_texture;
};
