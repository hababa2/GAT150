#include "FileSystem.h"

#include <filesystem>

namespace nh
{
	void SetFilePath(const std::string& pathname)
	{
		std::filesystem::current_path(pathname);
	}

	std::string GetFilePath()
	{
		return std::filesystem::current_path().string();
	}
}