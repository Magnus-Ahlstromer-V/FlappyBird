#pragma once
#include <SDL2/SDL_render.h>

enum PipeType
{
	PIPE_GROUND,
	PIPE_CEILING
};

class Pipe
{
public:
	Pipe(int x, int y, int type);

	inline float GetX() const { return m_xPosition; }
	inline float GetY() const { return m_yPosition; }
	inline int GetW() const { return m_width; }
	inline int GetH() const { return m_height; }

	inline void SetX(float x) { m_xPosition = x; }
	inline void SetY(float y) { m_yPosition = y; }

	void Update();
	void Draw(SDL_Renderer* renderer);

private:
	void RigBody(int x, int y, int w, int h);

private:
	float m_xPosition;
	float m_yPosition;
	int m_width;
	int m_height;

	float m_speed;
	int m_type;

	SDL_Rect m_body;
	SDL_Texture* m_texture;
};
