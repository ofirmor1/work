#ifndef MUTEX_EXCEPTIONS_HPP
#define MUTEX_EXCEPTIONS_HPP

#include <exception>

namespace mt 
{

class MutexLackResources : public std::exception {
    virtual const char* what() const throw() {return "Lack resources to initialize another Mutex.\n";}
};

class MutexLackMemory : public std::exception {
    virtual const char* what() const throw() {return "Lack memory to initialize the Mutex\n";}
};

class MutexPremissionUnmatch : public std::exception {
    virtual const char* what() const throw() {return "Does not have the privilege to create Mutex.\n";}
};

class MutexDestoryingBusyMutex : public std::exception {
    virtual const char* what() const throw() {return "Attempt to destroy a busy Mutex\n";}
};

class MutexMaxNumRecursiveLocks : public std::exception {
    virtual const char* what() const throw() {return "Maximum number of recursive locks has been exceeded.\n";}
};

class MutexNotRecoverable : public std::exception {
    virtual const char* what() const throw() {return "The state protected by the Mutex is not recoverable.\n";}
};

class MutexAllreadyLocked : public std::exception {
    virtual const char* what() const throw() {return "Trying to lock a locked Mutex\n";}
};

class MutexLockedByOtherThread : public std::exception {
    virtual const char* what() const throw() {return "Mutex is locked by other thread\n";}
};

class MutexAllreadyUnlocked : public std::exception {
    virtual const char* what() const throw() {return "Trying to unlock an unlocked Mutex\n";}
};

}//namespace mt

#endif /*MUTEX_EXCEPTIONS_HPP*/