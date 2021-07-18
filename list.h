#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T, size_t n>
class List
{
private:
    static const size_t CAPACITY = 100;
    T elements[CAPACITY];
    size_t index;
    size_t containerSize;

public:
    List();
    bool empty() const;
    bool full() const;
    size_t size() const;
    void push_front(const T &value);
    void push_back(const T &value);
    const T &front() const;
    const T &back() const;
    void pop_front();
    void pop_back();
    void insert(size_t position, const T &value);
    void erase(size_t position);
    void clear();
    void remove(const T &value);
    T &operator [](size_t position);
};

template<typename T, size_t n>
List<T,n>::List()
{
    if (n > CAPACITY)
    {
        throw invalid_argument("List size exceeds list capacity");
    }
    index = 0;
    containerSize = n;
}

template<typename T, size_t n>
bool List<T,n>::empty() const
{
    return index == 0;
}

template<typename T, size_t n>
bool List<T,n>::full() const
{
    return index == containerSize;
}

template<typename T, size_t n>
size_t List<T,n>::size() const
{
    return index;
}

template<typename T, size_t n>
void List<T,n>::push_front(const T &value)
{
    if (full())
    {
        throw range_error("Trying push_front() from full list");
    }
    for (size_t i(index); i > 0; --i)
    {
        elements[i] = elements[i-1];
    }
    elements[0] = value;
    ++index;
}

template<typename T, size_t n>
void List<T,n>::push_back(const T &value)
{
    if (full())
    {
        throw range_error("Trying push_back() from full list");
    }
    elements[index++] = value;
}

template<typename T, size_t n>
const T &List<T,n>::front() const
{
    if (empty())
    {
        throw range_error("Trying front() from empty list");
    }
    return elements[0];
}

template<typename T, size_t n>
const T &List<T,n>::back() const
{
    if (empty())
    {
        throw range_error("Trying back() from empty list");
    }
    return elements[index-1];
}

template<typename T, size_t n>
void List<T,n>::pop_front()
{
    if (empty())
    {
        throw range_error("Trying pop_front() from empty list");
    }
    for (size_t i(0); i < index-1; ++i)
    {
        elements[i] = elements[i+1];
    }
    --index;
}

template<typename T, size_t n>
void List<T,n>::pop_back()
{
    if (empty())
    {
        throw range_error("Trying pop_back() from empty list");
    }
    --index;
}

template<typename T, size_t n>
void List<T,n>::insert(size_t position, const T &value)
{
    if (full())
    {
        throw range_error("Trying insert() from full list");
    }
    if (position > size())
    {
        throw range_error("Trying insert() in nonvalid position");
    }
    if (position == size())
    {
        push_back(value);
    }
    else
    {
        for (size_t i(index); i > position; --i)
        {
            elements[i] = elements[i-1];
        }
        elements[position] = value;
        ++index;
    }
}

template<typename T, size_t n>
void List<T,n>::erase(size_t position)
{
    if (empty())
    {
        throw range_error("Trying erase() from empty list");
    }
    if (position >= size())
    {
        throw range_error("Trying erase() in nonvalid position");
    }
    if (position == size()-1)
    {
        pop_back();
    }
    else
    {
        for (size_t i(position); i < index-1; ++i)
        {
            elements[i] = elements[i+1];
        }
        --index;
    }
}

template<typename T, size_t n>
void List<T,n>::clear()
{
    index = 0;
}

template<typename T, size_t n>
void List<T,n>::remove(const T &value)
{
    if (empty())
    {
        throw range_error("Trying remove() from empty list");
    }
    size_t i(0);
    while (i < size())
    {
        if (elements[i] == value)
        {
            erase(i);
            --i;
        }
        ++i;
    }
}

template<typename T, size_t n>
T &List<T,n>::operator [](size_t position)
{
    if (empty())
    {
        throw range_error("Trying [] from empty list");
    }
    if (position >= size())
    {
        throw range_error("Trying [] in nonvalid position");
    }
    return elements[position];
}

#endif // LIST_H
