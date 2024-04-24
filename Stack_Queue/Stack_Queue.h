#include <iostream>
#include <stdexcept>
using namespace std;

const int MAX = 100;

template <class T>
class Stack
{
private:
    T arr[MAX];
    int TOP = -1;

public:
    Stack() : TOP(-1) {}
    void push(const T &data)
    {
        if (!this->is_full())
            arr[++TOP] = data;
        else
            throw overflow_error("push(): Stack overflow!");
    }

    void pop()
    {
        if (!this->is_empty())
            TOP--;
        else
            throw underflow_error("pop(): Stack underflow!");
    }

    const T &top() const
    {
        if (!this->is_empty())
            return arr[TOP];
        else
            throw out_of_range("top(): Stack is empty!");
    }

    void display() const
    {
        if (!this->is_empty())
        {
            for (int i = 0; i <= TOP; i++)
                cout << arr[i] << " ";
        }
        else
            throw out_of_range("display(): Stack is empty!");
        cout << endl;
    }

    size_t size() const { return static_cast<size_t>(TOP + 1); }

    bool is_empty() const { return TOP == -1; }

    bool is_full() const { return TOP == MAX - 1; }

    void clear() { TOP = -1; }
};

template <class T>
class Queue
{
private:
    T arr[MAX];
    int FRONT = -1;
    int REAR = -1;
    size_t SIZE = 0;

public:
    Queue() {}

    void enqueue(const T &data)
    {
        if (this->is_full())
            throw overflow_error("enqueue(): Queue overflow!");
        if (this->is_empty())
            FRONT = 0;
        if (REAR == MAX - 1) // Non-circular
            this->shift();
        arr[++REAR] = data;
        SIZE++;
    }

    void dequeue()
    {
        if (this->is_empty())
            throw underflow_error("dequeue(): Queue underflow!");
        FRONT++;
        SIZE--;
    }

    const T &getFront() const
    {
        if (!this->is_empty())
            return arr[FRONT];
        else
            throw out_of_range("getFront(): Queue is empty!");
    }

    const T &getRear() const
    {
        if (!this->is_empty())
            return arr[REAR];
        else
            throw out_of_range("getRear(): Queue is empty!");
    }

    size_t size() const { return SIZE; }

    bool is_empty() const { return !SIZE; }

    bool is_full() const { return SIZE == MAX; }

    void display() const
    {
        if (!this->is_empty())
        {
            cout << "Size: " << this->size() << endl;
            for (int i = FRONT; i <= REAR; i++)
                cout << arr[i] << " ";
        }
        else
            cout << "display(): Queue is empty!";
        cout << endl;
    }

    void clear()
    {
        FRONT = -1;
        REAR = -1;
        SIZE = 0;
    }

    // Pushing when there's empty space could use but REAR == MAX-1, shift those element to the beginning.
    void shift()
    {
        for (int newIdx = 0, oldIdx = FRONT; newIdx < SIZE; newIdx++, oldIdx++)
            arr[newIdx] = arr[oldIdx];
        FRONT = 0;
        REAR = SIZE - 1;
    }
};