#ifndef THREAD_HPP
#define THREAD_HPP

#include<pthread.h>

namespace mt
{

class Thread 
{
    
public:

    typedef void*(*funcPtr)(void*);

    Thread(funcPtr a_action, void* a_arg);

    // Thread(Thread const& a_th);
    ~Thread();

    void join();
    void detach();

    static void join(pthread_t a_th);
    static pthread_t self();
        
private:
    pthread_t m_id;
    bool m_joinable;
};    


}//namespace mt

#endif /*#ifndef THREAD_HPP*/