#pragma once

#include <span>

namespace fractal {
class Cubemap {
    const unsigned int TEXTURE_ID;

public:
    explicit Cubemap(std::span<const char* const, 6> face_filepaths);
    Cubemap(const Cubemap&) = delete;
    Cubemap(Cubemap&&) = delete;
    Cubemap& operator=(const Cubemap&) = delete;
    Cubemap& operator=(Cubemap&&) = delete;
    ~Cubemap();

    unsigned int get_id() const;
};
} // namespace fractal
