#include "mutex.hpp"
#include "mutex_exceptions.hpp"
#include <cassert>
#include <errno.h>

namespace mt
{

Mutex::Mutex()
{ 
	int res = pthread_mutex_init(&m_mtx, 0);
	if(res)
	{
		assert(res != EINVAL);
		switch (res)
		{
		case EAGAIN:
			throw MutexLackResources();
			break;
		case EPERM:
			throw MutexPremissionUnmatch();
			break;
		case ENOMEM:
			throw MutexLackMemory();
			break;
		default:
			assert (!"pthread_mutex_init failed");
		}
	}
}

Mutex::~Mutex()
{ 
    int res = pthread_mutex_destroy(&m_mtx);
	if(res)
	{
		assert(res != EBUSY);
		assert(res != EINVAL);
		assert (!"pthread_mutex_init failed");
	}
}

void Mutex::lock()
{ 
    int res = pthread_mutex_lock(&m_mtx);
	if(res)
	{
		assert(res != EAGAIN);
		assert(res != EINVAL);
		if(res == EDEADLK)
		{
			throw MutexAllreadyLocked();
		}
		else
		{
			assert(!"pthread_mutex_lock failed");
		}
	}
}

void Mutex::unlock()
{ 
    int res = pthread_mutex_unlock(&m_mtx);
	if(res)
	{
		switch (res)
		{
		case EPERM:
			throw MutexLockedByOtherThread();
			break;
		case EDEADLK:
			throw MutexAllreadyUnlocked();
			break;
		default:
			assert(!"pthread_mutex_unlock failed");
		}
	}
}

}//namespace mt