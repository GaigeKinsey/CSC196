#include "filesystem.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

bool filesystem::file_exists(const char* filename)
{
	fs::path path(filename);

	bool exists = fs::exists(filename) && fs::is_regular_file(filename);

	return exists;
}
