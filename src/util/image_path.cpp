#include "filesys.h"
#include "util/image_path.h"
#include "util/string.h"
#include <string>

/*
	Replaces the filename extension.
	eg:
		std::string image = "a/image.png"
		replace_ext(image, "jpg")
		-> image = "a/image.jpg"
	Returns true on success.
*/
static bool replace_ext(std::string &path, const char *ext)
{
	if (ext == nullptr)
		return false;

	// Find position of last dot in the string.
	const auto last_dot_pos{ path.find_last_of('.') };
	// If not found, return false.
	if (last_dot_pos == std::string::npos)
		return false;
	// Else make the new path
	path = path.substr(0, last_dot_pos + 1) + ext;
	return true;
}

bool find_correct_image_extension(std::string &full_path,
	const std::string &path_hint)
{
	full_path = path_hint;

	// If there is no extension, add one.
	// If there is an extension, check that path first to save time.
	if (removeStringEnd(full_path, image_constants::image_extensions).empty()) {
		full_path += ".png";
	} else {
		if (fs::PathExists(full_path))
			return true;
	}
	// Substitute image extensions until an existing path is found.
	for(const char *const *ext{ image_constants::image_extensions };
			*ext;
			++ext) {
		replace_ext(full_path, *ext);
		if (fs::PathExists(full_path))
			return true;
	}
	full_path = "";
	return false;
}
