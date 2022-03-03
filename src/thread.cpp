#include "thread.hpp"
#include <cassert>

namespace mt
{

Thread::Thread(funcPtr a_action, void* a_arg)
: m_id(0)
, m_joinable(true)
{
    int r = ::pthread_create(&m_id ,0, a_action, &a_arg);
    assert(r == 0);
}

// Thread::Thread(Thread const& a_th)
// : m_id(a_th.m_id)
// , m_joinable(a_th.m_joinable)
// {
//     Thread& th = const_cast<Thread& > (a_th);
//     th.m_id = 0;
//     th.m_joinable = false;
// }

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
        int r = pthread_join(m_id, 0);
        if(r == 0)
        {
            m_joinable = false;
        }
        assert(r == 0);
    }
    else
    {
        assert(false and "Join failed: already join");
    }
}

void Thread::join(pthread_t a_th)
{
    int r = pthread_join(a_th, 0);
    assert(r == 0);
}

void Thread::detach()
{
if(m_joinable)
    {
        int r = pthread_detach(m_id);
        if(r == 0)
        {
            m_joinable = false;
        }
        assert(r == 0);
    }
    else
    {
        assert(false and "Detach failed: already detached");
    }
}

pthread_t Thread::self()
{
    return pthread_self();
}


}//namespace mt
