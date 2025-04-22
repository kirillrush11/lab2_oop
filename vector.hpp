#ifndef M_VECTOR_H
#define M_VECTOR_H

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include "vector.hpp"
#include "iterator.hpp"


template <typename T>
class m_vector {
private:
    T* data = nullptr;
    size_t capacity = 0;
    size_t length = 0;

    void check_index(size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
    }

    void check_division(T val) const {
        if (val == 0) {
            throw std::invalid_argument("Division by zero");
        }
    }

    void check_size(size_t other_size) const {
        if (length != other_size) {
            throw std::invalid_argument("Vectors must be of same length");
        }
    }

    void reallocate(size_t new_capacity) {
        T* new_data = new T[new_capacity];

        for (size_t i = 0; i < length; ++i) {
            new_data[i] = std::move(data[i]);
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

    void ensure_capacity(size_t required_size) {
        if (required_size <= capacity) return;

        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        if (new_capacity < required_size) {
            new_capacity = required_size;
        }
        reallocate(new_capacity);
    }

public:
    using Iterator = m_vector_iterator<T>;

    m_vector(size_t length = 0) : capacity(length), length(length) {
        if (length > 0) {
            data = new T[length];
        }
    }

    m_vector(const m_vector<T>& other) : capacity(other.length), length(other.length) {
        if (length > 0) {
            data = new T[length];
            for (size_t i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    m_vector(m_vector<T>&& other) noexcept
        : data(other.data), capacity(other.capacity), length(other.length) {
        other.data = nullptr;
        other.capacity = 0;
        other.length = 0;
    }

    m_vector(std::initializer_list<T> lst) : capacity(lst.size()), length(lst.size()) {
        if (length > 0) {
            data = new T[length];
            size_t i = 0;
            for (const auto& item : lst) {
                data[i++] = item;
            }
        }
    }

    ~m_vector() {
        delete[] data;
    }

    m_vector<T>& operator=(m_vector<T>&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            capacity = other.capacity;

            other.data = nullptr;
            other.length = 0;
            other.capacity = 0;
        }
        return *this;
    }

    void set_elem(size_t index, const T& elem) {
        check_index(index);
        data[index] = elem;
    }

    T& get_elem(size_t index) {
        check_index(index);
        return data[index];
    }

    T& operator[](size_t index) { return get_elem(index); }
    const T& operator[](size_t index) const { return get_elem(index); }

    T* to_array() const {
        T* arr = new T[length];
        for (size_t i = 0; i < length; ++i) {
            arr[i] = data[i];
        }
        return arr;
    }

    size_t get_length() const { return length; }

    bool operator==(const m_vector<T>& other) const {
        if (length != other.length)
            return false;
        for (size_t i = 0; i < length; ++i) {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const m_vector<T>& other) const {
        return !(*this == other);
    }

    m_vector<T>& operator+=(const m_vector<T>& vect) {
        check_size(vect.length);
        for (size_t i = 0; i < length; ++i) {
            data[i] += vect.data[i];
        }
        return *this;
    }

    m_vector<T>& operator-=(const m_vector<T>& vect) {
        check_size(vect.length);
        for (size_t i = 0; i < length; ++i) {
            data[i] -= vect.data[i];
        }
        return *this;
    }

    m_vector<T>& operator*=(const T& val) {
        for (size_t i = 0; i < length; ++i) {
            data[i] *= val;
        }
        return *this;
    }

    m_vector<T>& operator/=(const T& val) {
        check_division(val);
        for (size_t i = 0; i < length; ++i) {
            data[i] /= val;
        }
        return *this;
    }

    friend m_vector<T> operator+(const m_vector<T>& v1, const m_vector<T>& v2) {
        m_vector<T> result(v1);
        result += v2;
        return result;
    }

    friend m_vector<T> operator-(const m_vector<T>& v1, const m_vector<T>& v2) {
        m_vector<T> result(v1);
        result -= v2;
        return result;
    }

    friend m_vector<T> operator*(const m_vector<T>& v1, const T& val) {
        m_vector<T> result(v1);
        result *= val;
        return result;
    }

    friend m_vector<T> operator/(const m_vector<T>& v1, const T& val) {
        m_vector<T> result(v1);
        result /= val;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const m_vector<T>& vec) {
        os << "[";
        for (size_t i = 0; i < vec.length; ++i) {
            if (i != 0) os << ", ";
            os << vec.data[i];
        }
        os << "]";
        return os;
    }

    Iterator iterator_begin() {
        return Iterator(*this, 0);
    }

    Iterator iterator_end() {
        return Iterator(*this, length);
    }

};

#endif // M_VECTOR_H
