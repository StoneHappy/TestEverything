#include <libheif/heif.h>
#include <iostream>
#include "ReadHeif.h"

#define LIBHEIF_TEST_ERROR(func, ...) if ((func) != heif_error_code::heif_error_Ok) {std::cout << __VA_ARGS__ << std::endl; return false;}


bool ReadHeif(const char* filename)
{
	heif_context* ctx = heif_context_alloc();
	LIBHEIF_TEST_ERROR(heif_context_read_from_file(ctx, filename, nullptr).code, "File read error!")

	// get a handle to the primary image
	heif_image_handle* handle;
	LIBHEIF_TEST_ERROR(heif_context_get_primary_image_handle(ctx, &handle).code, "Get image handle error")

	// decode the image and convert colorspace to RGB, saved as 24bit interleaved
	heif_image* img;
	LIBHEIF_TEST_ERROR(heif_decode_image(handle, &img, heif_colorspace_RGB, heif_chroma_interleaved_RGB, nullptr).code, "Decode image error")

	auto width = heif_image_get_primary_width(img);
	auto height = heif_image_get_primary_height(img);

	std::cout << "Get image info: " << std::endl;
	std::cout << "width: " << width << std::endl;
	std::cout << "height: " << height << std::endl;

	int stride;
	const uint8_t* data = heif_image_get_plane_readonly(img, heif_channel_interleaved, &stride);

	if (stride == NULL)
	{
		std::cout << "Get image data error!" << std::endl;
		return false;
	}

	std::cout << "Read image successfully!" << std::endl;
	return true;
}