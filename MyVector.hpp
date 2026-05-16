#include <iostream>
#include <stdexcept>

template <typename T>
class MyVector
{
public:
    MyVector()
        : m_data(nullptr), m_size(0), m_capacity(0)
    {
    }

    MyVector(size_t count, const T& value = T())
        : m_data(nullptr), m_size(0), m_capacity(0)
    {
        reserve(count);
        for (size_t i = 0; i < count; ++i)
        {
            new (m_data + i) T(value);
        }
        m_size = count;
    }

    MyVector(const MyVector& other)
        : m_data(nullptr), m_size(0), m_capacity(0)
    {
        reserve(other.m_size);
        for (size_t i = 0; i < other.m_size; ++i)
        {
            new (m_data + i) T(other.m_data[i]);
        }
        m_size = other.m_size;
    }

    MyVector(MyVector&& other) noexcept
        : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    ~MyVector()
    {
        clear();
        ::operator delete(m_data);
    }

    MyVector& operator=(const MyVector& other)
    {
        if (this != &other)
        {
            clear();
            reserve(other.m_size);
            for (size_t i = 0; i < other.m_size; ++i)
            {
                new (m_data + i) T(other.m_data[i]);
            }
            m_size = other.m_size;
        }
        return *this;
    }

    MyVector& operator=(MyVector&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            ::operator delete(m_data);

            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    T& operator[](size_t index)
    {
        return m_data[index];
    }

    const T& operator[](size_t index) const
    {
        return m_data[index];
    }

    void push_back(const T& value)
    {
        if (m_size == m_capacity)
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        new (m_data + m_size) T(value);
        ++m_size;
    }

    void push_back(T&& value)
    {
        if (m_size == m_capacity)
        {
            reserve(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        new (m_data + m_size) T(std::move(value));
        ++m_size;
    }

    void pop_back()
    {
        if (m_size == 0)
            return;
        m_data[m_size - 1].~T();
        --m_size;
    }

    size_t size() const
    {
        return m_size;
    }

    size_t capacity() const
    {
        return m_capacity;
    }

    bool empty() const
    {
        return m_size == 0;
    }

private:
    void reserve(size_t new_cap)
    {
        if (new_cap <= m_capacity)
            return;

        T* new_data = static_cast<T*>(::operator new(sizeof(T) * new_cap));

        for (size_t i = 0; i < m_size; ++i)
        {
            new (new_data + i) T(std::move(m_data[i]));
            m_data[i].~T();
        }

        ::operator delete(m_data);
        m_data = new_data;
        m_capacity = new_cap;
    }

public:
    void clear()
    {
        for (size_t i = 0; i < m_size; ++i)
        {
            m_data[i].~T();
        }
        m_size = 0;
    }

private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;
};

