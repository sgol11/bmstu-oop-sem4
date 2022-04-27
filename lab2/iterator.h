#ifndef ITERATOR_H
#define ITERATOR_H


#include "exceptions.h"
#include <memory>
#include <time.h>


template<typename Type>
class Vector;


// Iterator class derived from std::iterator

template<typename Type>
class Iterator: public std::iterator<std::random_access_iterator_tag, int>
{
    private:
        std::weak_ptr<Type[]> ptr;

    protected:
        Type *get_pointer() const;

        size_t cur_index = 0;
        size_t vector_size = 0;

        void check_expiration(int line) const;
        void check_validity(int line) const;

    public:
        Iterator(const Vector<Type> &vector) noexcept;
        Iterator(const Iterator<Type> &iterator) noexcept;

        Type *operator->();
        const Type *operator->() const;
        Type &operator*();
        const Type &operator*() const;

        operator bool() const;           // example: if (iter) {...}

        Iterator<Type> &operator=(const Iterator<Type> &iterator) noexcept;

        Iterator<Type> operator+(size_t count) const;
        Iterator<Type> &operator+=(size_t count);
        Iterator<Type> &operator++();    // prefix
        Iterator<Type> operator++(int);  // postfix

        Iterator<Type> operator-(size_t count) const;
        Iterator<Type> &operator-=(size_t count);
        Iterator<Type> &operator--();    // prefix
        Iterator<Type> operator--(int);  // postfix

        bool operator==(const Iterator<Type> &second_vector) const;
        bool operator!=(const Iterator<Type> &second_vector) const;
        bool operator<(const Iterator<Type> &second_vector) const;
        bool operator<=(const Iterator<Type> &second_vector) const;
        bool operator>(const Iterator<Type> &second_vector) const;
        bool operator>=(const Iterator<Type> &second_vector) const;
};


// Constructors

template<typename Type>
Iterator<Type>::Iterator(const Vector<Type> &vector) noexcept
{
    this->ptr = vector.values;
    this->cur_index = 0;
    this->vector_size = vector.get_size();
}

template<typename Type>
Iterator<Type>::Iterator(const Iterator<Type> &iterator) noexcept
{
    this->ptr = iterator.ptr;
    this->cur_index = iterator.cur_index;
    this->vector_size = iterator.vector_size;
}


// Checks for expiration and validity

template<typename Type>
void Iterator<Type>::check_expiration(int line) const
{
    if (this->ptr.expired())
    {
        time_t cur_time = time(NULL);
        throw ExpiredIteratorException(__FILE__, __func__,
                                       line, ctime(&cur_time));
    }
}

template<typename Type>
void Iterator<Type>::check_validity(int line) const
{
    if (this->cur_index >= this->vector_size)
    {
        time_t cur_time = time(NULL);
        throw InvalidIteratorException(__FILE__, __func__,
                                       line, ctime(&cur_time));
    }
}


// Getting current pointer by index

template<typename Type>
Type *Iterator<Type>::get_pointer() const
{
    std::shared_ptr<Type[]> ptr_copy = this->ptr.lock();

    return ptr_copy.get() + cur_index;
}


// Operators overloading

template<typename Type>
Type *Iterator<Type>::operator->()
{
    check_expiration(__LINE__);
    check_validity(__LINE__);

    return get_pointer();
}

template<typename Type>
const Type *Iterator<Type>::operator->() const
{
    check_expiration(__LINE__);
    check_validity(__LINE__);

    return get_pointer();
}

template<typename Type>
Type &Iterator<Type>::operator*()
{
    check_expiration(__LINE__);
    check_validity(__LINE__);

    return *get_pointer();
}

template<typename Type>
const Type &Iterator<Type>::operator*() const
{
    check_expiration(__LINE__);
    check_validity(__LINE__);

    return *get_pointer();
}


template<typename Type>
Iterator<Type>::operator bool() const
{
    check_expiration(__LINE__);

    bool res = true;
    if (cur_index >= vector_size || vector_size == 0)
        res = false;

    return res;
}


template<typename Type>
Iterator<Type> &Iterator<Type>::operator=(const Iterator<Type>& iterator) noexcept
{
    ptr = iterator.ptr;

    return *this;
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator+=(size_t n)
{
    check_expiration(__LINE__);

    cur_index += n;

    return *this;
}

template <typename Type>
Iterator<Type> &Iterator<Type>::operator-=(size_t n)
{
    check_expiration(__LINE__);

    cur_index -= n;

    return *this;
}


template<typename Type>
Iterator<Type> Iterator<Type>::operator+(size_t n) const
{
    check_expiration(__LINE__);

    Iterator<Type> res_iterator(*this);
    res_iterator += n;

    return res_iterator;
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator-(size_t n) const
{
    check_expiration(__LINE__);

    Iterator<Type> res_iterator(*this);
    res_iterator -= n;

    return res_iterator;
}

template<typename Type>
Iterator<Type> Iterator<Type>::operator++(int)
{
    check_expiration(__LINE__);

    ++(*this);

    return *this;
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator++()
{
    check_expiration(__LINE__);

    cur_index++;

    return *this;
}

template<typename Type>
Iterator<Type> Iterator<Type>::operator--(int)
{
    check_expiration(__LINE__);

    --(*this);

    return *this;
}

template<typename Type>
Iterator<Type> &Iterator<Type>::operator--()
{
    check_expiration(__LINE__);

    cur_index--;

    return *this;
}


template<typename Type>
bool Iterator<Type>::operator==(const Iterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index == second_vector.cur_index;
}

template<typename Type>
bool Iterator<Type>::operator!=(const Iterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index != second_vector.cur_index;
}

template<typename Type>
bool Iterator<Type>::operator<(const Iterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index < second_vector.cur_index;
}

template<typename Type>
bool Iterator<Type>::operator<=(const Iterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index <= second_vector.cur_index;
}

template<typename Type>
bool Iterator<Type>::operator>(const Iterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index > second_vector.cur_index;
}

template<typename Type>
bool Iterator<Type>::operator>=(const Iterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index >= second_vector.cur_index;
}


#endif // ITERATOR_H
