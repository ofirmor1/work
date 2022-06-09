#ifndef SORTED_LIST_HXX
#define SORTED_LIST_HXX

namespace cpp
{

template <typename T>
SortedList<T>::SortedList(size_t a_size)
: SortedListBase<T>()
{
    m_elements.reserve(a_size);
}

template <typename T>
SortedList<T>::~SortedList()
{}

template <typename T>
void SortedList<T>::insert(T a_element)
{
    if(m_elements.empty())
    {
        m_elements.push_back(a_element);
    }

    else
    {
        Itr it = m_elements.begin();
        Itr end = m_elements.end();

        while (it != end)
        {
            if(*it > a_element)
            {
                break;
            }
            it++;
        }
        m_elements.insert(it, a_element);
    }
}

template <typename T>
size_t SortedList<T>::fill(T a_element, size_t a_times)
{
    Itr it = std::lower_bound(m_elements.begin(), m_elements.end(), a_element);
    m_elements.insert(it, a_times, a_element);

    return a_times;
}


} // namespace cpp

#endif /*#ifndef SORTED_LIST_HXX*/