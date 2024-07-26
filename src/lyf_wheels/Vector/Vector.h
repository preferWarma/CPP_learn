#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <cstring>
#include <iterator>

namespace lyf {
    using std::size_t;
    using std::min, std::max;
    using std::random_access_iterator;
    using std::initializer_list;

    template <typename T, class Allocator = std::allocator<T>>
    class Vector {
    private:
        size_t m_size;
        size_t m_capacity;
        T* m_data;
    public:
        Vector() noexcept : m_size(0), m_capacity(0), m_data(nullptr) { }

        explicit Vector(size_t size, const T& fill_value = T()) : m_size(size), m_capacity(size), m_data(nullptr) {
            if (size == 0) return;
            m_data = Allocator{}.allocate(size);
            for (size_t i = 0; i < size; ++i) {
                std::construct_at(m_data + i, fill_value);
            }
        }

        template <random_access_iterator InputIt>
        explicit Vector(InputIt first, InputIt last) : m_size(last - first), m_capacity(last - first), m_data(nullptr) {
            if (m_size == 0) return;
            m_data = Allocator{}.allocate(m_size);
            size_t i = 0;
            for (auto it = first; it != last; ++it) {
                std::construct_at(m_data + i++, *it);
            }
        }

        Vector(initializer_list<T> list) : Vector(list.begin(), list.end()) { }

        Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity), m_data(nullptr) {
            if (m_size == 0) return;
            m_data = Allocator{}.allocate(m_size);
            for (size_t i = 0; i < m_size; ++i) {
                std::construct_at(m_data + i, other.m_data[i]);
            }
        }

        Vector(Vector&& other) noexcept : m_size(other.m_size), m_capacity(other.m_capacity), m_data(other.m_data) {
            other.m_size = 0;
            other.m_capacity = 0;
            other.m_data = nullptr;
        }

        ~Vector() noexcept {
            if (m_data != nullptr) {
                Allocator{}.deallocate(m_data, m_capacity);
            }
        }

        Vector& operator=(const Vector& other) {
            if (this == &other) {
                return *this;
            }
            m_size = other.m_size;
            reserve(other.m_capacity);
            if (m_size != 0) {
                for (size_t i = 0; i < m_size; ++i) {
                    m_data[i] = other.m_data[i];
                }
            }
            return *this;
        }

        Vector& operator=(Vector&& other) noexcept {
            if (this == &other) {
                return *this;
            }
            if (m_data != nullptr) {
                Allocator{}.deallocate(m_data, m_capacity);
            }
            m_size = other.m_size;
            m_data = other.m_data;
            other.m_size = 0;
            other.m_data = nullptr;
            return *this;
        }

        T& operator[](size_t index) const { return m_data[index]; }

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

        template <random_access_iterator InputIt>
        void assign(InputIt first, InputIt last) {
            size_t new_size = last - first;
            if (new_size > m_capacity) {
                reserve(new_size);
            }
            m_size = new_size;
            size_t i = 0;
            for (InputIt it = first; it != last; ++it) {
                m_data[i++] = *it;
            }
        }

        void assign(initializer_list<T> list) {
            assign(list.begin(), list.end());
        }

        void assign(size_t count, const T& value) {
            if (count > m_capacity) {
                reserve(count);
            }
            m_size = count;
            for (size_t i = 0; i < count; ++i) {
                m_data[i] = value;
            }
        }

        void push_back(const T& value) {
            _back_insert(value);
        }

        void push_back(T&& value) {
            _back_insert(std::move(value));
        }

        template <typename... Args>
        T& emplace_back(Args&&... args) {
            if (m_size == m_capacity) {
                reserve(m_capacity == 0 ? 1 : m_capacity * 2);
            }
            std::construct_at(m_data + m_size++, std::forward<Args>(args)...);
            return m_data[m_size - 1];
        }

        void pop_back() {
            if (m_size == 0) {
                throw std::out_of_range("out of range");
            }
            --m_size;
        }

        template <random_access_iterator InputIt>
        T* earse(InputIt begin, InputIt end) {
            if (begin >= end) return nullptr;
            if (end > this->end() || begin < this->begin()) {
                throw std::out_of_range("out of range");
                return nullptr;
            }
            size_t len = end - begin;
            for (size_t i = 0; i < m_size - len; ++i) {
                *(begin + i) = *(end + i);
            }
            m_size -= len;
            return begin;
        }

