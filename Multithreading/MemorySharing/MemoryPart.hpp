#ifndef MEMORYPART_HPP
#define MEMORYPART_HPP

#include <mutex>

class MemoryPart
{
public:
    MemoryPart(char*, const int&);
    ~MemoryPart();
    bool free() const;
    void makeBusy();
    void makeFree();
    int getLength() const;
    void setLength(const int&);
    char* getPtr() const;
    void setPtr(char*);

private:
    char* startPtr;
    int length;
    bool status;
    std::mutex* mutex;
};

#endif
