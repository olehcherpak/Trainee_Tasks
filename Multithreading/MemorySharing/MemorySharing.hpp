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

    void* realloc(void*, const int&);

private:

    std::list<MemoryPart>::iterator cutPart(std::list<MemoryPart>::iterator&, const int&);
    void combine(std::list<MemoryPart>::iterator&, std::list<MemoryPart>::iterator);
    std::list<MemoryPart>::iterator findPart(void*);
    void copy(void*, void*, const int&);

    std::list<MemoryPart> partsList;
    char* memory;
    std::mutex* mutex;

};

class out_of_memory_exception {};
class bad_pointer_exception {};
class wrong_size_exception {};

#endif
