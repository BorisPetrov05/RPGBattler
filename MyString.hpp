#pragma once
#include <iostream>

class MyString
{
    char* data_;
    std::size_t size_;
    std::size_t capacity_;

    static std::size_t max_size(std::size_t a, std::size_t b) { return a < b ? b : a; }

    void ensure_capacity(std::size_t min_capacity)
    {
        if (min_capacity == 0) min_capacity = 1;
        if (capacity_ >= min_capacity) return;

        std::size_t new_cap = capacity_ ? capacity_ : 1;

        while (new_cap < min_capacity) new_cap *= 2;

        char* buf = new char[new_cap + 1];
        if (data_) 
        {
            std::memcpy(buf, data_, size_);
            delete[] data_;
        }

        data_ = buf;
        capacity_ = new_cap;
        data_[size_] = '\0';
    }

public:
    MyString() : data_(nullptr), size_(0), capacity_(0)
    {
        ensure_capacity(1);
    }

    MyString(const char* s) : data_(nullptr), size_(0), capacity_(0)
    {
        if (!s) 
        { 
            ensure_capacity(1); 
            return; 
        }

        size_ = std::strlen(s);
        ensure_capacity(size_);

        if (size_ != 0)
            std::memcpy(data_, s, size_);

        data_[size_] = '\0';
    }

    MyString(const MyString& other)
        : data_(nullptr), size_(other.size_), capacity_(0)
    {
        ensure_capacity(size_);

        if (size_ != 0)
            std::memcpy(data_, other.data_, size_);

        data_[size_] = '\0';
    }

    MyString(MyString&& other) noexcept 
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~MyString()
    {
        delete[] data_;
    }

    MyString& operator=(const MyString& other)
    {
        if (this == &other) return *this;

        size_ = other.size_;
        ensure_capacity(size_);

        if (size_ != 0)
            std::memcpy(data_, other.data_, size_);

        data_[size_] = '\0';
        return *this;
    }

