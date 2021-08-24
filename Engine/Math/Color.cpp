#include "Color.h"

#include <string>

namespace nh
{
	const Color Color::white	{ 1, 1, 1 };
	const Color Color::black	{ 0.0f, 0.0f, 0.0f };
	const Color Color::red		{ 1.0f, 0.0f, 0.0f };
	const Color Color::green	{ 0.0f, 1.0f, 0.0f };
	const Color Color::blue		{ 0.0f, 0.0f, 1.0f };
	const Color Color::cyan		{ 0.0f, 1.0f, 1.0f };
	const Color Color::yellow	{ 1.0f, 1.0f, 0.0f };
	const Color Color::magenta	{ 1.0f, 0.0f, 1.0f };
	const Color Color::orange	{ 1.0f, 0.5f, 0.0f };

	std::istream& operator>>(std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{", 0) != std::string::npos)
		{
			size_t p1 = line.find('{');
			size_t p2 = line.find(',');
			size_t p3 = line.find(',', p2 + 1);

			std::string r = line.substr(p1 + 1, p2 - p1 - 1);
			std::string g = line.substr(p2 + 1, p3 - p2 - 1);
			std::string b = line.substr(p3 + 1, line.find('}') - p3 - 1);

			c.r = std::stof(r);
			c.g = std::stof(g);
			c.b = std::stof(b);
		}

		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, Color& c)
	{
		std::cout << c.r << ", " << c.g << ", " << c.b << std::endl;

		return stream;
	}
}