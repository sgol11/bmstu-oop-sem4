#include <limits>
#include "vector.h"

#define EPS 1e-5


// Memory allocation method

template<typename Type>
void Vector<Type>::allocate_memory(size_t size)
{
    try
    {
        values.reset(new Type[size], std::default_delete<Type[]>());
    }
    catch (std::bad_alloc &exception)
    {
        time_t cur_time = time(NULL);
        throw MemoryException(__FILE__, __func__,
                              __LINE__, ctime(&cur_time));
    }
}


// Iterators

template<typename Type>
Iterator<Type> Vector<Type>::begin() noexcept
{
    Iterator<Type> iterator(*this);

    return iterator;
}

template<typename Type>
Iterator<Type> Vector<Type>::end() noexcept
{
    Iterator<Type> iterator(*this);

    return iterator + this->vector_size;
}

template<typename Type>
ConstIterator<Type> Vector<Type>::begin() const noexcept
{
    ConstIterator<Type> constIterator(*this);

    return constIterator;
}

template<typename Type>
ConstIterator<Type> Vector<Type>::cend() const noexcept
{
    ConstIterator<Type> constIterator(*this);

    return constIterator + this->vector_size;
}


// Constructors

// Default
template<typename Type>
Vector<Type>::Vector()
{
    this->vector_size = 0;
    this->allocate_memory(vector_size);
}

