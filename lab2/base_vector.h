#ifndef BASE_VECTOR_H
#define BASE_VECTOR_H


#include <cstddef>


class BaseVector
{
    protected:
        size_t vector_size = 0;

    public:
        BaseVector(size_t size = 0): vector_size(size) {}

        virtual size_t get_size() const noexcept
        {
            return vector_size;
        }

        virtual operator bool() const noexcept
        {
            // If vector is not empty, return True
            return bool(vector_size);
        }

        virtual ~BaseVector() = 0;
};


BaseVector::~BaseVector() {}


#endif // BASE_VECTOR_H
