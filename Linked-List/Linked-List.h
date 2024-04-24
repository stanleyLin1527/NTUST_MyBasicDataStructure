#include <iostream>
#include <stdexcept>
using namespace std;

// testing code
/*
int main()
{
    // testing default & regular constructor, push functions, operator <<
    circular_doubly_LL<int> testA, testB(1);
    for (int i = 1; i <= 10; i++)
        testA.push_back(i);
    for (int i = 2; i <= 10; i++)
        testB.push_front(i);
    cout << testA << endl; // 1 ~ 10
    cout << testB << endl; // 10 ~ 1
    cout << endl;

    // testing copy constructor, reverse, operator =, ==
    circular_doubly_LL<int> testC(testA);
    testB.reverse();
    circular_doubly_LL<int> testD = testB;
    if (testC == testD)
        cout << "same" << endl; // this
    else
        cout << "not same" << endl;
    cout << testC << endl; // 1 ~ 10
    cout << testD << endl; // 1 ~ 10
    cout << endl;

    // testing clear, is_empty, pop functions, merge, erase, search
    testB.clear();
    if (testB.is_empty())
        cout << "empty" << endl;
    else
        cout << "not empty" << endl;
    for (int i = 11; i <= 20; i++)
        testB.push_back(i);
    for (int i = 0; i < 3; i++)
        testC.pop_back();
    for (int i = 0; i < 5; i++)
        testD.pop_front();
    testA.merge(testB);
    cout << testA << endl; // 1 ~ 20
    cout << testB << endl; // 11 ~ 20
    cout << testC << endl; // 1 ~ 7
    cout << testD << endl; // 6 ~ 10
    for (int i = 6; i <= 12; i++)
        testA.erase(i);
    cout << testA << endl; // 1 ~ 5 & 13 ~20
    if (testA.search(8))
        cout << "found" << endl;
    else
        cout << "not found" << endl; // this
    cout << endl;

    // testing size
    cout << "Size of testA: " << testA.size() << endl; // 13
    cout << "Size of testB: " << testB.size() << endl; // 10
    cout << "Size of testC: " << testC.size() << endl; // 7
    cout << "Size of testD: " << testD.size() << endl; // 5
    cout << endl;

    // testing headNode & tailNode
    cout << testA.getFront() << " " << testA.getBack() << endl; // 1 20
    cout << testB.getFront() << " " << testB.getBack() << endl; // 11 20
    cout << testC.getFront() << " " << testC.getBack() << endl; // 1 7
    cout << testD.getFront() << " " << testD.getBack() << endl; // 6 10
    system("pause");
    return 0;
}
*/

template <class T>
struct singlyNode
{
    T data;
    singlyNode<T> *nextNode = nullptr;

    const T &getData() { return data; }
};

template <class T>
struct doublyNode
{
    doublyNode<T> *prevNode = nullptr;
    T data;
    doublyNode<T> *nextNode = nullptr;

    const T &getData() { return data; }
};

template <class T>
class singly_LL
{
private:
    singlyNode<T> *headNode;
    singlyNode<T> *tailNode;

public:
    singly_LL() : headNode(nullptr), tailNode(nullptr) {}

