/*
Team Name: Bryan Chua and Yu Zet
Group: P02
Student ID: S10223076 & S10221991*/

#pragma once
#include <iostream>
#include <algorithm>

template <class T>
class Array
{
private:
    int m_size;
    T* m_data;

public:
    /*
    Constructor for Array Class
    
    Parameters: none
    Returns: nothing
    */
    Array() : m_size(0), m_data(nullptr)
    {
    }

    /*
    Constructor for Array Class
    
    Parameters:
        int size: the size of the array
    Returns: nothing
    */
    Array(int size) : m_size(size)
    {
        m_data = new T[size];
    }

    /*
    Constructor for Array Class
    
    Parameters:
        const Array<T>& other: the array to be copied
    Returns: nothing
    */
    Array(const Array<T>& other)
    {
        m_size = other.m_size;
        m_data = new T[m_size];
        std::copy(other.m_data, other.m_data + m_size, m_data);
    }

    /*
    Assignment operator for the array class
    
    Parameters:
        const Array<T>& other: the array to be copied
    Returns: Array&: the reference to the new array
    */
    Array& operator=(const Array<T>& other)
    {
        if (this != &other)
        {
            delete[] m_data;
            m_size = other.m_size;
            m_data = new T[m_size];
            std::copy(other.m_data, other.m_data + m_size, m_data);
        }
        return *this;
    }

    /*
    Destructor for the Array Class.
    
    Parameters: none
    Returns: nothing
    */
    ~Array()
    {
        delete[] m_data;
    }

    /*
    Resizes the array
    
    Parameters:
        int newSize: the size of the array after resizing
    Returns: nothing
    */
    void resize(int newSize)
    {
        T* temp = new T[newSize];
        int elementsToCopy = std::min(m_size, newSize);
        std::copy(m_data, m_data + elementsToCopy, temp);
        delete[] m_data;
        m_data = temp;
        m_size = newSize;
    }

    /*
    Gets the size of the array
    
    Parameters: none
    Returns: int: the size of the array
    */
    int size() const
    {
        return m_size;
    }

    /*
    Operator to access elements in the array
    
    Parameters:
        int index: the index of the element to be accessed
    Returns: T&: the reference to the element
    */
    T& operator[](int index)
    {
        return m_data[index];
    }

    /*
    Adds an element to the end of the array
    
    Parameters:
        const T& value: the value of the element to be added
    Returns: nothing
    */
    void push_back(const T& value)
    {
        resize(m_size + 1);
        m_data[m_size - 1] = value;
    }

    /*
    Gets a pointer to the first element of the array
    
    Parameters: none
    Returns: T*: the pointer to the first element of the array
    */
    T* begin()
    {
        return m_data;
    }

    /*
    Gets a pointer to the element after the last element of the array
    
    Parameters: none
    Returns: T*: the pointer to the element after the last element of the array
    */
    T* end()
    {
        return m_data + m_size;
    }

    /*
    Erases an element from the array
    
    Parameters:
        int index: the index of the element to be erased
    Returns: nothing
    */
    void erase(int index)
    {
        T* temp = new T[m_size - 1];
        int newSize = 0;
        for (int i = 0; i < m_size; i++) {
            if (i != index) {
                temp[newSize++] = m_data[i];
            }
        }
        delete[] m_data;
        m_data = temp;
        m_size = newSize;
    }

    /*
    Inserts an element into the array
    
    Parameters:
        int index: the index of the element to be inserted
        const T& value: the value of the element to be inserted
    Returns: nothing
    */
    void insert(int index, const T& value)
    {
        T* temp = new T[m_size + 1];
        std::copy(m_data, m_data + index, temp);
        temp[index] = value;
        std::copy(m_data + index, m_data + m_size, temp + index + 1);
        delete[] m_data;
        m_data = temp;
        m_size++;
    }
};