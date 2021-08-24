#pragma once

#include "json.h"

namespace nh
{
	class ISerializable
	{
	public:
		virtual ~ISerializable() {};

		virtual bool Write(const rapidjson::Value& value) const = 0;
		virtual bool Read(const rapidjson::Value& value) = 0;
	};
}