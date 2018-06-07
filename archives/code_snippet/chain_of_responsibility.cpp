#include <iostream>

class Handler
{
public:
    Handler() {}
    virtual ~Handler() {}

public:
    virtual void HandleRequest(int count) = 0;
    void SetSuccessor(Handler *successor)
    {
        m_successor = successor;
    }
    Handler *GetSuccessor()
    {
        return m_successor;
    }

protected:
    Handler *m_successor;
};

class ConcreteHandlerA : public Handler
{
public:
    ConcreteHandlerA() {}
    ~ConcreteHandlerA() {}

public:
    void HandleRequest(int count)
    {
        if (count < 100)
        {
            std::cout << "A: I can do it, done" << std::endl;
        }
        else
        {
            std::cout << "A: I can not do it, next" << std::endl;
            if (GetSuccessor() != nullptr)
            {
                GetSuccessor()->HandleRequest(count);
            }
        }
    }
};

class ConcreteHandlerB : public Handler
{
public:
    ConcreteHandlerB() {}
    ~ConcreteHandlerB() {}

public:
    void HandleRequest(int count)
    {
        if (count >= 100)
        {
            std::cout << "B: I can do it, done" << std::endl;
        }
    }
};

int main()
{
    Handler *a = new ConcreteHandlerA();
    Handler *b = new ConcreteHandlerB();
    a->SetSuccessor(b);

    a->HandleRequest(50);
    a->HandleRequest(150);

    a->SetSuccessor(nullptr);
    delete b;
    b = nullptr;
    delete a;
    a = nullptr;

    return 0;
}
