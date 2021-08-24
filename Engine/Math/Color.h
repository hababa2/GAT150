#pragma once

#include <iostream>
#include <SDL_ttf.h>

namespace nh
{
	struct Color
	{
		float r, g, b;

		Color() : r{ 0 }, g{ 0 }, b{ 0 } {}
		Color(float r, float g, float b) : r{ r }, g{ g }, b{ b } {}
		Color(std::uint32_t rgb) : r{ (rgb & 0xFF) / 255.f }, g{ (rgb & 0xFF00) / 255.f }, b{ (rgb & 0xFF0000) / 255.f } {}

		float& operator[] (size_t i) { return (&r)[i]; }
		const float operator[] (size_t i) const { return (&r)[i]; }

		Color operator+ (const Color& c) const { return { r + c.r, g + c.g, b + c.b }; }
		Color operator- (const Color& c) const { return { r - c.r, g - c.g, b - c.b }; }
		Color operator* (float s) const { return { r * s, g * s, b * s }; }

		friend std::istream& operator>> (std::istream& stream, Color& c);
		friend std::ostream& operator<< (std::ostream& stream, Color& c);

		operator std::uint32_t() const { return ToRGB(); }
		operator SDL_Color() const { return ToSDL_Color(); }

		std::uint32_t ToRGB() const
		{
			std::uint8_t red = static_cast<std::uint8_t>(r * 255);
			std::uint8_t green = static_cast<std::uint8_t>(g * 255);
			std::uint8_t blue = static_cast<std::uint8_t>(b * 255);
			return red | (green << 8) | (blue << 16);
		}

		SDL_Color ToSDL_Color() const
		{
			std::uint8_t red = static_cast<std::uint8_t>(r * 255);
			std::uint8_t green = static_cast<std::uint8_t>(g * 255);
			std::uint8_t blue = static_cast<std::uint8_t>(b * 255);
			std::uint8_t alpha = 255;

			return SDL_Color{ red, green, blue, alpha };
		}

		static const Color white;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color cyan;
		static const Color yellow;
		static const Color magenta;
		static const Color orange;
	};
}