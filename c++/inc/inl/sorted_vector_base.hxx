#ifndef SORTED_VECTOR_BASE_HXX
#define SORTED_VECTOR_BASE_HXX

namespace cpp
{

template <typename T>
SortedVectorBase<T>::SortedVectorBase(size_t a_size)
: SortedContainer<T>()
{}

template <typename T>
SortedVectorBase<T>::~SortedVectorBase()
{}

template <typename T>
size_t SortedVectorBase<T>::contains(T a_element) const
{
    ConstItr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_element);
    ConstItr end = m_elements.end();

    size_t count = 0;
    while(it != end && (*it) == a_element)
    {
        ++count;
        ++it;
    }

    return count;
}

template <typename T>
size_t SortedVectorBase<T>::remove(T a_element)
{
    size_t count = 0;
    if(m_elements.empty())
    {
        return count;
    }
    
    Itr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_element);
    Itr end = m_elements.end();

    while(it != end && *it == a_element)
    {
        it = m_elements.erase(it);
        end = m_elements.end();
        ++count;
    }

    return count;
}

template <typename T>
T const& SortedVectorBase<T>::front() const
{
    return m_elements.front();
}

template <typename T>
T const& SortedVectorBase<T>::back() const
{
    return m_elements.back();
}

template <typename T>
std::ostream& SortedVectorBase<T>::print(std::ostream& a_os) const
{
    return printContainer(m_elements, a_os);
}

template <typename T>
size_t SortedVectorBase<T>::size() const
{
    return m_elements.size();
}

} // end of namespace cpp

#endif /*#ifndef SORTED_VECTOR_BASE_HXX*/