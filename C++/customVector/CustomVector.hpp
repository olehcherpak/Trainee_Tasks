#ifndef CUSTOMVECTOR_HPP
#define CUSTOMVECTOR_HPP

class CustomVector
{
public:
    CustomVector(const unsigned n);
    CustomVector();
    CustomVector(const unsigned, const int&);
    ~CustomVector();

    CustomVector& operator=(const CustomVector&);
    unsigned size() const;
    unsigned max_size() const;
    void resize(unsigned n, int val = 0);
    unsigned capacity() const;
    bool empty() const;
    void reserve(unsigned);

    int& operator[] (unsigned);
    const int& operator[] (unsigned) const;
    int& at(unsigned);
    int& front();
    const int& front() const;
    int& back();
    const int& back() const;

    void assign (unsigned, const int&);
    void push_back(const int&);
    void pop_back();
    void insert(unsigned, const int&);
    void insert(unsigned, unsigned, const int&);
    void erase(unsigned);
    void erase(unsigned, unsigned);
    void swap(CustomVector&);
    void clear();

private:
    unsigned curSize;
    unsigned curCapacity;
    int* dataArray;

    void copyHandler(int*, int*);
    void moveHandler(unsigned, unsigned);
    void resizeHandler();
};

class out_of_range {};
#endif