    MyString& operator=(MyString&& other) noexcept
    {
        if (this == &other) return *this;

        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    std::size_t size() const { return size_; }
    std::size_t length() const { return size_; }
    bool empty() const { return size_ == 0; }
    const char* c_str() const { return data_ ? data_ : ""; }
    const char* data() const { return c_str(); }
    std::size_t capacity() const { return capacity_; }

    char& operator[](std::size_t i)
    {
        if (i >= size_) throw std::out_of_range("MyString::operator[]");
        return data_[i];
    }

    const char& operator[](std::size_t i) const
    {
        if (i >= size_) throw std::out_of_range("MyString::operator[]");
        return data_[i];
    }

    char& at(std::size_t i) { return operator[](i); }
    const char& at(std::size_t i) const { return operator[](i); }

    void clear() { size_ = 0; if (data_) data_[0] = '\0'; }
    void reserve(std::size_t new_cap) { if (new_cap > capacity_) ensure_capacity(new_cap); }

    void shrink_to_fit()
    {
        if (capacity_ == size_) return;

        char* buf = new char[size_ + 1];

        if (data_) 
        {
            std::memcpy(buf, data_, size_);
            delete[] data_;
        }

        data_ = buf;
        capacity_ = size_;
        data_[size_] = '\0';
    }

    MyString& push_back(char ch)
    {
        ensure_capacity(size_ + 1);

        data_[size_++] = ch;
        data_[size_] = '\0';

        return *this;
    }

    void pop_back()
    {
        if (size_ == 0) throw std::out_of_range("pop_back on empty MyString");
        --size_;
        data_[size_] = '\0';
    }

    MyString& append(const char* s)
    {
        if (!s) return *this;

        std::size_t add = std::strlen(s);
        ensure_capacity(size_ + add);
        std::memcpy(data_ + size_, s, add);

        size_ += add;
        data_[size_] = '\0';

        return *this;
    }

    MyString& append(const MyString& other)
    {
        ensure_capacity(size_ + other.size_);

        std::memcpy(data_ + size_, other.data_, other.size_);

        size_ += other.size_;
        data_[size_] = '\0';

        return *this;
    }

    MyString& operator+=(const MyString& other) { return append(other); }
    MyString& operator+=(const char* s) { return append(s); }
    MyString& operator+=(char c) { return push_back(c); }

    MyString substr(std::size_t pos = 0, std::size_t count = static_cast<std::size_t>(-1)) const
    {
        if (pos > size_) throw std::out_of_range("MyString::substr");

        std::size_t rcount = (count == static_cast<std::size_t>(-1)) ? (size_ - pos) : std::min(count, size_ - pos);

        MyString out;
        out.ensure_capacity(rcount);
        out.size_ = rcount;

        std::memcpy(out.data_, data_ + pos, rcount);
        out.data_[out.size_] = '\0';

        return out;
    }

    using ptrdiff = std::ptrdiff_t;

    ptrdiff find(const MyString& str, std::size_t pos = 0) const
    {
        if (str.size_ == 0) return (pos <= size_) ? static_cast<ptrdiff>(pos) : -1;

        if (str.size_ > size_) return -1;

        for (std::size_t i = pos; i + str.size_ <= size_; ++i) 
        {
            if (std::memcmp(data_ + i, str.data_, str.size_) == 0) 
                return static_cast<ptrdiff>(i);
        }

        return -1;
    }

    ptrdiff find(char ch, std::size_t pos = 0) const
    {
        for (std::size_t i = pos; i < size_; ++i) if (data_[i] == ch) return static_cast<ptrdiff>(i);
        return -1;
    }

    MyString& replace(std::size_t pos, std::size_t count, const MyString& repl)
    {
        if (pos > size_) throw std::out_of_range("MyString::replace");

        if (count > size_ - pos) count = size_ - pos;

        std::size_t new_size = size_ - count + repl.size_;

        MyString tmp;
        tmp.ensure_capacity(new_size);
        // prefix
        tmp.size_ = pos;
        std::memcpy(tmp.data_, data_, pos);

        // replacement
        std::memcpy(tmp.data_ + tmp.size_, repl.data_, repl.size_);
        tmp.size_ += repl.size_;

        // suffix
        std::size_t suffix = size_ - pos - count;
        std::memcpy(tmp.data_ + tmp.size_, data_ + pos + count, suffix);
        tmp.size_ += suffix;
        tmp.data_[tmp.size_] = '\0';
        *this = std::move(tmp);

        return *this;
    }

    int compare(const MyString& other) const
    {
        std::size_t n = std::min(size_, other.size_);
        int r = 0;

        if (n > 0) r = std::memcmp(data_, other.data_, n);
        if (r != 0) return r;
        if (size_ == other.size_) return 0;

        return (size_ < other.size_) ? -1 : 1;
    }

    bool operator==(const MyString& other) const
    {
        return (size_ == other.size_) && (size_ == 0 || std::memcmp(data_, other.data_, size_) == 0);
    }

    bool operator!=(const MyString& other) const { return !(*this == other); }
    bool operator<(const MyString& other) const { return compare(other) < 0; }
    bool operator>(const MyString& other) const { return compare(other) > 0; }
    bool operator<=(const MyString& other) const { return compare(other) <= 0; }
    bool operator>=(const MyString& other) const { return compare(other) >= 0; }

    friend MyString operator+(MyString a, const MyString& b)
    {
        a.append(b);
        return a;
    }

    friend MyString operator+(MyString a, const char* b)
    {
        a.append(b);
        return a;
    }

    friend MyString operator+(const char* a, const MyString& b)
    {
        MyString out(a);
        out.append(b);
        return out;
    }

    using iterator = char*;
    using const_iterator = const char*;

    iterator begin() { return data_; }
    iterator end() { return data_ + size_; }
    const_iterator begin() const { return data_; }
    const_iterator end() const { return data_ + size_; }

    friend std::istream& operator>>(std::istream& is, MyString& s)
    {
        s.clear();

        const std::size_t bufferSize = 256;
        char buffer[bufferSize];
        is >> buffer;
        s = MyString(buffer);

        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const MyString& s)
    {
        os << s.c_str();
        return os;
    }
};