        template <random_access_iterator InputIt>
        T* earse(InputIt pos) {
            return earse(pos, pos + 1);
        }

        template <random_access_iterator InputIt>
        T* insert(InputIt pos, const T& value) {
            if (pos < this->begin() || pos > this->end()) {
                throw std::out_of_range("out of range");
            }
            if (m_size == m_capacity) {
                reserve(m_capacity == 0 ? 1 : m_capacity * 2);
            }
            for (auto it = this->end(); it != pos; --it) {
                *it = *(it - 1);
            }
            *pos = value;
            ++m_size;
            return pos;
        }

        void swap(Vector& other) noexcept {
            std::swap(m_size, other.m_size);
            std::swap(m_capacity, other.m_capacity);
            std::swap(m_data, other.m_data);
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

            m_capacity = new_capacity;
            T* old_data = m_data;
            size_t old_capactiy = m_capacity;
            T* new_data = Allocator{}.allocate(m_capacity);
            if (old_data != nullptr) {
                for (size_t i = 0; i < m_size; ++i) {
                    std::construct_at(new_data + i, old_data[i]);
                }
            }
            Allocator{}.deallocate(old_data, old_capactiy);
            m_data = new_data;
        }

        // 释放多余的内存
        void shrink_to_fit() {
            if (m_size == 0) {
                Allocator{}.deallocate(m_data, m_capacity);
                m_data = nullptr;
                m_capacity = 0;
            }
            else if (m_size < m_capacity) {
                T* old_data = m_data;
                size_t old_capacity = m_capacity;
                m_capacity = m_size;
                m_data = Allocator{}.allocate(m_capacity);
                for (size_t i = 0; i < m_size; ++i) {
                    std::construct_at(m_data + i, old_data[i]);
                }
                Allocator{}.deallocate(old_data, old_capacity);
            }
        }

        size_t size() const noexcept { return m_size; }
        size_t capacity() const noexcept { return m_capacity; }
        bool empty() const noexcept { return m_size == 0; }
        T* data() noexcept { return m_data; }

        auto begin() const noexcept { return m_data; }
        auto end() const noexcept { return m_data + m_size; }
        auto const cbegin() const noexcept { return m_data; }
        auto const cend() const noexcept { return m_data + m_size; }
        auto rbegin() const noexcept { return std::make_reverse_iterator(end()); }
        auto rend() const noexcept { return std::make_reverse_iterator(begin()); }
        auto const crbegin() const noexcept { return std::make_reverse_iterator(end()); }
        auto const crend() const noexcept { return std::make_reverse_iterator(begin()); }

    private:
        void _back_insert(const T& value) {
            if (m_size == m_capacity) {
                m_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
                T* old_data = m_data;
                size_t old_capacity = m_size;
                m_data = Allocator{}.allocate(m_capacity);
                std::construct_at(m_data + m_size, value);    // 先构造新元素，再析构旧元素, 避免新元素是旧元素的引用
                if (old_data != nullptr) {
                    for (size_t i = 0; i < m_size; ++i) {
                        std::construct_at(m_data + i, old_data[i]);
                    }
                    Allocator{}.deallocate(old_data, old_capacity);
                }
            }
            else {
                std::construct_at(m_data + m_size, value);
            }
            m_size++;
        }
        void _back_insert(T&& value) {
            if (m_size == m_capacity) {
                m_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
                T* old_data = m_data;
                size_t old_capacity = m_size;
                m_data = Allocator{}.allocate(m_capacity);
                std::construct_at(m_data + m_size, std::move(value)); // 先构造新元素，再析构旧元素, 避免新元素是旧元素的引用
                if (old_data != nullptr) {
                    for (size_t i = 0; i < m_size; ++i) {
                        std::construct_at(m_data + i, old_data[i]);
                    }
                    Allocator{}.deallocate(old_data, old_capacity);
                }
            }
            else {
                std::construct_at(m_data + m_size, std::move(value));
            }
            m_size++;
        }
    };
}

#endif /* !VECTOR_H_ */
