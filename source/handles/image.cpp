#include "handles/image.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <fmt/format.h>
#include <stb_image.h>

namespace fractal {
Image::Image(const char* filepath)
{
    data_ = stbi_load(filepath, &width_, &height_, &num_channels_, 0);
    if (data_ == nullptr) {
        throw std::runtime_error(
            fmt::format("Unable to load image from filepath {}", filepath)
        );
    }
}

Image::~Image()
{
    stbi_image_free(data_);
}
} // namespace fractal
