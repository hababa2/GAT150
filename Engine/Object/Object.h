#pragma once

namespace nh
{
	class Object
	{
	public:
		virtual ~Object() {}

		virtual void Create() {}
	};
}