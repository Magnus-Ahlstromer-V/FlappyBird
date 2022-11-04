#pragma once
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>

#include <pthread.h>
class TextureManager
{
public:
	static inline TextureManager& Get() { static TextureManager instance; return instance; }

	void Load(const std::string& id, const char* path);
	void Drop(const std::string& id);
	void Draw(const std::string& id, int x, int y, int w, int h, int scale = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	TextureManager();
	~TextureManager();

private:
	std::unordered_map<std::string, SDL_Texture*> m_textureMap;
};
