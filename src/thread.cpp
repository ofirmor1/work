#include "thread.hpp"
#include <cassert>

namespace mt
{

Thread::Thread(funcPtr a_action)
: m_id(0)
, m_joinable(true)
{
    assert(::pthread_create(&m_id ,0, a_action, 0) == 0);
}

Thread::~Thread()
{
    if(m_joinable) 
    {
		join();
    }
}

void Thread::join()
{
    if(m_joinable)
    {
        assert(pthread_join(m_id, 0) == 0);
        m_joinable = false;
    }
    else
    {
        assert(false and "Join failed: already join");
    }
}

void Thread::join(pthread_t a_th)
{
    assert(pthread_join(a_th, 0) == 0);
}

void Thread::detach()
{
	if(!m_joinable)
	{
		assert(pthread_detach(m_id) == 0);
		m_joinable = false;
	}
}

pthread_t Thread::self()
{
    return pthread_self();
}


}//namespace mt
