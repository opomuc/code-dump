#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

template <typename Data_T>
    class Vector
    {
        private:
        size_t size_;
        Data_T* data_;

        Vector();

        public:
        Vector(const Vector&);
        Vector(int user_size);
        ~Vector();
        Vector<Data_T>& operator= (const Vector& that);
        Vector<Data_T>& operator+ (const Vector& that);
        Data_T operator[] (int pos);
    };

template <typename Data_T>
Vector<Data_T>::Vector(int user_size):
    size_ (user_size),
    data_ (new Data_T [user_size])
{
    if (size_ == 0)
    {
        assert(NULL);
    }

    printf("I'm a constructor. I made a vector :)\n");

    //memset(data_, 0, sizeof(Data_T) * user_size);
    //assert(ok);
}

template <typename Data_T>
Vector<Data_T>::Vector(const Vector& that):
    size_ (that.size_),
    data_ (new Data_T[size_])
{
    for (unsigned int i = 0; i < size_; i++)
    {
        data_[i] = that.data_[i];
    }
}

template <typename Data_T>
Vector <Data_T>::~Vector()
{
    delete[] data_;
    data_ = NULL;
    printf("I'm a destructor, I destroyed a vector\n");
}

template <typename Data_T>
Vector<Data_T>& Vector<Data_T>::operator= (const Vector<Data_T>& that)    // разный подход к реализации: 1) удалить весь объект, создать новый 2) проверять различные размеры
{
    if (size_ != that.size_)
    {
        delete[] data_;
        data_ = new Data_T [that.size_];
        size_ = that.size_;
    }

    for (unsigned int i = 0; i < size_; i++)
    {
        data_[i] = that.data_[i];
    }
    return *this;
}

template <typename Data_T>
Vector<Data_T>& Vector<Data_T>::operator+ (const Vector<Data_T>& that)
{
    if (size_ == that.size_)
    {
        for (unsigned int i = 0; i < size_; i++)
        {
            data_[i] += that.data_[i];
        }
        return *this;
    }
    else
    {
        printf("Cannot add vectors. Different dimensions\n");
        return NULL;
    }
    return NULL;
}

template <typename Data_T>
Data_T Vactor<Data_T>::operator[] (int pos)
{
    if (pos < 0 || pos >= size_)
    {
        printf("Can not reach the element by this number\n");
    }
    else
    {
        return data_[pos];
    }
}


int main()
{
    Vector <int> v(10);

    Vector <int> v2(10);

    Vector <int> v1(20);

    v1 = v;

    v2 = v + v1;

    return 0;
}
