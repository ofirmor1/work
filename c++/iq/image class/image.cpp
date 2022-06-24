#include "image.hpp"
#include <array>
#include <sstream>

#define NOT_IN_RANGE -1;

namespace advcpp
{

Image::Image(size_t a_width, size_t a_height, std::string a_type, int a_colorScale)
: m_width(a_width)
, m_height(a_height)
, m_colorScale(a_colorScale)
, m_type(a_type)
, m_pixels(new int[m_width * m_height])
{
    std::cout << "ctor\n";
}

Image::~Image()
{
    std::cout << "dtor\n";
    delete[] m_pixels;
}

Image::Image(Image const& a_src)
: m_width(a_src.m_width)
, m_height(a_src.m_height)
, m_colorScale(a_src.m_colorScale)
, m_type(a_src.m_type)
, m_pixels(new int[a_src.m_width * a_src.m_height])
{
    std::cout << "cctor\n";
    size_t sourceSize = a_src.m_width * a_src.m_height;
    std::copy(a_src.m_pixels, a_src.m_pixels + sourceSize, m_pixels);
}

Image::Image(Image&& a_src)
: m_width(a_src.m_width)
, m_height(a_src.m_height)
, m_colorScale(a_src.m_colorScale)
, m_type(a_src.m_type)
, m_pixels(a_src.m_pixels)
{
    std::cout << "move cctor\n";
    a_src.m_pixels = nullptr;
    a_src.m_width = 0;
    a_src.m_height = 0;
}

Image& Image::operator=(Image const& a_src)
{
    if(this != &a_src)
    {
        std::cout << "copy assignment ctor\n";
        Image img(a_src);
        std::swap(*this, img);
    }
    return *this;
}

Image& Image::operator=(Image&& a_src)
{
    if(this != &a_src)
    {
        std::cout << "move assignment ctor\n";
        Image img(a_src);
        std::swap(*this, a_src);
    }

    a_src.m_pixels = nullptr;
    return *this; 
}

Image read(std::ifstream& a_inputFile)
{

    // if (!a_inputFile.is_open())
    // {
    //     throw std::runtime_error("unable to open file");
    // }
    size_t scale, val, width, height;
    std::string type;
    a_inputFile >> type >> width >> height >> scale;
    Image img(width, height, type, scale);
    while (!a_inputFile.fail())
    {
        for (size_t i = 0; i < img.getHeight(); ++i)
        {
            for (size_t j = 0; j < img.getWidth(); ++j)
            {
                a_inputFile >> val;
                img.setPixel(i, j, val);
            }
        }
    }
    return img;
}

Image save(Image& a_src, std::ofstream& a_outputFile)
{
    // if (!a_outputFile.is_open())
    // {
    //     throw std::runtime_error("unable to open file");
    // }
    a_outputFile << a_src.getType() << std::endl;
    a_outputFile << a_src.getWidth() << ' ';
    a_outputFile << a_src.getHeight() << std::endl;
    a_outputFile << a_src.getScale() << std::endl;
    for (size_t i = 0; i < a_src.getHeight(); ++i)
    {
        for (size_t j = 0; j < a_src.getWidth(); ++j)
        {
            if(a_src.getPixel(i, j) != 255)
            {
                std::cout << a_src.getPixel(i, j) << ' ';
            }
            
            a_outputFile << a_src.getPixel(i, j) << " ";
        }
        a_outputFile << std::endl;
    }

    return a_src;
}

int Image::getPixel(size_t a_x, size_t a_y) const
{
    if(a_x >= m_width || a_y >= m_height)
    {
        return 0;
    }
    
    return m_pixels[m_width * (a_y) + a_x];
}


void Image::setPixel(size_t a_x, size_t a_y, int a_value)
{
    if(a_x >= m_width || a_y >= m_height)
    {
       return;
    }
    
   m_pixels[m_width * (a_y) + a_x] = a_value;
}

size_t Image::getWidth() const
{
    return m_width;
}

size_t Image::getHeight() const
{
    return m_height;
}

int Image::getScale() const
{
    return m_colorScale;
}

std::string Image::getType() const
{
    return m_type;
}

void Image::setWidth(size_t a_width)
{
    m_width = a_width;
}

void Image::setHeight(size_t a_height)
{
    m_height = a_height;
}

void brighten(Image& a_src, int a_factor)
{
    size_t width = a_src.getWidth();
    size_t height = a_src.getHeight();
    for(size_t i = 0; i < width; ++i)
    {
        for(size_t j = 0; j < height; ++j)
        {
            a_src.setPixel(i, j, a_factor);
        }
    }
}

bool Image::operator==(Image const& a_src)
{
    return m_pixels == a_src.m_pixels;
}

// void sharp(Image& a_src)
// {
//     std::array<int, 9> sharp = {-1,-1,-1,-1,9,-1,-1,-1,-1};

//     for (size_t h = 0; h < a_src.getHeight(); ++h)
//     {
//         for (size_t w = 0; w < a_src.getWidth(); ++w)
//         {
//             /* code */
//         }
        
//     }
    
// }

// size_t Image::operator[](size_t a_index)
// {
//     return m_pixels[a_size]
// }

// void Image::print(std::string a_separator, std::ostream& a_os) const
// {
//     for (auto const& row : m_img)
//     {            
//         for (auto const& col : m_img[0])
//         {
//             a_os << m_img[row][col] << a_separator;
//         }
//         a_os << "\n";
//     }
//     a_os << "\n";
//     return;
// }

} // namespace advcpp