    singly_LL(const T &data)
    {
        try
        {
            headNode = new singlyNode<T>{data, nullptr};
            if (!headNode)
                throw logic_error("Run out of memory!");
            tailNode = headNode;
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // Deep copy
    singly_LL(const singly_LL &copy)
    {
        if (copy.headNode) // If copy is not empty
        {
            try
            {
                headNode = new singlyNode<T>{copy.headNode->data, nullptr}; // Copy head node first
                if (!headNode)
                    throw logic_error("Run out of memory, no node is copied!");
                singlyNode<T> *current = headNode;
                singlyNode<T> *copy_current = copy.headNode->nextNode;
                while (copy_current)
                {
                    current->nextNode = new singlyNode<T>{copy_current->data, nullptr};
                    if (!current->nextNode)
                        throw logic_error("Run out of memory, some nodes are copied!");
                    current = current->nextNode;
                    copy_current = copy_current->nextNode;
                }
                tailNode = current;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            headNode = nullptr;
            tailNode = nullptr;
        }
    }

    // Deep delete
    ~singly_LL() { clear(); }

    bool search(const T &data) const
    {
        singlyNode<T> *current = headNode;
        while (current)
        {
            if (current->data == data)
                return true;
            current = current->nextNode;
        }
        return false;
    }

    void push_front(const T &data)
    {
        try
        {
            singlyNode<T> *newNode = new singlyNode<T>{data, nullptr};
            if (!newNode)
                throw logic_error("Run out of memory!");
            if (!headNode)
            {
                headNode = newNode;
                tailNode = headNode;
            }
            else
            {
                newNode->nextNode = headNode;
                headNode = newNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void push_back(const T &data)
    {
        try
        {
            singlyNode<T> *newNode = new singlyNode<T>{data, nullptr};
            if (!newNode)
                throw logic_error("Run out of memory!");
            if (!headNode)
            {
                headNode = newNode;
                tailNode = headNode;
            }
            else
            {
                tailNode->nextNode = newNode;
                tailNode = newNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void pop_front()
    {
        try
        {
            if (!headNode)
                throw out_of_range("Linked-list is empty!");
            else if (!headNode->nextNode)
            {
                delete headNode;
                headNode = nullptr;
                tailNode = nullptr;
            }
            else
            {
                singlyNode<T> *deleteNode = headNode;
                headNode = headNode->nextNode;
                delete deleteNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void pop_back()
    {
        try
        {
            if (!headNode)
                throw out_of_range("Linked-list is empty!");
            else if (!headNode->nextNode)
            {
                delete headNode;
                headNode = nullptr;
                tailNode = nullptr;
            }
            else
            {
                singlyNode<T> *secondLastNode = headNode;
                while (secondLastNode->nextNode != tailNode)
                    secondLastNode = secondLastNode->nextNode;
                delete tailNode;
                tailNode = secondLastNode;
                tailNode->nextNode = nullptr;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // FIXME:
    const T &getFront() const
    {
        try
        {
            if (headNode)
                return headNode->data;
            else
                throw out_of_range("Linked-list is empty!");
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // FIXME:
    const T &getBack() const
    {
        try
        {
            if (tailNode)
                return tailNode->data;
            else
                throw out_of_range("Linked-list is empty!");
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void erase(const T &data)
    {
        if (!headNode)
        {
            cout << data << " is not in the list" << endl;
            return;
        }
        else if (headNode->data == data)
        {
            this->pop_front();
            return;
        }
        else if (tailNode->data == data)
        {
            this->pop_back();
            return;
        }
        else
        {
            singlyNode<T> *current = headNode->nextNode;
            while (current)
            {
                if (current->data == data)
                {
                    singlyNode<T> *preNode = headNode;
                    while (preNode->nextNode != current)
                        preNode = preNode->nextNode;
                    preNode->nextNode = current->nextNode;
                    delete current;
                    return;
                }
                else
                    current = current->nextNode;
            }
            cout << data << " is not in this linked-list." << endl;
        }
    }

    void clear()
    {
        while (headNode)
            pop_front();
    }

    size_t size() const
    {
        size_t res = 0;
        singlyNode<T> *current = headNode;
        while (current)
        {
            ++res;
            current = current->nextNode;
        }
        return res;
    }

    bool is_empty() const { return headNode == nullptr; }

    void merge(const singly_LL &rhs)
    {
        if (this != &rhs)
        {
            if (!rhs.headNode)
                return;
            try
            {
                if (!this->headNode) // empty + not empty
                {
                    headNode = new singlyNode<T>{rhs.headNode->data, nullptr}; // Copy head node first
                    if (!headNode)
                        throw logic_error("Run out of memory, no node is merged!");
                    singlyNode<T> *current = headNode;
                    singlyNode<T> *rhs_current = rhs.headNode->nextNode;
                    while (rhs_current)
                    {
                        current->nextNode = new singlyNode<T>{rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory, some nodes are merged!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    }
                    tailNode = current;
                }
                else // not empty + not empty
                {
                    singlyNode<T> *current = tailNode;
                    singlyNode<T> *rhs_current = rhs.headNode;
                    while (rhs_current)
                    {
                        current->nextNode = new singlyNode<T>{rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    }
                    tailNode = current;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
    }

    void reverse()
    {
        if (!headNode || !headNode->nextNode)
            return;
        singlyNode<T> *prev = nullptr;
        singlyNode<T> *current = headNode;
        singlyNode<T> *nextNode = nullptr;
        while (current)
        {
            nextNode = current->nextNode;
            current->nextNode = prev;
            prev = current;
            current = nextNode;
        }
        tailNode = headNode;
        headNode = prev;
        tailNode->nextNode = nullptr;
    }

    bool operator==(const singly_LL &rhs) const
    {
        if (this != &rhs)
        {
            if (this->size() != rhs.size())
                return false;
            singlyNode<T> *lhs_current = this->headNode, *rhs_current = rhs.headNode;
            while (lhs_current)
            {
                if (lhs_current->data != rhs_current->data)
                    return false;
                lhs_current = lhs_current->nextNode;
                rhs_current = rhs_current->nextNode;
            }
        }
        return true;
    }

    // Deep copy
    singly_LL &operator=(const singly_LL &rhs)
    {
        if (this != &rhs)
        {
            try
            {
                this->clear();
                if (rhs.headNode) // If copy is not empty
                {
                    headNode = new singlyNode<T>{rhs.headNode->data, nullptr}; // Copy head node first
                    if (!headNode)
                        throw logic_error("Run out of memory, no node is copied!");
                    singlyNode<T> *current = headNode;
                    singlyNode<T> *rhs_current = rhs.headNode->nextNode;
                    while (rhs_current)
                    {
                        current->nextNode = new singlyNode<T>{rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory, some nodes are copied!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    }
                    tailNode = current;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            headNode = nullptr;
            tailNode = nullptr;
        }
        return *this;
    }

    template <class U>
    friend ostream &operator<<(ostream &output, const singly_LL<U> &list)
    {
        if (!list.headNode)
            output << "Linked-list is empty!";
        else
        {
            singlyNode<U> *current = list.headNode;
            while (current)
            {
                output << current->getData();
                current = current->nextNode;
                if (current)
                    output << " ";
            }
        }
        return output;
    }
};

template <class T>
class circular_singly_LL
{
private:
    singlyNode<T> *headNode;
    singlyNode<T> *tailNode;

    void init_empty_LL(const T &data)
    {
        headNode = new singlyNode<T>{data, nullptr};
        if (!headNode)
            throw logic_error("Run out of memory, no node is created!");
        headNode->nextNode = headNode;
        tailNode = headNode;
    }

public:
    circular_singly_LL() : headNode(nullptr), tailNode(nullptr) {}

    circular_singly_LL(const T &data)
    {
        try
        {
            init_empty_LL(data);
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // Deep copy
    circular_singly_LL(const circular_singly_LL &copy)
    {
        if (copy.headNode)
        {
            try
            {
                init_empty_LL(copy.headNode->data);
                singlyNode<T> *current = headNode;
                singlyNode<T> *copy_current = copy.headNode->nextNode;
                while (copy_current != copy.headNode)
                {
                    current->nextNode = new singlyNode<T>{copy_current->data, nullptr};
                    if (!current->nextNode)
                        throw logic_error("Run out of memory, some nodes are copied!");
                    if (copy_current == copy.tailNode)
                    {
                        tailNode = current->nextNode;
                        tailNode->nextNode = headNode;
                    }
                    current = current->nextNode;
                    copy_current = copy_current->nextNode;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            headNode = nullptr;
            tailNode = nullptr;
        }
    }

    // Deep delete
    ~circular_singly_LL() { clear(); }

    bool search(const T &data) const
    {
        if (!headNode) // empty list
            return false;
        singlyNode<T> *current = headNode;
        do
        {
            if (current->data == data)
                return true;
            current = current->nextNode;
        } while (current != headNode);
        return false;
    }

    void push_front(const T &data)
    {
        try
        {
            if (!headNode) // empty list
                init_empty_LL(data);
            else
            {
                singlyNode<T> *newNode = new singlyNode<T>{data, nullptr};
                if (!newNode)
                    throw logic_error("Run out of memory!");
                newNode->nextNode = headNode;
                headNode = newNode;
                tailNode->nextNode = headNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void push_back(const T &data)
    {
        try
        {
            if (!headNode) // empty list
                init_empty_LL(data);
            else
            {
                singlyNode<T> *newNode = new singlyNode<T>{data, nullptr};
                if (!newNode)
                    throw logic_error("Run out of memory!");
                tailNode->nextNode = newNode;
                newNode->nextNode = headNode;
                tailNode = newNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void pop_front()
    {
        try
        {
            if (!headNode)
                throw out_of_range("Linked-list is empty!");
            else if (headNode == tailNode)
            {
                delete headNode;
                headNode = nullptr;
                tailNode = nullptr;
            }
            else
            {
                singlyNode<T> *deleteNode = headNode;
                headNode = headNode->nextNode;
                tailNode->nextNode = headNode;
                delete deleteNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void pop_back()
    {
        try
        {
            if (!headNode)
                throw out_of_range("Linked-list is empty!");
            else if (headNode == tailNode)
            {
                delete headNode;
                headNode = nullptr;
                tailNode = nullptr;
            }
            else
            {
                singlyNode<T> *secondLastNode = headNode;
                singlyNode<T> *deleteNode = headNode->nextNode;
                while (deleteNode->nextNode != headNode)
                {
                    secondLastNode = secondLastNode->nextNode;
                    deleteNode = deleteNode->nextNode;
                }
                delete deleteNode;
                secondLastNode->nextNode = headNode;
                tailNode = secondLastNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // FIXME:
    const T &getFront() const
    {
        try
        {
            if (headNode)
                return headNode->data;
            else
                throw out_of_range("Linked-list is empty!");
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // FIXME:
    const T &getBack() const
    {
        try
        {
            if (tailNode)
                return tailNode->data;
            else
                throw out_of_range("Linked-list is empty!");
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void erase(const T &data)
    {
        if (!headNode)
        {
            cout << data << " is not in the list" << endl;
            return;
        }
        else if (headNode->data == data)
        {
            pop_front();
            return;
        }
        else if (tailNode->data == data)
        {
            pop_back();
            return;
        }
        else
        {
            singlyNode<T> *preNode = headNode;
            singlyNode<T> *current = headNode->nextNode;
            do
            {
                if (current->data == data)
                {
                    preNode->nextNode = current->nextNode;
                    delete current;
                    return;
                }
                preNode = preNode->nextNode;
                current = current->nextNode;
            } while (current != headNode);
            cout << data << " is not in the list." << endl;
        }
    }

    void clear()
    {
        while (headNode)
            pop_front();
    }

    size_t size() const
    {
        size_t res = 0;
        singlyNode<T> *current = headNode;
        do
        {
            ++res;
            current = current->nextNode;
        } while (current != headNode);
        return res;
    }

    bool is_empty() const { return headNode == nullptr; }

    void merge(const circular_singly_LL &rhs)
    {
        if (this != &rhs)
        {
            if (!rhs.headNode)
                return;
            try
            {
                if (!headNode) // empty + not empty
                {
                    init_empty_LL(rhs.headNode->data);
                    singlyNode<T> *current = headNode;
                    singlyNode<T> *rhs_current = rhs.headNode->nextNode;
                    while (rhs_current != rhs.headNode)
                    {
                        current->nextNode = new singlyNode<T>{rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory, some node is merged!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    }
                    tailNode = current;
                    tailNode->nextNode = headNode;
                }
                else // not empty + not empty
                {
                    singlyNode<T> *current = tailNode;
                    singlyNode<T> *rhs_current = rhs.headNode;
                    do
                    {
                        current->nextNode = new singlyNode<T>{rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    } while (rhs_current != rhs.headNode);
                    tailNode = current;
                    tailNode->nextNode = headNode;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
    }

    void reverse()
    {
        if (!headNode || headNode == tailNode)
            return;
        singlyNode<T> *prevNode = nullptr;
        singlyNode<T> *current = headNode;
        singlyNode<T> *postNode = nullptr;
        do
        {
            postNode = current->nextNode;
            current->nextNode = prevNode;
            prevNode = current;
            current = postNode;
        } while (postNode != headNode);
        tailNode = headNode;
        headNode = prevNode;
        tailNode->nextNode = headNode;
    }

    bool operator==(const circular_singly_LL &rhs) const
    {
        if (this != &rhs)
        {
            if (this->size() != rhs.size())
                return false;
            singlyNode<T> *current = headNode;
            singlyNode<T> *rhs_current = rhs.headNode;
            do
            {
                if (current->data != rhs_current->data)
                    return false;
                current = current->nextNode;
                rhs_current = rhs_current->nextNode;
            } while (current != headNode);
        }
        return true;
    }

    // Deep copy
    circular_singly_LL &operator=(const circular_singly_LL &rhs)
    {
        if (this != &rhs)
        {
            clear();
            if (rhs.headNode)
            {
                try
                {
                    init_empty_LL(rhs.headNode->data);
                    singlyNode<T> *current = headNode;
                    singlyNode<T> *rhs_current = rhs.headNode->nextNode;
                    do
                    {
                        current->nextNode = new singlyNode<T>{rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory, some nodes are copied!");
                        current = current->nextNode;
                        if (rhs_current == rhs.tailNode)
                        {
                            tailNode = current;
                            tailNode->nextNode = headNode;
                        }
                        rhs_current = rhs_current->nextNode;
                    } while (rhs_current != rhs.headNode);
                }
                catch (const exception &e)
                {
                    cout << e.what() << endl;
                }
            }
        }
        else
            return *this;
    }

    template <class U>
    friend ostream &operator<<(ostream &output, const circular_singly_LL<U> &list)
    {
        if (!list.headNode)
            output << "Linked-list is empty!";
        else
        {
            singlyNode<U> *current = list.headNode;
            do
            {
                output << current->getData();
                current = current->nextNode;
                if (current != list.headNode)
                    output << " ";
            } while (current != list.headNode);
            return output;
        }
    }
};

template <class T>
class doubly_LL
{
private:
    doublyNode<T> *headNode;
    doublyNode<T> *tailNode;

public:
    doubly_LL() : headNode(nullptr), tailNode(nullptr) {}

    doubly_LL(const T &data)
    {
        try
        {
            headNode = new doublyNode<T>{nullptr, data, nullptr};
            if (!headNode)
                throw logic_error("Run out of memory!");
            tailNode = headNode;
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // deep copy
    doubly_LL(const doubly_LL &copy)
    {
        if (copy.headNode)
        {
            try
            {
                headNode = new doublyNode<T>{nullptr, copy.headNode->data, nullptr};
                if (!headNode)
                    throw logic_error("Run out of memory, no node is copied!");
                doublyNode<T> *current = headNode;
                doublyNode<T> *copy_current = copy.headNode->nextNode;
                while (copy_current)
                {
                    current->nextNode = new doublyNode<T>{current, copy_current->data, nullptr};
                    if (!current->nextNode)
                        throw logic_error("Run out of memory, some nodes are copied!");
                    current = current->nextNode;
                    copy_current = copy_current->nextNode;
                }
                tailNode = current;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        else
        {
            headNode = nullptr;
            tailNode = nullptr;
        }
    }

    ~doubly_LL() { clear(); }

    bool search(const T &data) const
    {
        doublyNode<T> *current = headNode;
        while (current)
        {
            if (current->data == data)
                return true;
            current = current->nextNode;
        }
        return false;
    }

    void push_front(const T &data)
    {
        try
        {
            doublyNode<T> *newNode = new doublyNode<T>{nullptr, data, nullptr};
            if (!newNode)
                throw logic_error("Run out of memory!");
            if (!headNode)
                headNode = tailNode = newNode;
            else
            {
                headNode->prevNode = newNode;
                newNode->nextNode = headNode;
                headNode = newNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void push_back(const T &data)
    {
        try
        {
            doublyNode<T> *newNode = new doublyNode<T>{nullptr, data, nullptr};
            if (!newNode)
                throw logic_error("Run out of memory!");
            if (!headNode)
                headNode = tailNode = newNode;
            else
            {
                tailNode->nextNode = newNode;
                newNode->prevNode = tailNode;
                tailNode = newNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void pop_front()
    {
        try
        {
            if (!headNode)
                throw out_of_range("Linked-list is empty!");
            else if (!headNode->nextNode)
            {
                delete headNode;
                headNode = nullptr;
                tailNode = nullptr;
            }
            else
            {
                doublyNode<T> *deleteNode = headNode;
                headNode = headNode->nextNode;
                headNode->prevNode = nullptr;
                delete deleteNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void pop_back()
    {
        try
        {
            if (!headNode)
                throw out_of_range("Linked-list is empty!");
            else if (!headNode->nextNode)
            {
                delete headNode;
                headNode = nullptr;
                tailNode = nullptr;
            }
            else
            {
                doublyNode<T> *deleteNode = tailNode;
                tailNode = tailNode->prevNode;
                tailNode->nextNode = nullptr;
                delete deleteNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // FIXME:
    const T &getFront() const
    {
        try
        {
            if (headNode)
                return headNode->data;
            else
                throw out_of_range("Linked-list is empty!");
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // FIXME:
    const T &getBack() const
    {
        try
        {
            if (tailNode)
                return tailNode->data;
            else
                throw out_of_range("Linked-list is empty!");
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void erase(const T &data)
    {
        if (!headNode)
        {
            cout << data << " is not in the list" << endl;
            return;
        }
        if (headNode->data == data)
        {
            pop_front();
            return;
        }
        else if (tailNode->data == data)
        {
            pop_back();
            return;
        }
        else
        {
            doublyNode<T> *current = headNode;
            while (current)
            {
                if (current->data == data)
                {
                    current->prevNode->nextNode = current->nextNode;
                    current->nextNode->prevNode = current->prevNode;
                    delete current;
                    return;
                }
                current = current->nextNode;
            }
            cout << data << " is not in the list!" << endl;
        }
    }

    void clear()
    {
        while (headNode)
            pop_front();
    }

    size_t size() const
    {
        size_t res = 0;
        doublyNode<T> *current = headNode;
        while (current)
        {
            ++res;
            current = current->nextNode;
        }
        return res;
    }

    bool is_empty() const { return headNode == nullptr; }

    void merge(const doubly_LL &rhs)
    {
        if (this != &rhs)
        {
            if (!rhs.headNode)
                return;
            try
            {
                if (!headNode) // empty + not empty
                {
                    headNode = new doublyNode<T>{nullptr, rhs.headNode->data, nullptr};
                    if (!headNode)
                        throw logic_error("Run out of memory, no node is merged!");
                    doublyNode<T> *current = headNode;
                    doublyNode<T> *rhs_current = rhs.headNode->nextNode;
                    while (rhs_current)
                    {
                        current->nextNode = new doublyNode<T>{current, rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory, some nodes are merged!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    }
                    tailNode = current;
                }
                else // not empty + not empty
                {
                    doublyNode<T> *current = tailNode;
                    doublyNode<T> *rhs_current = rhs.headNode;
                    while (rhs_current)
                    {
                        current->nextNode = new doublyNode<T>{current, rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    }
                    tailNode = current;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
    }

    void reverse()
    {
        if (!headNode || !headNode->nextNode)
            return;
        doublyNode<T> *prev_curr = nullptr;
        doublyNode<T> *current = headNode;
        doublyNode<T> *next_curr = nullptr;
        while (current)
        {
            next_curr = current->nextNode;
            current->nextNode = prev_curr;
            current->prevNode = next_curr;
            prev_curr = current;
            current = next_curr;
        }
        tailNode = headNode;
        headNode = prev_curr;
    }

    bool operator==(const doubly_LL &rhs) const
    {
        if (this->size() != rhs.size())
            return false;
        doublyNode<T> *current = headNode;
        doublyNode<T> *rhs_current = rhs.headNode;
        while (current)
        {
            if (current->data != rhs_current->data)
                return false;
            current = current->nextNode;
            rhs_current = rhs_current->nextNode;
        }
        return true;
    }

    doubly_LL &operator=(const doubly_LL &rhs)
    {
        if (this != &rhs)
        {
            clear();
            if (rhs.headNode)
            {
                try
                {
                    headNode = new doublyNode<T>{nullptr, rhs.headNode->data, nullptr};
                    if (!headNode)
                        throw logic_error("Run out of memory, no node is copied!");
                    doublyNode<T> *current = headNode;
                    doublyNode<T> *rhs_current = rhs.headNode->nextNode;
                    while (rhs_current)
                    {
                        current->nextNode = new doublyNode<T>{current, rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory, some nodes are copied!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    }
                    tailNode = current;
                }
                catch (const exception &e)
                {
                    cout << e.what() << endl;
                }
            }
            else
            {
                headNode = nullptr;
                tailNode = nullptr;
            }
        }
        return *this;
    }

    template <class U>
    friend ostream &operator<<(ostream &output, const doubly_LL<U> &list)
    {
        if (!list.headNode)
            output << " Linked-list is empty!";
        else
        {
            doublyNode<U> *current = list.headNode;
            while (current)
            {
                output << current->getData();
                current = current->nextNode;
                if (current)
                    output << " ";
            }
        }
        return output;
    }
};

template <class T>
class circular_doubly_LL
{
private:
    doublyNode<T> *headNode;
    doublyNode<T> *tailNode;

    void init_empty_list(const T &data)
    {
        headNode = new doublyNode<T>{nullptr, data, nullptr};
        if (!headNode)
            throw logic_error("Run out of memory, no node is created!");
        tailNode = headNode->nextNode = headNode->prevNode = headNode;
    }

public:
    circular_doubly_LL() : headNode(nullptr), tailNode(nullptr) {}

    circular_doubly_LL(const T &data)
    {
        try
        {
            init_empty_list(data);
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // deep copy
    circular_doubly_LL(const circular_doubly_LL &copy)
    {
        if (copy.headNode)
        {
            try
            {
                init_empty_list(copy.headNode->data);
                doublyNode<T> *current = headNode;
                doublyNode<T> *copy_current = copy.headNode->nextNode;
                while (copy_current != copy.headNode)
                {
                    current->nextNode = new doublyNode<T>{current, copy_current->data, nullptr};
                    if (!current->nextNode)
                        throw logic_error("Run out of memory, some nodes are copied!");
                    current = current->nextNode;
                    copy_current = copy_current->nextNode;
                }
                tailNode = current;
                tailNode->nextNode = headNode;
                headNode->prevNode = tailNode;
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
        else
            headNode = tailNode = nullptr;
    }

    ~circular_doubly_LL() { clear(); }

    bool search(const T &data) const
    {
        if (headNode)
        {
            doublyNode<T> *current = headNode;
            do
            {
                if (current->data == data)
                    return true;
                current = current->nextNode;
            } while (current != headNode);
        }
        return false;
    }

    void push_front(const T &data)
    {
        try
        {
            if (!headNode)
                init_empty_list(data);
            else
            {
                doublyNode<T> *newNode = new doublyNode<T>{nullptr, data, nullptr};
                if (!newNode)
                    throw logic_error("Run out of memory!");
                newNode->nextNode = headNode;
                newNode->prevNode = tailNode;
                headNode->prevNode = newNode;
                headNode = newNode;
                tailNode->nextNode = headNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void push_back(const T &data)
    {
        try
        {
            if (!headNode)
                init_empty_list(data);
            else
            {
                doublyNode<T> *newNode = new doublyNode<T>{nullptr, data, nullptr};
                if (!newNode)
                    throw logic_error("Run out of memory!");
                newNode->prevNode = tailNode;
                newNode->nextNode = headNode;
                tailNode->nextNode = newNode;
                tailNode = newNode;
                headNode->prevNode = tailNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void pop_front()
    {
        try
        {
            if (!headNode)
                throw logic_error("Linked-list is empty!");
            else if (headNode->nextNode == headNode)
            {
                delete headNode;
                headNode = tailNode = nullptr;
            }
            else
            {
                doublyNode<T> *deleteNode = headNode;
                headNode = headNode->nextNode;
                headNode->prevNode = tailNode;
                tailNode->nextNode = headNode;
                delete deleteNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void pop_back()
    {
        try
        {
            if (!headNode)
                throw logic_error("Linked-list is empty!");
            else if (headNode->nextNode == headNode)
            {
                delete headNode;
                headNode = tailNode = nullptr;
            }
            else
            {
                doublyNode<T> *deleteNode = tailNode;
                tailNode = tailNode->prevNode;
                tailNode->nextNode = headNode;
                headNode->prevNode = tailNode;
                delete deleteNode;
            }
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // FIXME:
    const T &getFront() const
    {
        try
        {
            if (headNode)
                return headNode->data;
            else
                throw out_of_range("Linked-list is empty!");
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    // FIXME:
    const T &getBack() const
    {
        try
        {
            if (tailNode)
                return tailNode->data;
            else
                throw out_of_range("Linked-list is empty!");
        }
        catch (const exception &e)
        {
            cout << e.what() << endl;
        }
    }

    void erase(const T &data)
    {
        if (!headNode)
        {
            cout << data << " is not in the list" << endl;
            return;
        }
        if (headNode->data == data)
        {
            pop_front();
            return;
        }
        else if (tailNode->data == data)
        {
            pop_back();
            return;
        }
        else
        {
            doublyNode<T> *current = headNode->nextNode;
            do
            {
                if (current->data == data)
                {
                    current->prevNode->nextNode = current->nextNode;
                    current->nextNode->prevNode = current->prevNode;
                    delete current;
                    return;
                }
                current = current->nextNode;
            } while (current != tailNode);
            cout << data << " is not in the list" << endl;
        }
    }

    void clear()
    {
        while (headNode)
            pop_front();
    }

    size_t size() const
    {
        size_t res = 0;
        doublyNode<T> *current = headNode;
        do
        {
            ++res;
            current = current->nextNode;
        } while (current != headNode);
        return res;
    }

    bool is_empty() const { return headNode == nullptr; }

    void merge(const circular_doubly_LL &rhs)
    {
        if (this != &rhs)
        {
            if (!rhs.headNode)
                return;
            try
            {
                if (!headNode) // empty + not empty
                {
                    init_empty_list(rhs.headNode->data);
                    doublyNode<T> *current = headNode;
                    doublyNode<T> *rhs_current = rhs.headNode->nextNode;
                    while (rhs_current != rhs.headNode)
                    {
                        current->nextNode = new doublyNode<T>{current, rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory, some nodes are merged!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    }
                    tailNode = current;
                    headNode->prevNode = tailNode;
                    tailNode->nextNode = headNode;
                }
                else // not empty + not empty
                {
                    doublyNode<T> *current = tailNode;
                    doublyNode<T> *rhs_current = rhs.headNode;
                    do
                    {
                        current->nextNode = new doublyNode<T>{current, rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory, some nodes are merged!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    } while (rhs_current != rhs.headNode);
                    tailNode = current;
                    headNode->prevNode = tailNode;
                    tailNode->nextNode = headNode;
                }
            }
            catch (const exception &e)
            {
                cout << e.what() << endl;
            }
        }
    }

    void reverse()
    {
        if (!headNode || headNode == tailNode)
            return;
        doublyNode<T> *prev_curr = nullptr;
        doublyNode<T> *current = headNode;
        doublyNode<T> *next_curr = nullptr;
        do
        {
            next_curr = current->nextNode;
            current->nextNode = current->prevNode;
            current->prevNode = next_curr;
            prev_curr = current;
            current = next_curr;
        } while (current != headNode);
        tailNode = headNode;
        headNode = prev_curr;
        tailNode->nextNode = headNode;
        headNode->prevNode = tailNode;
    }

    bool operator==(const circular_doubly_LL &rhs) const
    {
        if (this->size() != rhs.size())
            return false;
        doublyNode<T> *current = headNode;
        doublyNode<T> *rhs_current = rhs.headNode;
        do
        {
            if (current->data != rhs_current->data)
                return false;
            current = current->nextNode;
            rhs_current = rhs_current->nextNode;
        } while (current != headNode);
        return true;
    }

    circular_doubly_LL &operator=(const circular_doubly_LL &rhs)
    {
        if (this != &rhs)
        {
            clear();
            if (rhs.headNode)
            {
                try
                {
                    init_empty_list(rhs.headNode->data);
                    doublyNode<T> *current = headNode;
                    doublyNode<T> *rhs_current = rhs.headNode->nextNode;
                    while (rhs_current != rhs.headNode)
                    {
                        current->nextNode = new doublyNode<T>{current, rhs_current->data, nullptr};
                        if (!current->nextNode)
                            throw logic_error("Run out of memory, some nodes are copied!");
                        current = current->nextNode;
                        rhs_current = rhs_current->nextNode;
                    }
                    tailNode = current;
                    headNode->prevNode = tailNode;
                    tailNode->nextNode = headNode;
                }
                catch (const exception &e)
                {
                    cout << e.what() << endl;
                }
            }
            else
                headNode = tailNode = nullptr;
        }
        return *this;
    }

    template <class U>
    friend ostream &operator<<(ostream &output, const circular_doubly_LL<U> &list)
    {
        if (!list.headNode)
            output << "Linked-list is empty!";
        else
        {
            doublyNode<U> *current = list.headNode;
            do
            {
                output << current->getData();
                current = current->nextNode;
                if (current != list.headNode)
                    output << " ";
            } while (current != list.headNode);
        }
        return output;
    }
};