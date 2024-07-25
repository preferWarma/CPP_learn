#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <cstring>

namespace lyf {
    using std::size_t;
    using std::memcpy;
    using std::min, std::max;

    template <typename T>
    class Vector {
        size_t m_size;
        size_t m_capacity;
        T* m_data;
    public:
        Vector() noexcept : m_size(0), m_capacity(0), m_data(nullptr) { }

        explicit Vector(size_t size, T fill_value = T()) : m_size(size), m_capacity(size), m_data(nullptr) {
            if (size == 0) return;
            m_data = new T[size];
            for (size_t i = 0; i < size; ++i) {
                m_data[i] = fill_value;
            }
        }

        Vector(std::initializer_list<T> list) : Vector(list.size()) {
            size_t i = 0;
            for (const T& elem : list) {
                m_data[i++] = elem;
            }
        }

        Vector(const Vector& other) : Vector(other.m_size) {
            if (m_size == 0) return;
            memcpy(m_data, other.m_data, m_size * sizeof(T));
        }

        Vector(Vector&& other) noexcept : m_size(other.m_size), m_capacity(other.m_capacity), m_data(other.m_data) {
            other.m_size = 0;
            other.m_capacity = 0;
            other.m_data = nullptr;
        }

        ~Vector() noexcept {
            if (m_data != nullptr) {
                delete[] m_data;
            }
        }

        Vector& operator=(const Vector& other) {
            if (this == &other) {
                return *this;
            }
            m_size = other.m_size;
            reserve(other.m_capacity);
            if (m_size != 0) {
                m_data = new T[m_size];
                memcpy(m_data, other.m_data, m_size * sizeof(T));
            }
            return *this;
        }

        Vector& operator=(Vector&& other) noexcept {
            if (this == &other) {
                return *this;
            }
            delete[] m_data;
            m_size = other.m_size;
            m_data = other.m_data;
            other.m_size = 0;
            other.m_data = nullptr;
            return *this;
        }

        T& operator[](size_t index) const { return m_data[index]; }

        size_t size() const noexcept { return m_size; }
        size_t capacity() const noexcept { return m_capacity; }

        T& at(size_t index) const {
            if (index >= m_size || index < 0) {
                [[unlikely]] throw std::out_of_range(string("out of range that index = ") + std::to_string(index));
            }
            return m_data[index];
        }

        T& back() const {
            if (m_size == 0) {
                throw std::out_of_range("out of range");
            }
            return m_data[m_size - 1];
        }
        T& front() const {
            if (m_size == 0) {
                throw std::out_of_range("out of range");
            }
            return m_data[0];
        }

        void push_back(const T& value) {
            _back_insert(value);
        }

        void earse(size_t index) {
            if (index >= m_size || index < 0) {
                throw std::out_of_range(string("out of range that index = ") + std::to_string(index));
            }
            for (size_t i = index + 1; i < m_size; ++i) {
                m_data[i - 1] = m_data[i];
            }
            --m_size;
        }

        void clear() noexcept {
            m_size = 0;
        }

        void resize(size_t new_size) {
            if (new_size > m_capacity) {
                reserve(new_size);
            }
            m_size = new_size;
        }

        // 保证容量至少为new_capacity
        void reserve(size_t new_capacity) {
            if (new_capacity <= m_capacity) return;

            cout << "从" << m_capacity << "扩容到" << new_capacity << endl;
            m_capacity = new_capacity;
            T* old_data = m_data;
            T* new_data = new T[m_capacity]{};
            if (old_data != nullptr) {
                memcpy(new_data, old_data, m_size * sizeof(T));
            }
            delete[] old_data;
            m_data = new_data;
        }

        // 释放多余的内存
        void shrink_to_fit() {
            if (m_size == 0) {
                delete[] m_data;
                m_data = nullptr;
                m_capacity = 0;
            }
            else if (m_size < m_capacity) {
                T* old_data = m_data;
                m_capacity = m_size;
                m_data = new T[m_capacity];
                memcpy(m_data, old_data, m_size * sizeof(T));
                delete[] old_data;
            }
        }
    private:
        void _back_insert(const T& value) {
            if (m_size == m_capacity) {
                reserve(m_capacity == 0 ? 1 : m_capacity * 2);
            }
            m_data[m_size++] = value;
        }
    };
}

#endif /* !VECTOR_H_ */
