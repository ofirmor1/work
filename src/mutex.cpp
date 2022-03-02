#include "mutex.hpp"
#include <cassert>

namespace mt
{

Mutex::Mutex()
: m_isLock(false)
{ 
    assert(pthread_mutex_init(&m_mtx, 0) == 0);
}

Mutex::~Mutex()
{ 
    if(pthread_mutex_destroy(&m_mtx))
	{
		assert(false and "mutex destroy fail");
	}
}

void Mutex::lock()
{ 
    assert(pthread_mutex_lock(&m_mtx) == 0);
	m_isLock = true;
}

void Mutex::unlock()
{ 
    assert(pthread_mutex_unlock(&m_mtx) == 0);
	m_isLock = false;
}

bool Mutex::isLock() const
{
	return m_isLock;
}

}//namespace mt