#include "image.hpp"

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
        for (size_t height = 0; height < img.getHeight(); ++height)
        {
            for (size_t width = 0; width < img.getWidth(); ++width)
            {
                a_inputFile >> val;
                img.setPixel(width, height, val);
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
    a_outputFile << a_src.getType();
    a_outputFile << a_src.getWidth();
    a_outputFile << a_src.getHeight();
    a_outputFile << a_src.getScale();

    for (size_t height = 0; height < a_src.getHeight(); ++height)
    {
        for (size_t width = 0; width < a_src.getWidth(); ++width)
        {
            a_outputFile << a_src.getPixel(width, height) << " ";
        }
        a_outputFile << std::endl;
    }

    return a_src;
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
// 1 2 3 // 2 * 3
// 4 5 6
// 1 1 --> 5
// 1 2 3 4 5 6
// 3 * 1 + 1
int Image::getPixel(size_t a_width, size_t a_height) const
{
    if(a_width >= m_width || a_height >= m_height)
    {
        return NOT_IN_RANGE;
    }
    if(a_height == 0)
    {
        return m_pixels[a_width];
    }
    return m_pixels[m_width * (a_height - 1) + a_width];  
}

void Image::setPixel(size_t a_width, size_t a_height, int a_val) const
{
    if(a_width >= m_width || a_height >= m_height)
    {
        return;
    }
    if(a_height == 0)
    {
        m_pixels[a_width] = a_val;
        return;
    }
    if(m_pixels[m_width * (a_height - 1) + a_width] - a_val < 0)
    {
        m_pixels[m_width * (a_height - 1) + a_width] = 0; 
    }

    m_pixels[m_width * (a_height - 1) + a_width] = a_val;
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
