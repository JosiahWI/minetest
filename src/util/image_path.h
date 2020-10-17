#pragma once

#include <string>

namespace image_constants {
	/// Define an array of image extensions ordered roughly by commonness.
	/// We use a sentinel value of nullptr so we don't have to store a length.
	constexpr const char *image_extensions[]{
		"png", "jgp", "bmp", "tga", "pcx", "ppm", "psd", "wal", "rgb", nullptr};
}

/**
  * Find the full path to a file by trying different image extensions.
  *
  *	@param full_path Is set to the first path found, or to "" if none was found.
  *	@param path_hint The image path to look for.
*/
void find_correct_image_extension(std::string &full_path,
	const std::string &path_hint);
