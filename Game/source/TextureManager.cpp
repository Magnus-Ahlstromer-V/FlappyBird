#include "TextureManager.h"
#include "Global.h"

#include <SDL2/SDL_image.h>
#include <stdio.h>

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	std::unordered_map<std::string, SDL_Texture*>::iterator it;

	for (it = m_textureMap.begin(); it != m_textureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}

	m_textureMap.clear();
}


void TextureManager::Load(const std::string& id, const char* path)
{
	SDL_Surface* surface = IMG_Load(path);

	if (!surface)
		puts("Failed to load texture");

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Global.renderer, surface);
	m_textureMap[id] = texture;
}

void TextureManager::Drop(const std::string& id)
{
	SDL_DestroyTexture(m_textureMap[id]);
	m_textureMap.erase(id);
}

void TextureManager::Draw(const std::string& id, int x, int y, int w, int h, int scale, SDL_RendererFlip flip)
{
	SDL_Rect source = { 0, 0, w, h };
	SDL_Rect dest = { x, y, w * scale, h * scale };
	SDL_RenderCopyEx(Global.renderer, m_textureMap[id], &source, &dest, 0, NULL, flip);
}


