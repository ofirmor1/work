#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

namespace advcpp
{

class Image
{
public:
    Image() = default;
    Image(size_t a_width, size_t a_height, std::string a_type, int a_colorScale);
    
    ~Image();
    Image(Image const& a_src);
    Image& operator=(Image const& a_src);

    Image(Image&& a_src);
    Image& operator=(Image&& a_src);

    // void print(std::string a_separator = "\t", std::ostream& a_os = std::cout) const;
    // size_t operator[](size_t a_index);

    size_t getWidth() const;
    size_t getHeight() const;
    int getScale() const;
    std::string getType() const;

    void setWidth(size_t a_width);
    void setHeight(size_t a_height);
    
    int getPixel(size_t a_width, size_t a_height) const;
    void setPixel(size_t a_width, size_t a_height, int a_factor) const;
    // void setPixel(size_t a_width, size_t a_height, int a_factor) const;

    bool operator==(Image const& a_src);

private:
    size_t m_width;
    size_t m_height;
    int m_colorScale;
    std::string m_type;
    int* m_pixels;
};

void brighten(Image& a_src, int a_factor);

Image read(std::ifstream& a_inputFile);

Image save(Image& a_src, std::ofstream& a_outputFile);
} // namespace advcpp