// Filling the memory of a given size with nulls
template<typename Type>
Vector<Type>::Vector(size_t size)
{
    time_t cur_time = time(NULL);

    if (size <= 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->vector_size = size;
    this->allocate_memory(this->vector_size);

    if (!this->values)
        throw MemoryException(__FILE__, __func__,
                              __LINE__, ctime(&cur_time));

    Iterator<Type> iterator = this->begin();
    for (; iterator; iterator++)
        *iterator = 0;
}

// Filling the memory of a given size with the given element
template<typename Type>
Vector<Type>::Vector(size_t size, const Type &element)
{
    time_t cur_time = time(NULL);

    if (size <= 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->vector_size = size;
    this->allocate_memory(this->vector_size);

    if (!this->values)
        throw MemoryException(__FILE__, __func__,
                              __LINE__, ctime(&cur_time));

    Iterator<Type> iterator = this->begin();
    for (; iterator; iterator++)
        *iterator = element;
}

// Filling the memory of a given size with the given array of values
template<typename Type>
Vector<Type>::Vector(size_t size, const Type *src_array)
{
    time_t cur_time = time(NULL);

    if (size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));
    if (!src_array)
        throw InvalidPointerException(__FILE__, __func__,
                                      __LINE__, ctime(&cur_time));

    this->vector_size = size;
    this->allocate_memory(vector_size);

    if (!this->values)
        throw MemoryException(__FILE__, __func__,
                              __LINE__, ctime(&cur_time));

    Iterator<Type> iterator = this->begin();
    for (size_t i = 0; iterator; iterator++, i++)
        *iterator = src_array[i];
}

// Filling the memory of a given size with the given initializer list
template<typename Type>
Vector<Type>::Vector(std::initializer_list<Type> elements)
{
    time_t cur_time = time(NULL);

    this->vector_size = elements.size();
    this->allocate_memory(this->vector_size);

    if (!this->values)
        throw MemoryException(__FILE__, __func__,
                              __LINE__, ctime(&cur_time));

     Iterator<Type> iterator = this->begin();
     for (auto &element : elements)
     {
         *iterator = element;
         iterator++;
     }
}

// Copy constructor
template<typename Type>
Vector<Type>::Vector(const Vector<Type> &src_vector) : BaseVector(src_vector.vector_size)
{
    *this = src_vector;
}

// Move constructor
template<typename Type>
Vector<Type>::Vector(Vector<Type> &&src_vector) noexcept : BaseVector(src_vector.vector_size)
{
    this->vector_size = src_vector.vector_size;
    this->values = src_vector.values;
    src_vector.values = nullptr;
}


// Equality operator (=)

template<typename Type>
Vector<Type> &Vector<Type>::operator=(const Vector<Type> &src_vector)
{
    time_t cur_time = time(NULL);

    this->vector_size = src_vector.vector_size;
    this->allocate_memory(this->vector_size);

    if (this->values == nullptr)
        throw MemoryException(__FILE__, __func__,
                              __LINE__, ctime(&cur_time));

    Iterator<Type> dst_iterator(*this);
    Iterator<Type> src_iterator(src_vector);

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *src_iterator;

    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator=(Vector<Type> &&src_vector)
{
    time_t cur_time = time(NULL);

    this->vector_size = src_vector.vector_size;
    this->allocate_memory(this->vector_size);

    if (this->values == nullptr)
        throw MemoryException(__FILE__, __func__,
                              __LINE__, ctime(&cur_time));

    this->values = src_vector.values;
    src_vector.values.reset();

    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator=(std::initializer_list<Type> elements)
{
    this->vector_size = elements.size();
    this->allocate_memory(this->vector_size);

    Iterator<Type> iterator = this->begin();

    for (auto &element : elements)
    {
        *iterator = element;
        iterator++;
    }

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator=(const Vector<Type2> &src_vector)
{
    time_t cur_time = time(NULL);

    this->vector_size = src_vector.get_size();
    this->allocate_memory(this->vector_size);

    if (this->values == nullptr)
        throw MemoryException(__FILE__, __func__,
                              __LINE__, ctime(&cur_time));

    Iterator<Type> dst_iterator(*this);
    Iterator<Type2> src_iterator(src_vector);

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *src_iterator;

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator=(Vector<Type2> &&src_vector)
{
    time_t cur_time = time(NULL);

    this->vector_size = src_vector.get_size();
    this->allocate_memory(this->vector_size);

    if (this->values == nullptr)
        throw MemoryException(__FILE__, __func__,
                              __LINE__, ctime(&cur_time));

    Iterator<Type> dst_iterator(*this);
    Iterator<Type2> src_iterator(src_vector);

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *src_iterator;
    src_vector.values.reset();

    return *this;
}


// Indexing operator

template<typename Type>
Type &Vector<Type>::operator[](size_t index)
{
    time_t cur_time = time(NULL);

    if (index >= this->vector_size)
        throw OutOfRangeException(__FILE__, __func__,
                                  __LINE__, ctime(&cur_time));

    Iterator<Type> iterator = this->begin();
    for (size_t i = 0; i < index; i++)
        iterator++;

    return *iterator;
}

template<typename Type>
const Type &Vector<Type>::operator[](size_t index) const
{
    time_t cur_time = time(NULL);

    if (index >= this->vector_size)
        throw OutOfRangeException(__FILE__, __func__,
                                  __LINE__, ctime(&cur_time));

    ConstIterator<Type> iterator = this->begin();
    for (size_t i = 0; i < index; i++)
        iterator++;

    return *iterator;
}

template<typename Type>
Type &Vector<Type>::at(size_t index)
{
    return this->operator[](index);
}

template<typename Type>
const Type &Vector<Type>::at(size_t index) const
{
    return this->operator[](index);
}


// Work with a single vector

template<typename Type>
bool Vector<Type>::is_zero() const noexcept
{
    bool res = true;

    if (this->vector_length() > std::numeric_limits<Type>::epsilon())
        res = false;

    return res;
}

template<typename Type>
bool Vector<Type>::is_unit() const noexcept
{
    bool res = true;

    if (std::fabs(this->vector_length() - 1) > std::numeric_limits<Type>::epsilon())
        res = false;

    return res;
}

template<typename Type>
double Vector<Type>::vector_length() const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    ConstIterator<Type> iterator = this->begin();

    double sum = 0;
    for (; iterator; iterator++)
        sum += *iterator * *iterator;

    return std::sqrt(sum);
}

template<typename Type>
Vector<Type> Vector<Type>::get_unit_vector() const
{
    Vector<Type> res(this->vector_size);
    Type length = this->vector_length();

    Iterator<Type> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = this->begin();

    for (; src_iterator; src_iterator++, dst_iterator++)
        *dst_iterator = *src_iterator / length;

    return res;
}

template<typename Type>
Vector<Type> Vector<Type>::operator-()
{
    Vector<Type> new_vector(*this);
    Iterator<Type> iterator = new_vector.begin();

    for (; iterator; iterator++)
        *iterator = -*iterator;

    return new_vector;
}

template<typename Type>
Vector<Type> Vector<Type>::neg()
{
    return -*this;
}


// Comparing vectors

template<typename Type>
bool Vector<Type>::operator==(const Vector<Type> &second_vector) const
{
    bool res = true;

    if (this->vector_size != second_vector.vector_size)
        res = false;
    else
    {
        ConstIterator<Type> iterator_1 = this->begin();
        ConstIterator<Type> iterator_2 = second_vector.begin();

        for (; iterator_1 && res; iterator_1++, iterator_2++)
            if (std::fabs(*iterator_1 - *iterator_2) > std::numeric_limits<Type>::epsilon())
                res = false;
    }

    return res;
}

template<typename Type>
bool Vector<Type>::operator!=(const Vector<Type> &second_vector) const
{
    return !(*this == second_vector);
}

template<typename Type>
bool Vector<Type>::is_equal(const Vector<Type> &second_vector) const
{
    return *this == second_vector;
}

template<typename Type>
bool Vector<Type>::is_not_equal(const Vector<Type> &second_vector) const
{
    return *this != second_vector;
}


// Mutual arrangement of two vectors

template<typename Type>
double Vector<Type>::angle(const Vector<Type> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->is_zero() || second_vector.is_zero())
        throw ZeroDivisionException(__FILE__, __func__,
                                    __LINE__, ctime(&cur_time));

    double angle = (*this & second_vector) / (this->vector_length() * second_vector.vector_length());

    return std::acos(angle) * 180 / M_PI;
}

template<typename Type>
bool Vector<Type>::are_collinear(const Vector<Type> &second_vector) const
{
    bool result = false;

    if (std::fabs(this->angle(second_vector)) < EPS)
        result = true;

    return result;
}

template<typename Type>
bool Vector<Type>::are_orthogonal(const Vector<Type> &second_vector) const
{
    bool result = false;

    if (std::fabs((this->angle(second_vector) - 90)) < EPS)
        result = true;

    return result;
}


// SUM

template<typename Type>
Vector<Type> Vector<Type>::operator+(const Vector<Type> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    Vector<Type> res(*this);

    Iterator<Type> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = second_vector.begin();

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *dst_iterator + *src_iterator;

    return res;
}

template<typename Type>
Vector<Type> Vector<Type>::operator+(const Type &element) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    Vector<Type> res(*this);

    Iterator<Type> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = this->begin();

    for (; src_iterator; src_iterator++, dst_iterator++)
        *dst_iterator = *src_iterator + element;

    return res;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator+(const Vector<Type2> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    Vector<decltype(this->values[0] + second_vector[0])> res(this->get_size());
    for (size_t i = 0; i < this->get_size(); i++)
        res[i] = this->values[i];

    Iterator<decltype(this->values[0] + second_vector[0])> dst_iterator = res.begin();
    ConstIterator<Type2> src_iterator = second_vector.begin();

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *dst_iterator + *src_iterator;

    return res;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator+(const Type2 &element) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    Vector<decltype(this->values[0] + element)> res(this->get_size());
    for (size_t i = 0; i < this->get_size(); i++)
        res[i] = this->values[i];

    Iterator<decltype(this->values[0] + element)> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = this->begin();

    for (; src_iterator; src_iterator++, dst_iterator++)
        *dst_iterator = *src_iterator + element;

    return res;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator+=(const Vector<Type> &second_vector)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    *this = *this + second_vector;

    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator+=(const Type &element)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    *this = *this + element;

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator+=(const Vector<Type2> &second_vector)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    *this = *this + second_vector;

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator+=(const Type2 &element)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    *this = *this + element;

    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::sum(const Vector<Type> &second_vector) const
{
    return *this + second_vector;
}

template<typename Type>
Vector<Type> Vector<Type>::sum(const Type &element) const
{
    return *this + element;
}

template<typename Type>
Vector<Type> &Vector<Type>::add_to_vec(const Vector<Type> &second_vector)
{
    *this += second_vector;
    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::add_to_vec(const Type &element)
{
    *this += element;
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::add_to_vec(const Vector<Type2> &second_vector)
{
    *this += second_vector;
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::add_to_vec(const Type2 &element)
{
    *this += element;
    return *this;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::sum(const Vector<Type2> &second_vector) const
{
    return *this + second_vector;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::sum(const Type2 &element) const
{
    return *this + element;
}

// SUB

template<typename Type>
Vector<Type> Vector<Type>::operator-(const Vector<Type> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    Vector<Type> res(*this);

    Iterator<Type> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = second_vector.begin();

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *dst_iterator - *src_iterator;

    return res;
}

template<typename Type>
Vector<Type> Vector<Type>::operator-(const Type &element) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    Vector<Type> res(*this);

    Iterator<Type> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = this->begin();

    for (; src_iterator; src_iterator++, dst_iterator++)
        *dst_iterator = *src_iterator - element;

    return res;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator-(const Vector<Type2> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    Vector<decltype(this->values[0] + second_vector[0])> res(this->get_size());
    for (size_t i = 0; i < this->get_size(); i++)
        res[i] = this->values[i];

    Iterator<decltype(this->values[0] + second_vector[0])> dst_iterator = res.begin();
    ConstIterator<Type2> src_iterator = second_vector.begin();

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *dst_iterator - *src_iterator;

    return res;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator-(const Type2 &element) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    Vector<decltype(this->values[0] + element)> res(this->get_size());
    for (size_t i = 0; i < this->get_size(); i++)
        res[i] = this->values[i];

    Iterator<decltype(this->values[0] + element)> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = this->begin();

    for (; src_iterator; src_iterator++, dst_iterator++)
        *dst_iterator = *src_iterator - element;

    return res;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator-=(const Vector<Type> &second_vector)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    *this = *this - second_vector;

    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator-=(const Type &element)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    *this = *this - element;

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator-=(const Vector<Type2> &second_vector)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    *this = *this - second_vector;

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator-=(const Type2 &element)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    *this = *this - element;

    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::sub(const Vector<Type> &second_vector) const
{
    return *this - second_vector;
}

template<typename Type>
Vector<Type> Vector<Type>::sub(const Type &element) const
{
    return *this - element;
}

template<typename Type>
Vector<Type> &Vector<Type>::sub_from_vec(const Vector<Type> &second_vector)
{
    *this -= second_vector;
    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::sub_from_vec(const Type &element)
{
    *this -= element;
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::sub_from_vec(const Vector<Type2> &second_vector)
{
    *this -= second_vector;
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::sub_from_vec(const Type2 &element)
{
    *this -= element;
    return *this;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::sub(const Vector<Type2> &second_vector) const
{
    return *this - second_vector;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::sub(const Type2 &element) const
{
    return *this - element;
}


// MUL (element-by-element)

template<typename Type>
Vector<Type> Vector<Type>::operator*(const Vector<Type> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    Vector<Type> res(*this);

    Iterator<Type> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = second_vector.begin();

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *dst_iterator * *src_iterator;

    return res;
}

template<typename Type>
Vector<Type> Vector<Type>::operator*(const Type &element) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    Vector<Type> res(*this);

    Iterator<Type> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = this->begin();

    for (; src_iterator; src_iterator++, dst_iterator++)
        *dst_iterator = *src_iterator * element;

    return res;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator*(const Vector<Type2> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    Vector<decltype(this->values[0] + second_vector[0])> res(this->get_size());
    for (size_t i = 0; i < this->get_size(); i++)
        res[i] = this->values[i];

    Iterator<decltype(this->values[0] + second_vector[0])> dst_iterator = res.begin();
    ConstIterator<Type2> src_iterator = second_vector.begin();

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *dst_iterator * *src_iterator;

    return res;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator*(const Type2 &element) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    Vector<decltype(this->values[0] + element)> res(this->get_size());
    for (size_t i = 0; i < this->get_size(); i++)
        res[i] = this->values[i];

    Iterator<decltype(this->values[0] + element)> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = this->begin();

    for (; src_iterator; src_iterator++, dst_iterator++)
        *dst_iterator = *src_iterator * element;

    return res;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator*=(const Vector<Type> &second_vector)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    *this = *this * second_vector;

    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator*=(const Type &element)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    *this = *this * element;

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator*=(const Vector<Type2> &second_vector)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    *this = *this * second_vector;

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator*=(const Type2 &element)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    *this = *this * element;

    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::mul(const Vector<Type> &second_vector) const
{
    return *this * second_vector;
}

template<typename Type>
Vector<Type> Vector<Type>::mul(const Type &element) const
{
    return *this * element;
}

template<typename Type>
Vector<Type> &Vector<Type>::mul_to_vec(const Vector<Type> &second_vector)
{
    *this *= second_vector;
    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::mul_to_vec(const Type &element)
{
    *this *= element;
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::mul_to_vec(const Vector<Type2> &second_vector)
{
    *this *= second_vector;
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::mul_to_vec(const Type2 &element)
{
    *this *= element;
    return *this;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::mul(const Vector<Type2> &second_vector) const
{
    return *this * second_vector;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::mul(const Type2 &element) const
{
    return *this * element;
}

// DIV

template<typename Type>
Vector<Type> Vector<Type>::operator/(const Vector<Type> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    Vector<Type> res(*this);

    Iterator<Type> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = second_vector.begin();

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *dst_iterator / *src_iterator;

    return res;
}

template<typename Type>
Vector<Type> Vector<Type>::operator/(const Type &element) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    Vector<Type> res(*this);

    Iterator<Type> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = this->begin();

    for (; src_iterator; src_iterator++, dst_iterator++)
        *dst_iterator = *src_iterator / element;

    return res;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator/(const Vector<Type2> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    Vector<decltype(this->values[0] + second_vector[0])> res(this->get_size());
    for (size_t i = 0; i < this->get_size(); i++)
        res[i] = this->values[i];

    Iterator<decltype(this->values[0] + second_vector[0])> dst_iterator = res.begin();
    ConstIterator<Type2> src_iterator = second_vector.begin();

    for (; dst_iterator; dst_iterator++, src_iterator++)
        *dst_iterator = *dst_iterator / *src_iterator;

    return res;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::operator/(const Type2 &element) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    Vector<decltype(this->values[0] + element)> res(this->get_size());
    for (size_t i = 0; i < this->get_size(); i++)
        res[i] = this->values[i];

    Iterator<decltype(this->values[0] + element)> dst_iterator = res.begin();
    ConstIterator<Type> src_iterator = this->begin();

    for (; src_iterator; src_iterator++, dst_iterator++)
        *dst_iterator = *src_iterator / element;

    return res;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator/=(const Vector<Type> &second_vector)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    *this = *this / second_vector;

    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator/=(const Type &element)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    *this = *this / element;

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator/=(const Vector<Type2> &second_vector)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.get_size() == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    *this = *this / second_vector;

    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::operator/=(const Type2 &element)
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    *this = *this / element;

    return *this;
}

template<typename Type>
Vector<Type> Vector<Type>::div(const Vector<Type> &second_vector) const
{
    return *this / second_vector;
}

template<typename Type>
Vector<Type> Vector<Type>::div(const Type &element) const
{
    return *this / element;
}

template<typename Type>
Vector<Type> &Vector<Type>::div_vec_by(const Vector<Type> &second_vector)
{
    *this /= second_vector;
    return *this;
}

template<typename Type>
Vector<Type> &Vector<Type>::div_vec_by(const Type &element)
{
    *this /= element;
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::div_vec_by(const Vector<Type2> &second_vector)
{
    *this /= second_vector;
    return *this;
}

template<typename Type>
template<typename Type2>
Vector<Type> &Vector<Type>::div_vec_by(const Type2 &element)
{
    *this /= element;
    return *this;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::div(const Vector<Type2> &second_vector) const
{
    return *this / second_vector;
}

template<typename Type>
template<typename Type2>
decltype(auto) Vector<Type>::div(const Type2 &element) const
{
    return *this / element;
}


// Special multiplications of vectors (scalar and vector)

template<typename Type>
Type Vector<Type>::scalar_mul(const Vector<Type> &second_vector) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0 || second_vector.vector_size == 0)
        EmptyVectorException(__FILE__, __func__,
                             __LINE__, ctime(&cur_time));

    this->check_sizes_equality(second_vector, __LINE__);

    Type res = (*this * second_vector).values_sum();

    return res;
}

template<typename Type>
Type Vector<Type>::operator&(const Vector<Type> &second_vector) const
{
    return this->scalar_mul(second_vector);
}

template<typename Type>
Vector<Type> Vector<Type>::vector_mul(const Vector<Type> &second_vector) const
{
    check_sizes_for_vec_mul(second_vector, __LINE__);

    Type x = this->values[1] * second_vector.values[2] - this->values[2] * second_vector.values[1];
    Type y = this->values[2] * second_vector.values[0] - this->values[0] * second_vector.values[2];
    Type z = this->values[0] * second_vector.values[1] - this->values[1] * second_vector.values[0];

    Vector<Type> res = {x, y, z};

    return res;
}

template<typename Type>
Vector<Type> Vector<Type>::operator^(const Vector<Type> &second_vector) const
{
    Vector<Type> result = this->vector_mul(second_vector);

    return result;
}

template<typename Type>
Vector<Type> &Vector<Type>::operator^=(const Vector<Type> &second_vector)
{
    *this = *this ^ second_vector;

    return *this;
}


// Checks

template<typename Type>
Type Vector<Type>::values_sum()
{
    time_t cur_time = time(NULL);

    if (this->vector_size == 0)
        throw EmptyVectorException(__FILE__, __func__,
                                   __LINE__, ctime(&cur_time));

    Iterator<Type> iterator = this->begin();

    Type sum = 0;
    for (; iterator; iterator++)
        sum += *iterator;

    return sum;
}

template<typename Type>
template<typename Type2>
void Vector<Type>::check_sizes_equality(const Vector<Type2> &second_vector, int cur_line) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size != second_vector.get_size())
        throw InvalidSizesException(__FILE__, __func__,
                                    cur_line, ctime(&cur_time));
}

template<typename Type>
void Vector<Type>::check_sizes_for_vec_mul(const Vector<Type> &second_vector, int cur_line) const
{
    time_t cur_time = time(NULL);

    if (this->vector_size != 3 || second_vector.vector_size != 3)
        throw InvalidSizesException(__FILE__, __func__,
                                    cur_line, ctime(&cur_time));
}


// Output of the vector
template<typename Type>
std::ostream &operator<<(std::ostream &os, const Vector<Type> &vector)
{
    ConstIterator<Type> iterator = vector.begin();

    if (!iterator)
    {
        os << "Empty Vector";
        return os;
    }

    os << "{";
    os << *iterator;
    for (iterator++; iterator; iterator++)
            os << ", " << *iterator;
    os << "}";

    return os;
}


// Commutative operations

template<typename Type>
Vector<Type> operator+(const Type &element, const Vector<Type> &vector)
{
    return vector + element;
}

template<typename Type>
Vector<Type> operator*(const Type &element, const Vector<Type> &vector)
{
    return vector * element;
}
