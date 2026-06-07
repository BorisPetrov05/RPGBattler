#pragma once
#include <iostream>

template <typename T>
class MyVector
{
public:
    MyVector()
        : data_(nullptr), size_(0), capacity_(0)
    {
    }

    MyVector(size_t count, const T& value = T())
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(count);
        for (size_t i = 0; i < count; ++i)
        {
            new (data_ + i) T(value);
        }
        size_ = count;
    }

    MyVector(const MyVector& other)
        : data_(nullptr), size_(0), capacity_(0)
    {
        reserve(other.size_);
        for (size_t i = 0; i < other.size_; ++i)
        {
            new (data_ + i) T(other.data_[i]);
        }
        size_ = other.size_;
    }

    MyVector(MyVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~MyVector()
    {
        clear();
        ::operator delete(data_);
    }

    MyVector& operator=(const MyVector& other)
    {
        if (this != &other)
        {
            clear();
            reserve(other.size_);
            for (size_t i = 0; i < other.size_; ++i)
            {
                new (data_ + i) T(other.data_[i]);
            }
            size_ = other.size_;
        }
        return *this;
    }

    MyVector& operator=(MyVector&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            ::operator delete(data_);

            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    T& operator[](size_t index)
    {
        return data_[index];
    }

    const T& operator[](size_t index) const
    {
        return data_[index];
    }

    void push_back(const T& value)
    {
        if (size_ == capacity_)
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (data_ + size_) T(value);
        ++size_;
    }

    void push_back(T&& value)
    {
        if (size_ == capacity_)
        {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        new (data_ + size_) T(std::move(value));
        ++size_;
    }

    void pop_back()
    {
        if (size_ == 0)
            return;
        data_[size_ - 1].~T();
        --size_;
    }

    size_t size() const
    {
        return size_;
    }

    size_t capacity() const
    {
        return capacity_;
    }

    bool empty() const
    {
        return size_ == 0;
    }

private:
    void reserve(size_t new_cap)
    {
        if (new_cap <= capacity_)
            return;

        T* new_data = static_cast<T*>(::operator new(sizeof(T) * new_cap));

        for (size_t i = 0; i < size_; ++i)
        {
            new (new_data + i) T(std::move(data_[i]));
            data_[i].~T();
        }

        ::operator delete(data_);
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    void clear()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i].~T();
        }
        size_ = 0;
    }

private:
    T* data_;
    size_t size_;
    size_t capacity_;
};

