#ifndef THREAD_EXCEPTIONS_HPP
#define THREAD_EXCEPTIONS_HPP

#include <exception>

namespace mt {

class ThreadLackResourcesException : public std::exception {
    virtual const char* what() const throw(){return "Lack of resources to create another Thread.\n";}
};

class ThreadInvalidPremissionsException : public std::exception {
    virtual const char* what() const throw(){return "Invalid permission to create another Thread.\n";}
};

class ThreadInvalidAttrSettings : public std::exception {
    virtual const char* what() const throw(){return "Invalid settings in attr.\n";}
};

class ThreadDeadLockDetected : public std::exception {
    virtual const char* what() const throw(){return "A deadlock was detected.\n";}
};

class ThreadBusyWaitingException : public std::exception {
    virtual const char* what() const throw(){return "Another thread is already waiting to join with this thread.\n";}
};

class ThreadNotJoinableException : public std::exception {
    virtual const char* what() const throw(){return "Thread is not a joinable thread.\n";}
};

class ThreadIDNotFound : public std::exception {
    virtual const char* what() const throw(){return "No Thread with the ID thread could be found.\n";}
};


}//namespace mt

#endif /*THREAD_EXCEPTIONS_HPP*/