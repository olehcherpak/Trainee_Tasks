#ifndef MEMORYSHARING_HPP
#define MEMORYSHARING_HPP

#include <list>
#include <mutex>
#include "MemoryPart.hpp"

class MemorySharing
{
public:

    MemorySharing();
    ~MemorySharing();

    void reserveMemory(const int&);
    void releaseMemory();

    void* getMemory(const int&);
    void freeMemory(void*);

private:

    void* cutPart(std::list<MemoryPart>::iterator&, const int&);
    void combine(std::list<MemoryPart>::iterator&);

    std::list<MemoryPart> partsList;
    char* memory;
    std::mutex* mutex;

};

class out_of_memory_exception {};
class bad_pointer_exception {};
class wrong_size_exception {};

#endif
