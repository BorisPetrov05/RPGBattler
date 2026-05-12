#pragma once

#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <utility>

class MyString 
{
    char* m_data;
    std::size_t m_size;
    std::size_t m_capacity;

    static std::size_t max_size(std::size_t a, std::size_t b) { return a < b ? b : a; }

    void ensure_capacity(std::size_t min_capacity)
    {
        if (m_capacity >= min_capacity) return;
        std::size_t new_cap = m_capacity ? m_capacity : 1;
        while (new_cap < min_capacity) new_cap *= 2;
        char* buf = new char[new_cap + 1];
        if (m_data) {
            std::memcpy(buf, m_data, m_size);
            delete[] m_data;
        }
        m_data = buf;
        m_capacity = new_cap;
        m_data[m_size] = '\0';
    }

public:
    MyString()
        : m_data(nullptr), m_size(0), m_capacity(0)
    {
        ensure_capacity(1);
    }

    MyString(const char* s)
        : m_data(nullptr), m_size(0), m_capacity(0)
    {
        if (!s) { ensure_capacity(1); return; }
        m_size = std::strlen(s);
        ensure_capacity(m_size);
        std::memcpy(m_data, s, m_size);
        m_data[m_size] = '\0';
    }

    MyString(const MyString& other)
        : m_data(nullptr), m_size(other.m_size), m_capacity(0)
    {
        ensure_capacity(m_size);
        std::memcpy(m_data, other.m_data, m_size);
        m_data[m_size] = '\0';
    }

    MyString(MyString&& other) noexcept
        : m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    ~MyString()
    {
        delete[] m_data;
    }

    MyString& operator=(const MyString& other)
    {
        if (this == &other) return *this;
        m_size = other.m_size;
        ensure_capacity(m_size);
        std::memcpy(m_data, other.m_data, m_size);
        m_data[m_size] = '\0';
        return *this;
    }

    MyString& operator=(MyString&& other) noexcept
    {
        if (this == &other) return *this;
        delete[] m_data;
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
        return *this;
    }

    std::size_t size() const { return m_size; }
    std::size_t length() const { return m_size; }
    bool empty() const { return m_size == 0; }
    const char* c_str() const { return m_data ? m_data : ""; }
    const char* data() const { return c_str(); }
    std::size_t capacity() const { return m_capacity; }

    char& operator[](std::size_t i)
    {
        if (i >= m_size) throw std::out_of_range("MyString::operator[]");
        return m_data[i];
    }

    const char& operator[](std::size_t i) const
    {
        if (i >= m_size) throw std::out_of_range("MyString::operator[]");
        return m_data[i];
    }

    char& at(std::size_t i) { return operator[](i); }
    const char& at(std::size_t i) const { return operator[](i); }

    void clear() { m_size = 0; if (m_data) m_data[0] = '\0'; }
    void reserve(std::size_t new_cap) { if (new_cap > m_capacity) ensure_capacity(new_cap); }

    void shrink_to_fit()
    {
        if (m_capacity == m_size) return;
        char* buf = new char[m_size + 1];
        if (m_data) {
            std::memcpy(buf, m_data, m_size);
            delete[] m_data;
        }
        m_data = buf;
        m_capacity = m_size;
        m_data[m_size] = '\0';
    }

    MyString& push_back(char ch)
    {
        ensure_capacity(m_size + 1);
        m_data[m_size++] = ch;
        m_data[m_size] = '\0';
        return *this;
    }

    void pop_back()
    {
        if (m_size == 0) throw std::out_of_range("pop_back on empty MyString");
        --m_size;
        m_data[m_size] = '\0';
    }

    MyString& append(const char* s)
    {
        if (!s) return *this;
        std::size_t add = std::strlen(s);
        ensure_capacity(m_size + add);
        std::memcpy(m_data + m_size, s, add);
        m_size += add;
        m_data[m_size] = '\0';
        return *this;
    }

    MyString& append(const MyString& other)
    {
        ensure_capacity(m_size + other.m_size);
        std::memcpy(m_data + m_size, other.m_data, other.m_size);
        m_size += other.m_size;
        m_data[m_size] = '\0';
        return *this;
    }

    MyString& operator+=(const MyString& other) { return append(other); }
    MyString& operator+=(const char* s) { return append(s); }
    MyString& operator+=(char c) { return push_back(c); }

    MyString substr(std::size_t pos = 0, std::size_t count = static_cast<std::size_t>(-1)) const
    {
        if (pos > m_size) throw std::out_of_range("MyString::substr");
        std::size_t rcount = (count == static_cast<std::size_t>(-1)) ? (m_size - pos) : std::min(count, m_size - pos);
        MyString out;
        out.ensure_capacity(rcount);
        out.m_size = rcount;
        std::memcpy(out.m_data, m_data + pos, rcount);
        out.m_data[out.m_size] = '\0';
        return out;
    }

    using ptrdiff = std::ptrdiff_t;

    ptrdiff find(const MyString& needle, std::size_t pos = 0) const
    {
        if (needle.m_size == 0) return (pos <= m_size) ? static_cast<ptrdiff>(pos) : -1;
        if (needle.m_size > m_size) return -1;
        for (std::size_t i = pos; i + needle.m_size <= m_size; ++i) {
            if (std::memcmp(m_data + i, needle.m_data, needle.m_size) == 0) return static_cast<ptrdiff>(i);
        }
        return -1;
    }

    ptrdiff find(char ch, std::size_t pos = 0) const
    {
        for (std::size_t i = pos; i < m_size; ++i) if (m_data[i] == ch) return static_cast<ptrdiff>(i);
        return -1;
    }

    MyString& replace(std::size_t pos, std::size_t count, const MyString& repl)
    {
        if (pos > m_size) throw std::out_of_range("MyString::replace");
        if (count > m_size - pos) count = m_size - pos;
        std::size_t new_size = m_size - count + repl.m_size;
        MyString tmp;
        tmp.ensure_capacity(new_size);
        // prefix
        tmp.m_size = pos;
        std::memcpy(tmp.m_data, m_data, pos);
        // replacement
        std::memcpy(tmp.m_data + tmp.m_size, repl.m_data, repl.m_size);
        tmp.m_size += repl.m_size;
        // suffix
        std::size_t suffix = m_size - pos - count;
        std::memcpy(tmp.m_data + tmp.m_size, m_data + pos + count, suffix);
        tmp.m_size += suffix;
        tmp.m_data[tmp.m_size] = '\0';
        *this = std::move(tmp);
        return *this;
    }

    int compare(const MyString& other) const
    {
        std::size_t n = std::min(m_size, other.m_size);
        int r = 0;
        if (n > 0) r = std::memcmp(m_data, other.m_data, n);
        if (r != 0) return r;
        if (m_size == other.m_size) return 0;
        return (m_size < other.m_size) ? -1 : 1;
    }

    bool operator==(const MyString& other) const
    {
        return (m_size == other.m_size) && (m_size == 0 || std::memcmp(m_data, other.m_data, m_size) == 0);
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

    iterator begin() { return m_data; }
    iterator end() { return m_data + m_size; }
    const_iterator begin() const { return m_data; }
    const_iterator end() const { return m_data + m_size; }
};