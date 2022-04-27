#ifndef ConstIterator_CONST_H
#define ConstIterator_CONST_H


#include "exceptions.h"
#include <memory>
#include <time.h>


template<typename Type>
class Vector;


// Const iterator class derived from std::iterator

template<typename Type>
class ConstIterator: public std::iterator<std::random_access_iterator_tag, int>
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
        ConstIterator(const ConstIterator<Type> &) noexcept;
        ConstIterator(const Vector<Type> &) noexcept;

        const Type* operator->() const;
        const Type& operator*() const;

        operator bool() const;

        ConstIterator<Type> &operator=(const ConstIterator<Type> &) noexcept;
        ConstIterator<Type> &operator+=(size_t n);
        ConstIterator<Type> &operator-=(size_t n);

        ConstIterator<Type> operator+(size_t n) const;
        ConstIterator<Type> &operator++();
        ConstIterator<Type> operator++(int);
        ConstIterator<Type> operator-(size_t n) const;
        ConstIterator<Type> &operator--();
        ConstIterator<Type> operator--(int);

        bool operator==(const ConstIterator<Type> &second_vector) const;
        bool operator!=(const ConstIterator<Type> &second_vector) const;
        bool operator<(const ConstIterator<Type> &second_vector) const;
        bool operator<=(const ConstIterator<Type> &second_vector) const;
        bool operator>(const ConstIterator<Type> &second_vector) const;
        bool operator>=(const ConstIterator<Type> &second_vector) const;
};


// Constructors

template<typename Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type> &iterator) noexcept
{
    this->ptr = iterator.ptr;
    this->cur_index = iterator.cur_index;
    this->vector_size = iterator.vector_size;
}

template<typename Type>
ConstIterator<Type>::ConstIterator(const Vector<Type> &vector) noexcept {
    this->ptr = vector.values;
    this->cur_index = 0;
    this->vector_size = vector.get_size();
}


// Checks for expiration and validity

template<typename Type>
void ConstIterator<Type>::check_expiration(int line) const
{
    if (this->ptr.expired())
    {
        time_t cur_time = time(NULL);
        throw ExpiredIteratorException(__FILE__, __func__,
                                       line, ctime(&cur_time));
    }
}

template<typename Type>
void ConstIterator<Type>::check_validity(int line) const
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
Type *ConstIterator<Type>::get_pointer() const
{
    std::shared_ptr<Type[]> ptr_copy = this->ptr.lock();

    return ptr_copy.get() + cur_index;
}


// Operator overloading

template<typename Type>
const Type *ConstIterator<Type>::operator->() const
{
    check_expiration(__LINE__);
    check_validity(__LINE__);

    return get_pointer();
}

template<typename Type>
const Type &ConstIterator<Type>::operator*() const
{
    check_expiration(__LINE__);
    check_validity(__LINE__);

    return *get_pointer();
}


template<typename Type>
ConstIterator<Type>::operator bool() const
{
    check_expiration(__LINE__);

    bool res;
    if (cur_index >= vector_size || vector_size == 0)
        res = false;
    else
        res = true;

    return res;
}


template<typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator=(const ConstIterator<Type> &iterator) noexcept
{
    ptr = iterator.ptr;

    return *this;
}

template<typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator+=(size_t n)
{
    check_expiration(__LINE__);

    cur_index += n;

    return *this;
}

template <typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator-=(size_t n)
{
    check_expiration(__LINE__);

    cur_index -= n;

    return *this;
}


template<typename Type>
ConstIterator<Type> ConstIterator<Type>::operator+(size_t n) const
{
    check_expiration(__LINE__);

    ConstIterator<Type> res_ConstIterator(*this);
    res_ConstIterator += n;

    return res_ConstIterator;
}

template <typename Type>
ConstIterator<Type> ConstIterator<Type>::operator-(size_t n) const
{
    check_expiration(__LINE__);

    ConstIterator<Type> res_ConstIterator(*this);
    res_ConstIterator -= n;

    return res_ConstIterator;
}

template<typename Type>
ConstIterator<Type> ConstIterator<Type>::operator++(int)
{
    check_expiration(__LINE__);

    ++(*this);

    return *this;
}

template<typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator++()
{
    check_expiration(__LINE__);

    cur_index++;

    return *this;
}

template<typename Type>
ConstIterator<Type> ConstIterator<Type>::operator--(int)
{
    check_expiration(__LINE__);

    --(*this);

    return *this;
}

template<typename Type>
ConstIterator<Type> &ConstIterator<Type>::operator--()
{
    check_expiration(__LINE__);

    cur_index--;

    return *this;
}


template<typename Type>
bool ConstIterator<Type>::operator==(const ConstIterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index == second_vector.cur_index;
}

template<typename Type>
bool ConstIterator<Type>::operator!=(const ConstIterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index != second_vector.cur_index;
}

template<typename Type>
bool ConstIterator<Type>::operator<(const ConstIterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index < second_vector.cur_index;
}

template<typename Type>
bool ConstIterator<Type>::operator<=(const ConstIterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index <= second_vector.cur_index;
}

template<typename Type>
bool ConstIterator<Type>::operator>(const ConstIterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index > second_vector.cur_index;
}

template<typename Type>
bool ConstIterator<Type>::operator>=(const ConstIterator<Type> &second_vector) const
{
    check_expiration(__LINE__);

    return this->cur_index >= second_vector.cur_index;
}


#endif // ITERATOR_CONST_H
