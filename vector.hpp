#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <typename T>
class Vector
{
private:
    T *m_elements;
    int m_size;
    int m_capacity;

public:
    //CLASS CONSTRUCTORS
    Vector()
    {
        m_size = 0;
        m_elements = nullptr;
        m_capacity = 0;
    }
    Vector(const Vector<T> &source)
    {
        m_elements = new T[source.m_size];
        for (int i = 0; i < source.m_size; i++)
        {
            m_elements[i] = source.m_elements[i];
        }
        m_capacity = source.m_capacity;
        m_size = source.m_size;
    }
    Vector(Vector<T> &&source)
    {
        m_elements = std::move(source.m_elements);
        m_capacity = source.m_capacity;
        m_size = source.m_size;

        source.m_elements = nullptr;
        source.m_capacity = 0;
        source.m_size = 0;
    }

    //CLAS DESTRUCTOR
    ~Vector()
    {
        delete[] m_elements;
    }

    //CLASS FUNCTIONS
    int size() const
    {
        return m_size;
    }
    int capacity() const
    {
        return m_capacity;
    }
    bool empty() const
    {
        return (m_size == 0);
    }
    T &at(int index) const
    {
        if (m_size != 0)
        {
            if (index >= m_size || index < 0)
            {
                throw std::invalid_argument("INDEX_OUT_OF_RANGE_ERROR");
            }
        }
        else if (m_size == 0)
        {
            throw std::invalid_argument("EMPTY_VECTOR_HOLDS_NO_ELEMENTS");
        }
        return m_elements[index];
    }
    T &front() const
    {
        if (m_size != 0)
        {
            return m_elements[0];
        }
        throw std::invalid_argument("EMPTY_VECTOR_HOLDS_NO_ELEMENTS");

    }
    T &back() const
    {
        if (m_size != 0)
        {
            return m_elements[m_size - 1];
        }
        throw std::invalid_argument("EMPTY_VECTOR_HOLDS_NO_ELEMENTS");
    }
    const T *data() const
    {
        return m_elements;
    }
    void clear()
    {
        if (m_size != 0)
        {
            delete[] m_elements;
            m_elements = new T[m_size];
            m_size = 0;
            m_capacity = 0;
        }
        else
        {
            return;
        }
    }
    void insert(int index, const T &value)
    {
        if (index >= 0 && index < m_size)
        {
            if (m_size < m_capacity)
            {
                m_size++;
                T *temp_arr = new T[m_size - 1];
                for (int i = 0; i < m_size - 1; i++)
                {
                    temp_arr[i] = m_elements[i];
                }
                delete[] m_elements;
                m_elements = new T[m_capacity];
                for (int i = 0; i < index + 1; i++)
                {
                    if (index != i)
                    {
                        m_elements[i] = temp_arr[i];
                    }
                    else
                    {
                        m_elements[i] = value;
                    }
                }
                for (int i = index + 1; i < m_size; i++)
                {
                    m_elements[i] = temp_arr[i - 1];
                }
                delete[] temp_arr;
            }
            else if (m_size >= m_capacity)
            {
                m_capacity = m_size * 2;
                m_size++;
                T *temp_arr = new T[m_size - 1];
                for (int i = 0; i < m_size - 1; i++)
                {
                    temp_arr[i] = m_elements[i];
                }
                delete[] m_elements;
                m_elements = new T[m_capacity];
                for (int i = 0; i < index + 1; i++)
                {
                    if (index != i)
                    {
                        m_elements[i] = temp_arr[i];
                    }
                    else
                    {
                        m_elements[i] = value;
                    }
                }
                for (int i = index + 1; i < m_size; i++)
                {
                    m_elements[i] = temp_arr[i - 1];
                }
                delete[] temp_arr;
            }
        }
    }
    void push_back(const T &value)
    {
        if (m_size >= m_capacity)
        {
            m_size++;
            m_capacity = m_size * 2;
            T *temp_arr = new T[m_capacity];
            for (int i = 0; i < m_size - 1; i++)
            {
                temp_arr[i] = m_elements[i];
            }
            delete[] m_elements;
            temp_arr[m_size - 1] = value;
            m_elements = temp_arr; 
        }
        else
        {
            m_size++;
            T *temp_arr = new T[m_capacity];
            for (int i = 0; i < m_size - 1; i++)
            {
                temp_arr[i] = m_elements[i];
            }
            delete[] m_elements;
            temp_arr[m_size - 1] = value;
            m_elements = temp_arr;
        }
    }
    void erase(int index)
    {
        if (index >= 0 && index < m_size)
        {
            T *temp_arr = new T[m_size - 1];
            for (int i = 0; i < index; i++)
            {
                temp_arr[i] = m_elements[i];
            }
            for (int i = index + 1; i < m_size; i++)
            {
                temp_arr[i - 1] = m_elements[i];
            }
            delete[] m_elements;
            m_size--;
            m_elements = temp_arr;
        }
    }
    void pop_back()
    {
        if (m_size != 0)
        {
            m_size--;
        }
    }

    //CLASS OPERATORS
    T &operator[](int index) const
    {
        if (m_size != 0)
        {
            if (index >= m_size || index < 0)
            {
                throw std::invalid_argument("INDEX_OUT_OF_RANGE_ERROR");
            }
        }
        else if (m_size == 0)
        {
            throw std::invalid_argument("EMPTY_VECTOR_HOLDS_NO_ELEMENTS");
        }
        return m_elements[index];
    }
    Vector &operator=(Vector<T> &&source)
    {
        if (this == &source)
        {
            return *this;
        }
        delete[] m_elements;
        m_size = std::move(source.m_size);
        m_capacity = std::move(source.m_capacity);
        m_elements = std::move(source.m_elements);

        source.m_elements = nullptr;
        source.m_capacity = 0;
        source.m_size = 0;

        return *this;
    }
    Vector &operator=(const Vector<T> &source)
    {
        if (this == &source)
        {
            return *this;
        }
        m_size = source.m_size;
        m_capacity = source.m_capacity;
        delete[] m_elements;
        m_elements = new T[m_size];
        for (int i = 0; i < m_size; i++)
        {
            m_elements[i] = source.m_elements[i];
        }
        return *this;
    }
};

#endif