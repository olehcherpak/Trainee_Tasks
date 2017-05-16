#ifndef MEMORYPART_HPP
#define MEMORYPART_HPP

class MemoryPart
{
public:
    MemoryPart(char* start, const unsigned& size);
    ~MemoryPart();
    bool isFree() const;
    void makeBusy();
    void makeFree();
    unsigned getLength() const;
    void setLength(const unsigned& newLength);
    char* getPtr() const;
    void setPtr(char* newPtr);

private:
    char* startPtr;
    unsigned length;
    bool status;
};

#endif
