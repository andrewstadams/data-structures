#ifndef SLL_H
#define SLL_H

#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

template<typename T>
class SLL
{
private:
    struct NodeSLL
    {
        T data;
        shared_ptr<NodeSLL> next;
        NodeSLL(const T &value, shared_ptr<NodeSLL> n = nullptr):
            data(value), next(n)
        {}
    };
    size_t listSize;
    shared_ptr<NodeSLL> listFront;
    shared_ptr<NodeSLL> listBack;

public:
    SLL();
    ~SLL();
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
SLL<T>::SLL()
{
    listSize = 0;
    listFront = nullptr;
    listBack = nullptr;
}

template<typename T>
SLL<T>::~SLL()
{
    clear();
}

template<typename T>
bool SLL<T>::empty() const
{
    return listSize == 0;
}

template<typename T>
size_t SLL<T>::size() const
{
    return listSize;
}

template<typename T>
void SLL<T>::push_front(const T &value)
{
    if (empty())
    {
        listFront = make_shared<NodeSLL>(value);
        listBack = listFront;
    }
    else
    {
        shared_ptr<NodeSLL> temp = make_shared<NodeSLL>(value, listFront);
        listFront = temp;
    }
    ++listSize;
}

template<typename T>
void SLL<T>::push_back(const T &value)
{
    if (empty())
    {
        listFront = make_shared<NodeSLL>(value);
        listBack = listFront;
    }
    else
    {
        shared_ptr<NodeSLL> temp = make_shared<NodeSLL>(value);
        listBack->next = temp;
        listBack = temp;
    }
    ++listSize;
}

template<typename T>
const T &SLL<T>::front() const
{
    if (empty())
    {
        throw range_error("Trying front() from empty list");
    }
    return listFront->data;
}

template<typename T>
const T &SLL<T>::back() const
{
    if (empty())
    {
        throw range_error("Trying back() from empty list");
    }
    return listBack->data;
}

template<typename T>
void SLL<T>::pop_front()
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
    }
    --listSize;
}

template<typename T>
void SLL<T>::pop_back()
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
        shared_ptr<NodeSLL> temp = listFront;
        while (temp->next != listBack)
        {
            temp = temp->next;
        }
        temp->next = nullptr;
        listBack = temp;
    }
    --listSize;
}

template<typename T>
void SLL<T>::insert(size_t position, const T &value)
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
        shared_ptr<NodeSLL> temp = listFront;
        for (size_t i(0); i < position-1; ++i)
        {
            temp = temp->next;
        }
        shared_ptr<NodeSLL> new_node = make_shared<NodeSLL>(value, temp->next);
        temp->next = new_node;
        ++listSize;
    }
}

template<typename T>
void SLL<T>::erase(size_t position)
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
        shared_ptr<NodeSLL> temp = listFront;
        for (size_t i(0); i < position-1; ++i)
        {
            temp = temp->next;
        }
        shared_ptr<NodeSLL> delete_node = temp->next;
        temp->next = delete_node->next;
        delete_node->next = nullptr;
        --listSize;
    }
}

template<typename T>
void SLL<T>::clear()
{
    for (size_t i(0), j(size()); i < j; ++i)
    {
        pop_front();
    }
}

template<typename T>
void SLL<T>::remove(const T &value)
{
    if (empty())
    {
        throw range_error("Trying remove() from empty list");
    }
    T data;
    shared_ptr<NodeSLL> temp = listFront;
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
T &SLL<T>::operator [](size_t position)
{
    if (empty())
    {
        throw range_error("Trying [] from empty list");
    }
    if (position >= size())
    {
        throw range_error("Trying [] in nonvalid position");
    }
    shared_ptr<NodeSLL> temp = listFront;
    for (size_t i(0); i < position; ++i)
    {
        temp = temp->next;
    }
    return temp->data;
}

#endif // SLL_H
