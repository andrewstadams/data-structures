#ifndef DLL_H
#define DLL_H

#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

template<typename T>
class DLL
{
private:
    struct NodeDLL
    {
        T data;
        shared_ptr<NodeDLL> prev;
        shared_ptr<NodeDLL> next;
        NodeDLL(const T &value, shared_ptr<NodeDLL> p = nullptr, shared_ptr<NodeDLL> n = nullptr):
            data(value), prev(p), next(n)
        {}
    };
    size_t listSize;
    shared_ptr<NodeDLL> listFront;
    shared_ptr<NodeDLL> listBack;

public:
    DLL();
    ~DLL();
    bool empty() const;
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

template<typename T>
DLL<T>::DLL()
{
    listSize = 0;
    listFront = nullptr;
    listBack = nullptr;
}

template<typename T>
DLL<T>::~DLL()
{
    clear();
}

template<typename T>
bool DLL<T>::empty() const
{
    return listSize == 0;
}

template<typename T>
size_t DLL<T>::size() const
{
    return listSize;
}

template<typename T>
void DLL<T>::push_front(const T &value)
{
    if (empty())
    {
        listFront = make_shared<NodeDLL>(value);
        listBack = listFront;
    }
    else
    {
        shared_ptr<NodeDLL> temp = make_shared<NodeDLL>(value, nullptr, listFront);
        listFront->prev = temp;
        listFront = temp;
    }
    ++listSize;
}

template<typename T>
void DLL<T>::push_back(const T &value)
{
    if (empty())
    {
        listFront = make_shared<NodeDLL>(value);
        listBack = listFront;
    }
    else
    {
        shared_ptr<NodeDLL> temp = make_shared<NodeDLL>(value, listBack);
        listBack->next = temp;
        listBack = temp;
    }
    ++listSize;
}

template<typename T>
const T &DLL<T>::front() const
{
    if (empty())
    {
        throw range_error("Trying front() from empty list");
    }
    return listFront->data;
}

template<typename T>
const T &DLL<T>::back() const
{
    if (empty())
    {
        throw range_error("Trying back() from empty list");
    }
    return listBack->data;
}

template<typename T>
void DLL<T>::pop_front()
{
    if (empty())
    {
        throw range_error("Trying pop_front() from empty list");
    }
    if (size() == 1)
    {
        listFront = nullptr;
        listBack = nullptr;
    }
    else
    {
        listFront = listFront->next;
        listFront->prev->next = nullptr;
        listFront->prev = nullptr;
    }
    --listSize;
}

template<typename T>
void DLL<T>::pop_back()
{
    if (empty())
    {
        throw range_error("Trying pop_back() from empty list");
    }
    if (size() == 1)
    {
        listFront = nullptr;
        listBack = nullptr;
    }
    else
    {
        listBack = listBack->prev;
        listBack->next->prev = nullptr;
        listBack->next = nullptr;
    }
    --listSize;
}

template<typename T>
void DLL<T>::insert(size_t position, const T &value)
{
    if (position > size())
    {
        throw range_error("Trying insert() in nonvalid position");
    }
    if (position == 0)
    {
        push_front(value);
    }
    else if (position == size())
    {
        push_back(value);
    }
    else
    {
        shared_ptr<NodeDLL> temp = listFront;
        for (size_t i(0); i < position-1; ++i)
        {
            temp = temp->next;
        }
        shared_ptr<NodeDLL> new_node = make_shared<NodeDLL>(value, temp, temp->next);
        temp->next = new_node;
        new_node->next->prev = new_node;
        ++listSize;
    }
}

template<typename T>
void DLL<T>::erase(size_t position)
{
    if (empty())
    {
        throw range_error("Trying erase() from empty list");
    }
    if (position >= size())
    {
        throw range_error("Trying erase() in nonvalid position");
    }
    if (position == 0)
    {
        pop_front();
    }
    else if (position == size()-1)
    {
        pop_back();
    }
    else
    {
        shared_ptr<NodeDLL> temp = listFront;
        for (size_t i(0); i < position-1; ++i)
        {
            temp = temp->next;
        }
        shared_ptr<NodeDLL> delete_node = temp->next;
        temp->next = delete_node->next;
        delete_node->next->prev = temp;
        delete_node->next = nullptr;
        delete_node->prev = nullptr;
        --listSize;
    }
}

template<typename T>
void DLL<T>::clear()
{
    for (size_t i(0), j(size()); i < j; ++i)
    {
        pop_front();
    }
}

template<typename T>
void DLL<T>::remove(const T &value)
{
    if (empty())
    {
        throw range_error("Trying remove() from empty list");
    }
    T data;
    shared_ptr<NodeDLL> temp = listFront;
    size_t i(0);
    while (temp != nullptr)
    {
        data = temp->data;
        temp = temp->next;
        if (data == value)
        {
            erase(i);
            --i;
        }
        ++i;
    }
}

template<typename T>
T &DLL<T>::operator [](size_t position)
{
    if (empty())
    {
        throw range_error("Trying [] from empty list");
    }
    if (position >= size())
    {
        throw range_error("Trying [] in nonvalid position");
    }
    shared_ptr<NodeDLL> temp = listFront;
    for (size_t i(0); i < position; ++i)
    {
        temp = temp->next;
    }
    return temp->data;
}

#endif // DLL_H
