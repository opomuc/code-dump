#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#define STK_SIZE 20

using namespace std;

class Stack_t
{
    private:
    int     count_;
    int     size_;
    double* data_;

    private:
    Stack_t();

    public:
    Stack_t(int user_size);
    ~Stack_t();
    bool push(double val);
    bool pop();
    void dump();
    bool ok() const;

    friend void operator+= (Stack_t& a_stack, double num);

};

/*
Stack_t:: Stack_t():
    count_(0),
    size_(STK_SIZE)
{
    memset(data_, 0, sizeof(data_));
    assert(ok());
}
*/

Stack_t:: Stack_t(int user_size):
    count_(0),
    size_(user_size)
{
    data_ = (double*) calloc(size_, sizeof(double));
    assert(ok());
}

Stack_t:: ~Stack_t()
{
    assert(ok());
    free(data_);
}

bool Stack_t:: ok() const
{
    assert(this != NULL);
    assert(data_ != NULL);
    return !(count_ < 0 || count_ > size_);
}

bool Stack_t:: push(double val)
{
    assert(ok());
    data_[count_++] = val;
    assert(ok());
    return true;
}

bool Stack_t:: pop()
{
    assert(ok());
    if (count_ != 0)
    {
        printf("\n\tPopped number: %.2f", data_[--count_]);
    }
    else
    {
        printf("\n\tStack is empty!");
        return false;
    }
    assert(ok());
    return true;
}

void Stack_t:: dump()
{
    assert(ok());
    printf("\n\t# Stack adress: %p", this);
    for(int i = 0; i < size_; i++)
    {
        printf("\n\t# data_[%d]: %.2f", i, data_[i]);
    }
    printf("\n\n");

}

void operator+= (const Stack_t& a_stack, double num)
{
    a_stack.push(num);
}

int main()
{
    int s = 20;
    Stack_t st(s);

    for (int i = 0; i < s; i++)
    {
        st.push(5.5*i);
    }
    st.dump();
    st.pop();
    st.pop();

    return 0;
}
