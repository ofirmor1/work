#ifndef BLOCKING_QUEUE_EXCEPTIONS_HPP
#define BLOCKING_QUEUE_EXCEPTIONS_HPP

#include <exception>

namespace mt 
{
class BlockingQueueIsFull : public std::exception {
    public: const char* what() const throw() {return "Queue is full.\n";}
};

class BlockingQueueIsEmpty : public std::exception {
    public: const char* what() const throw() {return "Queue is empty.\n";}
};

}//namespace mt

#endif /*BLOCKING_QUEUE_EXCEPTIONS_HPP*/