#include "json.h"

#include <fstream>
#include "istreamwrapper.h"

namespace nh
{
	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document) 
		{
			bool success = false; 
			std::ifstream stream(filename);

			if (stream.is_open()) 
			{ 
				rapidjson::IStreamWrapper istream(stream); 
				document.ParseStream(istream);
				success = document.IsObject(); 
			}

			return success; 
		}

		bool Get(const rapidjson::Value& value, const std::string& name, int& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsInt() == false)
			{
				return false;
			}

			data = value[name.c_str()].GetInt();
			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, float& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsNumber() == false)
			{
				return false;
			}

			data = value[name.c_str()].GetFloat();
			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, bool& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsBool() == false)
			{
				return false;
			}

			data = value[name.c_str()].GetBool();
			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsString() == false)
			{
				return false;
			}

			data = value[name.c_str()].GetString();
			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 2)
			{
				return false;
			}
			
			auto& array = value[name.c_str()];
			for (rapidjson::SizeType i = 0; i < array.Size(); i++)
			{
				if (array[i].IsNumber())
				{
					data[i] = array[i].GetFloat();
				}
			}
			
			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, Color& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 3)
			{
				return false;
			}

			auto& array = value[name.c_str()];
			for (rapidjson::SizeType i = 0; i < array.Size(); i++)
			{
				if (array[i].IsNumber())
				{
					data[i] = array[i].GetFloat();
				}
			}

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, SDL_Rect& data)
		{
			if (value.HasMember(name.c_str()) == false || value[name.c_str()].IsArray() == false || value[name.c_str()].Size() != 4)
			{
				return false;
			}

			auto& array = value[name.c_str()];
			for (rapidjson::SizeType i = 0; i < array.Size(); i++)
			{
				if (array[i].IsNumber())
				{
					(&data.x)[i] = array[i].GetFloat();
				}
			}

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data)
		{
			if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
			{
				return false;
			}

			auto& array = value[name.c_str()];
			for (auto& e : array.GetArray())
			{
				data.push_back(e.GetString());
			}

			return true;
		}

		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data)
		{
			if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray())
			{
				return false;
			}

			auto& array = value[name.c_str()];
			for (auto& e : array.GetArray())
			{
				if (e.IsInt())
				{
					data.push_back(e.GetInt());
				}
			}

			return true;
		}
	}
}