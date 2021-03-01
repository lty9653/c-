#include <cstddef>
#ifndef ARRAY_H
#define ARRAY_H

template <typename T> class Array
{
    private:
        T* elements;
        size_t count;
    public:
        explicit Array(size_t arraySize);
        Array(const Array& other);
        Array(Array&& other);
        virtual ~Array();
        T& operator[](size_t index);
        const T& operator[](size_t index) const;

        Array& operator=(const Array& rhs);
        Array& operator=(Array&& rhs);
        size_t size(){return count;}
};

#endif // ARRAY_H
