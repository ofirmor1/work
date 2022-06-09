#ifndef BLOCKING_QUEUE_EXCEPTIONS_HPP
#define BLOCKING_QUEUE_EXCEPTIONS_HPP

#include <exception>

namespace mt 
{
    
class BlockingQueueExceptions : public std::runtime_error {
    public: BlockingQueueExceptions(const std::string& what = "") : std::runtime_error(what) {}
};

class BlockingQueueIsFull : public BlockingQueueExceptions {
    public: const char* what() const throw() {return "Queue is full.\n";}
};

class BlockingQueueIsEmpty : public BlockingQueueExceptions {
    public: const char* what() const throw() {return "Queue is empty.\n";}
};

}//namespace mt

#endif /*BLOCKING_QUEUE_EXCEPTIONS_HPP*/