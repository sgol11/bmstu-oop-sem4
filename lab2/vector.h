#ifndef VECTOR_H
#define VECTOR_H


#include <iostream>
#include <memory>
#include <cmath>

#include "iterator.h"
#include "iterator_const.h"
#include "base_vector.h"


// TO DO
// [x] public -> protected -> private (порядок)
// [x] избыточный интерфейс: добавить методы к арифметическим операторам (sum, sub и т.д.)
// [x] разные типы для работы с двумя векторами (шаблонные методы)
// [x] добавить ConstIterator begin и end (для foreach)


template<typename Type>
class Vector: public BaseVector
{
    public:
        friend class Iterator<Type>;
        friend class ConstIterator<Type>;

        // Constructors

        Vector();
        explicit Vector(size_t size);
        Vector(size_t size, const Type &element);
        Vector(size_t size, const Type *src_array);
        Vector(std::initializer_list<Type> args);

        explicit Vector(const Vector<Type> &src_vector);
        Vector(Vector<Type> &&src_vector) noexcept;

        // Equality operator

        Vector<Type> &operator=(const Vector<Type> &vector);
        Vector<Type> &operator=(Vector<Type> &&vector);
        Vector<Type> &operator=(std::initializer_list<Type> elements);
        template<typename Type2> Vector<Type> &operator=(const Vector<Type2> &vector);
        template<typename Type2> Vector<Type> &operator=(Vector<Type2> &&vector);

        // Getting element by index

        Type &operator[](size_t index);
        const Type &operator[](size_t index) const;
        Type &at(size_t index);
        const Type &at(size_t index) const;

        // Work with a single vector

        Vector<Type> operator-();
        Vector<Type> neg();
        bool is_zero() const noexcept;
        bool is_unit() const noexcept;
        double vector_length() const;
        Vector<Type> get_unit_vector() const;

        // Comparing vectors

        bool operator==(const Vector<Type> &second_vector) const;
        bool operator!=(const Vector<Type> &second_vector) const;
        bool is_equal(const Vector<Type> &second_vector) const;
        bool is_not_equal(const Vector<Type> &second_vector) const;

        // Mutual arrangement of two vectors

        double angle(const Vector<Type> &second_vector) const;
        bool are_collinear(const Vector<Type> &second_vector) const;
        bool are_orthogonal(const Vector<Type> &second_vector) const;

        // Arithmetical operations

        Vector<Type> &operator+=(const Vector<Type> &second_vector);
        Vector<Type> &operator+=(const Type &element);
        Vector<Type> operator+(const Vector<Type> &second_vector) const;
        Vector<Type> operator+(const Type &element) const;
        Vector<Type> &add_to_vec(const Vector<Type> &second_vector);
        Vector<Type> &add_to_vec(const Type &element);
        Vector<Type> sum(const Vector<Type> &second_vector) const;
        Vector<Type> sum(const Type &element) const;
        template<typename Type2> Vector<Type> &operator+=(const Vector<Type2> &second_vector);
        template<typename Type2> Vector<Type> &operator+=(const Type2 &element);
        template<typename Type2> decltype(auto) operator+(const Vector<Type2> &second_vector) const;
        template<typename Type2> decltype(auto) operator+(const Type2 &element) const;
        template<typename Type2> Vector<Type> &add_to_vec(const Vector<Type2> &second_vector);
        template<typename Type2> Vector<Type> &add_to_vec(const Type2 &element);
        template<typename Type2> decltype(auto) sum(const Vector<Type2> &second_vector) const;
        template<typename Type2> decltype(auto) sum(const Type2 &element) const;

        Vector<Type> &operator-=(const Vector<Type> &second_vector);
        Vector<Type> &operator-=(const Type &element);
        Vector<Type> operator-(const Vector<Type> &second_vector) const;
        Vector<Type> operator-(const Type &element) const;
        Vector<Type> &sub_from_vec(const Vector<Type> &second_vector);
        Vector<Type> &sub_from_vec(const Type &element);
        Vector<Type> sub(const Vector<Type> &second_vector) const;
        Vector<Type> sub(const Type &element) const;
        template<typename Type2> Vector<Type> &operator-=(const Vector<Type2> &second_vector);
        template<typename Type2> Vector<Type> &operator-=(const Type2 &element);
        template<typename Type2> decltype(auto) operator-(const Vector<Type2> &second_vector) const;
        template<typename Type2> decltype(auto) operator-(const Type2 &element) const;
        template<typename Type2> Vector<Type> &sub_from_vec(const Vector<Type2> &second_vector);
        template<typename Type2> Vector<Type> &sub_from_vec(const Type2 &element);
        template<typename Type2> decltype(auto) sub(const Vector<Type2> &second_vector) const;
        template<typename Type2> decltype(auto) sub(const Type2 &element) const;

