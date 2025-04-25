#pragma once

namespace fractal {

class Image {
    unsigned char* data_{};
    int width_{};
    int height_{};
    int num_channels_{};

public:
    explicit Image(const char* filepath);

    Image(const Image&) = delete;
    Image(Image&&) = delete;
    Image& operator=(const Image&) = delete;
    Image& operator=(Image&&) = delete;

    ~Image();

    unsigned char*
    get_data() const
    {
        return data_;
    }

    int
    get_width() const
    {
        return width_;
    }

    int
    get_height() const
    {
        return height_;
    }
};
} // namespace fractal
