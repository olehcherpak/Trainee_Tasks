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

    void reserveMemory(const unsigned size);

    void* getMemory(const unsigned& size);
    void freeMemory(void* ptr);

    void* realloc(void* ptr, const unsigned& size);

private:

    std::list<MemoryPart>::iterator cutPart(std::list<MemoryPart>::iterator& iter, const unsigned& size);
    void combine(std::list<MemoryPart>::iterator& iter1, std::list<MemoryPart>::iterator iter2);
    std::list<MemoryPart>::iterator findPart(void* ptr);
    void copy(void* source, void* target, const unsigned& size);

    std::list<MemoryPart> partsList;
    char* memory;
    std::mutex mutex;

};

class out_of_memory_exception {};
class bad_pointer_exception {};
class wrong_size_exception {};
class twice_memory_reservation_exception {};

#endif