        // element-by-element multiplication
        Vector<Type> &operator*=(const Vector<Type> &second_vector);
        Vector<Type> &operator*=(const Type &element);
        Vector<Type> operator*(const Vector<Type> &second_vector) const;
        Vector<Type> operator*(const Type &element) const;
        Vector<Type> &mul_to_vec(const Vector<Type> &second_vector);
        Vector<Type> &mul_to_vec(const Type &element);
        Vector<Type> mul(const Vector<Type> &second_vector) const;
        Vector<Type> mul(const Type &element) const;
        template<typename Type2> Vector<Type> &operator*=(const Vector<Type2> &second_vector);
        template<typename Type2> Vector<Type> &operator*=(const Type2 &element);
        template<typename Type2> decltype(auto) operator*(const Vector<Type2> &second_vector) const;
        template<typename Type2> decltype(auto) operator*(const Type2 &element) const;
        template<typename Type2> Vector<Type> &mul_to_vec(const Vector<Type2> &second_vector);
        template<typename Type2> Vector<Type> &mul_to_vec(const Type2 &element);
        template<typename Type2> decltype(auto) mul(const Vector<Type2> &second_vector) const;
        template<typename Type2> decltype(auto) mul(const Type2 &element) const;

        Vector<Type> &operator/=(const Vector<Type> &second_vector);
        Vector<Type> &operator/=(const Type &element);
        Vector<Type> operator/(const Vector<Type> &second_vector) const;
        Vector<Type> operator/(const Type &element) const;
        Vector<Type> &div_vec_by(const Vector<Type> &second_vector);
        Vector<Type> &div_vec_by(const Type &element);
        Vector<Type> div(const Vector<Type> &second_vector) const;
        Vector<Type> div(const Type &element) const;
        template<typename Type2> Vector<Type> &operator/=(const Vector<Type2> &second_vector);
        template<typename Type2> Vector<Type> &operator/=(const Type2 &element);
        template<typename Type2> decltype(auto) operator/(const Vector<Type2> &second_vector) const;
        template<typename Type2> decltype(auto) operator/(const Type2 &element) const;
        template<typename Type2> Vector<Type> &div_vec_by(const Vector<Type2> &second_vector);
        template<typename Type2> Vector<Type> &div_vec_by(const Type2 &element);
        template<typename Type2> decltype(auto) div(const Vector<Type2> &second_vector) const;
        template<typename Type2> decltype(auto) div(const Type2 &element) const;

        // Special multiplications of vectors (scalar and vector)

        Type operator&(const Vector<Type> &second_vector) const;
        Type scalar_mul(const Vector<Type> &second_vector) const;

        Vector<Type> operator^(const Vector<Type> &second_vector) const;
        Vector<Type> &operator^=(const Vector<Type> &second_vector);
        Vector<Type> vector_mul(const Vector<Type> &second_vector) const;

        // Iterators

        Iterator<Type> begin() noexcept;
        Iterator<Type> end() noexcept;
        ConstIterator<Type> begin() const noexcept;
        ConstIterator<Type> end() const noexcept;
        ConstIterator<Type> cbegin() const noexcept;
        ConstIterator<Type> cend() const noexcept;

        // Destructor

        virtual ~Vector() = default;

    protected:
        void allocate_memory(size_t size);
        Type values_sum();
        template<typename Type2> void check_sizes_equality(const Vector<Type2> &vector, int line) const;
        void check_sizes_for_vec_mul(const Vector<Type> &vector, int lineError) const;

    private:
        std::shared_ptr<Type[]> values;
};


#include "vector.hpp"


#endif // VECTOR_H
