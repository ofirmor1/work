#include "image.hpp"

namespace advcpp
{
template <typename T>
Image<T>::Image(const size_t a_width, const size_t a_height, const int a_colorScale)
: m_width(a_width)
, m_height(a_height)
, m_colorScale(a_colorScale)
{
    m_pixels = new T * [a_width];
    for(auto row : m_pixels)
    {
        row = new T[a_height];
    }
}

template <typename T>
Image<T>::~Image()
{
    for (size_t i = 0; i < m_height; ++i)
    {
        delete[] m_pixels[i];
    }

    delete[] m_pixels;
}

template <typename T>
Image<T>::Image(Image<T> const& a_src)
: m_width(a_src.m_width)
, m_height(a_src.m_height)
, m_colorScale(a_src.m_colorScale)
{
    m_pixels = new T * [a_width];
    for(auto row : m_pixels)
    {
        row = new T[a_height];
        std::copy(a_src.m_pixels[i], a_src.m_pixels[i] + m_height, m_pixels[i]);
    }
}

template <typename T>
Image<T>::Image(Image&& a_src)
: m_width(a_src.m_width)
, m_height(a_src.m_height)
, m_colorScale(a_src.m_colorScale)
, m_pixels(a_src.m_pixels)
{
   a_src.m_pixels = nullptr;
}

template <typename T>
Image<T>& Image<T>::operator=(Image<T> const& a_src)
{
    if(this != &a_source)
    {
        Image img(a_source);
        std::swap(m_pixels, img);
    }
    return *this;
}

template <typename T>
Image<T>& operator=(Image<T>&& a_src)
{
    if(this != &a_source)
    {
        Image img(a_source);
        std::swap(m_pixels, img);
    }

    a_src.m_pixels = nullptr;
    return *this; 
}

// template <typename T>
// void brighten(Image<T> a_source);

template <typename T>
Image<T>& read(std::string a_path, Image<T>& a_destImg)
{
    size_t width, height;
    std::string type;
    std::ifstream file;
    file.open(a_path, std::ios::in | std::ios::binary);
    file.seekg(0, std::ios::beg);
    for (size_t row = 0; row < a_destImg.getWidth(); ++row)
    {
        for (size_t col = 0; col < a_destImg.getHeight(); ++col)
        {
            file.read(reinterpret_cast<char*>(m_pixels[row][col]), a_destImg.getWidth());
        }
    }
    file.close();
}

template <typename T>
Image<T>& save(Image<T>& a_src, std::ofstream &outputFile)
{
    
    std::ostream outputFile;
    outputFile.open(a_path, std::ios::out | std::ios::binary | std::ios::trunc);
    std::string type;
    outputFile << type;
    outputFile << a_src.getWidth();
    outputFile << a_src.getHeight();
    outputFile << a_src.getScale();
    file.seekg(0, std::ios::beg);
    for (size_t row = 0; row < a_destImg.getWidth(); ++row)
    {
        for (size_t col = 0; col < a_destImg.getHeight(); ++col)
        {
            outputFile.write(reinterpret_cast<char*>(m_pixels[row][col]), a_destImg.getWidth());
        }
    }
    file.close();
}

// template <typename T>
// size_t Image<T>::operator[](size_t a_index)
// {
//     return m_pixels[a_size]
// }

// template <typename T>
// void Image<T>::print(std::string a_separator, std::ostream& a_os) const
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

template <typename T>
size_t Image<T>::getWidth() const
{
    return m_width;
}

template <typename T>
size_t Image<T>::getHeight() const
{
    return m_height;
}

template <typename T>
int Image<T>::getScale() const
{
    return m_colorScale;
}

template <typename T>
T Image<T>::getPixel(size_t a_width, size_t a_height) const
{
    if(a_width >= m_width || a_height >= m_height)
    {
        std::cout << "not in rage" << std::endl;
        return m_pixels[m_width - 1][m_height - 1];
    }

    return m_pixels[a_width][a_height]; 
}

template <typename T>
void Image<T>::setPixel(size_t a_width, size_t a_height, T a_factor) const
{
    if(a_width >= m_width || a_height >= m_height)
    {
        std::cout << "not in rage" << std::endl;
        return;
    }
    m_pixels[a_width][a_height] = getPixel(a_width, a_height) - a_factor;
}

template<typename T>
void brighten(Image<T>& a_src, T a_factor)
{
    size_t width = getWidth();
    size_t height = getHeight();
    for(size_t i = 0; i < width; ++i)
    {
        for(size_t j = 0; j < height; ++j)
        {
            a_src.setPixel(i, j, a_factor);
        }
    }
}

} // namespace advcpp
