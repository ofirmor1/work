#pragma once

#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

namespace advcpp
{

template <typename T>
class Image
{
public:
    Image() = default;
    Image(const size_t a_width, const size_t a_height, const int a_colorScale);
    
    ~Image();
    Image<T>(Image const& a_src);
    Image<T>(Image&& a_src);
    Image<T>& operator=(Image<T> const& a_src);
    Image<T>& operator=(Image<T>&& a_src);

    // void print(std::string a_separator = "\t", std::ostream& a_os = std::cout) const;
    // size_t operator[](size_t a_index);

    size_t getWidth() const;
    size_t getHeight() const;
    int getScale() const;
    T getPixel(size_t a_width, size_t a_height) const;
    void setPixel(size_t a_width, size_t a_height, T a_factor) const;

private:
    size_t m_width;
    size_t m_height;
    int m_colorScale;
    T** m_pixels;
};

template <typename T>
void brighten(Image<T>& a_src, int a_factor);

template <typename T>
Image<T>& read(std::string a_path, Image<T>& a_destImg);

template <typename T>
Image<T>& save(Image<T>& a_src, std::ofstream &outputFile);
} // namespace advcpp
