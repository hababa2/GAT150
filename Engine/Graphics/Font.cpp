#include "Font.h"

#include <cassert>

namespace nh
{
	Font::~Font()
	{
		if (font)
		{ 
			//Close Font
		}
	}

	bool Font::Load(const std::string& name, void* data)
	{
		assert(data);
		font = TTF_OpenFont(name.c_str(), *(reinterpret_cast<int*>(data)));

		if (font == nullptr) 
		{ 
			std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl; 
			return false;
		}

		return true;
	}

	SDL_Surface* Font::CreateSurface(const std::string& text, const nh::Color& color)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

		if (surface == nullptr)
		{ 
			std::cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl; 
		}

		return surface;
	}
}